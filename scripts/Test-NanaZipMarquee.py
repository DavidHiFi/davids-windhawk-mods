"""Objective repro/detect harness for the NanaZip drag-select marquee trails.

Launches NanaZip on a scratch folder containing only a few files, drags through
the empty lower half of the file list, then compares that region before the drag
with the same region after the button is released.

In a healthy app the marquee is erased on mouse-up, so the two captures match
over the empty region. Trails leave the rubber-band rectangles behind, which
shows up as a large pixel delta. Because the drag stays in empty space, no
selection can change, so any delta is repaint damage.

Safety: the window is made topmost for the test, and before any click the
script checks with WindowFromPoint that every sample point in the list belongs
to NanaZip. If anything else is on top (a game, an overlay), it aborts without
sending input. The first run of this harness hit a game window, which is why
the guard exists.

A result only counts when the marquee was visible mid-drag (marquee_seen); a
drag that never registered cannot prove the trails are gone.

Usage:
    python Test-NanaZipMarquee.py --label baseline
    python Test-NanaZipMarquee.py --label excluded --window-tree

Writes PNGs plus result.json to .tmp/nanazip-marquee/<label>/ and prints JSON.
"""

from __future__ import annotations

import argparse
import ctypes
import ctypes.wintypes as wt
import json
import os
import subprocess
import sys
import time
from pathlib import Path

from PIL import Image, ImageChops, ImageGrab

user32 = ctypes.WinDLL("user32", use_last_error=True)

REPO = Path(r"H:\System Configuration")
OUT_ROOT = REPO / ".tmp" / "nanazip-marquee"
SCRATCH = Path(os.environ["TEMP"]) / "nz-marquee-test"
NANAZIP_PROC = "NanaZip.Modern.FileManager.exe"
MODERNIZER_DLL = "win32-ui-modernizer"

MOUSEEVENTF_LEFTDOWN = 0x0002
MOUSEEVENTF_LEFTUP = 0x0004
SWP_NOACTIVATE = 0x0010
SW_RESTORE = 9
HWND_TOPMOST = -1
HWND_NOTOPMOST = -2
GA_ROOT = 2

# Pixels this far apart in any channel count as changed. High enough to ignore
# font antialiasing jitter, low enough to catch a thin rubber-band line.
DIFF_THRESHOLD = 24
# A single marquee outline over this drag is several thousand pixels; incidental
# repaint noise (a scrollbar hover) stays far below it.
TRAIL_PIXELS = 2000
MARQUEE_PIXELS = 400

user32.WindowFromPoint.restype = wt.HWND
user32.WindowFromPoint.argtypes = [wt.POINT]
user32.GetAncestor.restype = wt.HWND
user32.GetAncestor.argtypes = [wt.HWND, ctypes.c_uint]
user32.SetWindowPos.argtypes = [
    wt.HWND, wt.HWND, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_uint
]


def set_dpi_aware() -> None:
    try:
        # PER_MONITOR_AWARE_V2 so our coordinates are physical pixels, matching
        # what ImageGrab captures.
        user32.SetProcessDpiAwarenessContext(ctypes.c_void_p(-4))
    except Exception:
        try:
            ctypes.WinDLL("shcore").SetProcessDpiAwareness(2)
        except Exception:
            user32.SetProcessDPIAware()


WNDENUMPROC = ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)


def window_text(hwnd: int) -> str:
    n = user32.GetWindowTextLengthW(hwnd)
    buf = ctypes.create_unicode_buffer(n + 1)
    user32.GetWindowTextW(hwnd, buf, n + 1)
    return buf.value


def window_class(hwnd: int) -> str:
    buf = ctypes.create_unicode_buffer(256)
    user32.GetClassNameW(hwnd, buf, 256)
    return buf.value


def pid_of(hwnd: int) -> int:
    pid = wt.DWORD()
    user32.GetWindowThreadProcessId(hwnd, ctypes.byref(pid))
    return pid.value


def screen_rect(hwnd: int) -> tuple[int, int, int, int]:
    r = wt.RECT()
    user32.GetWindowRect(hwnd, ctypes.byref(r))
    return r.left, r.top, r.right, r.bottom


def top_level_windows(pids: set[int]) -> list[int]:
    found: list[int] = []

    def cb(hwnd, _lparam):
        if user32.IsWindowVisible(hwnd) and pid_of(hwnd) in pids:
            l, t, r, b = screen_rect(hwnd)
            if (r - l) > 200 and (b - t) > 200:
                found.append(hwnd)
        return True

    user32.EnumWindows(WNDENUMPROC(cb), 0)
    return found


def descendants(hwnd: int) -> list[int]:
    found: list[int] = []

    def cb(child, _lparam):
        found.append(child)
        return True

    user32.EnumChildWindows(hwnd, WNDENUMPROC(cb), 0)
    return found


def child_tree(hwnd: int, depth: int = 0, limit: int = 60) -> list[str]:
    rows: list[str] = []

    def cb(child, _lparam):
        if len(rows) >= limit:
            return False
        l, t, r, b = screen_rect(child)
        rows.append(
            f"{'  ' * depth}{window_class(child)!r} "
            f"[{l},{t},{r},{b}] {window_text(child)[:40]!r}"
        )
        rows.extend(child_tree(child, depth + 1, limit))
        return True

    user32.EnumChildWindows(hwnd, WNDENUMPROC(cb), 0)
    return rows


def pids_named(name: str) -> set[int]:
    out = subprocess.run(
        ["tasklist", "/FI", f"IMAGENAME eq {name}", "/FO", "CSV", "/NH"],
        capture_output=True,
        text=True,
    ).stdout
    pids: set[int] = set()
    for line in out.splitlines():
        parts = [p.strip('" ') for p in line.split('","')]
        if len(parts) >= 2 and parts[0].lower() == name.lower():
            try:
                pids.add(int(parts[1]))
            except ValueError:
                pass
    return pids


def modernizer_loaded(pid: int) -> bool:
    out = subprocess.run(
        ["tasklist", "/FI", f"PID eq {pid}", "/M", f"{MODERNIZER_DLL}*", "/FO", "CSV", "/NH"],
        capture_output=True,
        text=True,
    ).stdout
    return MODERNIZER_DLL.lower() in out.lower()


def kill_nanazip() -> None:
    subprocess.run(["taskkill", "/F", "/IM", NANAZIP_PROC], capture_output=True, text=True)
    time.sleep(1.0)


def ensure_scratch() -> None:
    SCRATCH.mkdir(parents=True, exist_ok=True)
    for old in SCRATCH.iterdir():
        if old.is_file():
            old.unlink()
    for i in range(4):
        (SCRATCH / f"sample-{i:02d}.txt").write_text(f"marquee harness file {i}\n")


def launch_nanazip(timeout: float = 25.0) -> int:
    alias = Path(os.environ["LOCALAPPDATA"]) / "Microsoft" / "WindowsApps" / "NanaZip.exe"
    subprocess.Popen([str(alias), str(SCRATCH)], close_fds=True)
    deadline = time.time() + timeout
    while time.time() < deadline:
        pids = pids_named(NANAZIP_PROC)
        if pids:
            wins = top_level_windows(pids)
            if wins:
                return wins[0]
        time.sleep(0.4)
    raise RuntimeError("NanaZip window did not appear")


def place_topmost(hwnd: int, x: int, y: int, w: int, h: int) -> None:
    user32.ShowWindow(hwnd, SW_RESTORE)
    # Topmost puts NanaZip above ordinary windows without needing the
    # foreground, which Windows refuses to hand to a background process.
    user32.SetWindowPos(hwnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE)
    time.sleep(1.5)


def find_listview(hwnd: int) -> int:
    for child in descendants(hwnd):
        if window_class(child) == "SysListView32" and user32.IsWindowVisible(child):
            return child
    raise RuntimeError("no visible SysListView32 in the NanaZip window")


def owner_at(x: int, y: int) -> tuple[int, int]:
    hit = user32.WindowFromPoint(wt.POINT(int(x), int(y)))
    return (hit or 0), (pid_of(hit) if hit else 0)


def assert_ours(points: list[tuple[int, int]], listview: int, pid: int) -> None:
    """Refuse to send input unless every point lands on NanaZip's list."""
    for x, y in points:
        hit, hit_pid = owner_at(x, y)
        if hit_pid != pid or hit != listview:
            raise RuntimeError(
                f"point ({x},{y}) hits {window_class(hit) if hit else None!r} "
                f"in pid {hit_pid}, not NanaZip's list (pid {pid}); aborting before any input"
            )


def grab(box: tuple[int, int, int, int]) -> Image.Image:
    return ImageGrab.grab(bbox=box, all_screens=True).convert("RGB")


def changed_pixels(a: Image.Image, b: Image.Image):
    diff = ImageChops.difference(a, b).convert("L")
    mask = diff.point(lambda v: 255 if v >= DIFF_THRESHOLD else 0)
    return sum(mask.histogram()[255:]), mask


def drag(box, x1: int, y1: int, x2: int, y2: int, steps: int = 45) -> Image.Image:
    """Drag with the real mouse and return a capture taken mid-drag."""
    user32.SetCursorPos(int(x1), int(y1))
    time.sleep(0.25)
    user32.mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0)
    time.sleep(0.15)
    mid = None
    try:
        for i in range(1, steps + 1):
            t = i / steps
            user32.SetCursorPos(round(x1 + (x2 - x1) * t), round(y1 + (y2 - y1) * t))
            time.sleep(0.02)
        time.sleep(0.35)
        mid = grab(box)
    finally:
        user32.mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)
    time.sleep(0.6)
    return mid


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--label", required=True)
    ap.add_argument("--keep-open", action="store_true")
    ap.add_argument("--window-tree", action="store_true")
    args = ap.parse_args()

    set_dpi_aware()
    out = OUT_ROOT / args.label
    out.mkdir(parents=True, exist_ok=True)

    kill_nanazip()
    ensure_scratch()
    hwnd = launch_nanazip()
    pid = pid_of(hwnd)

    result: dict = {
        "label": args.label,
        "pid": pid,
        "window_title": window_text(hwnd),
        "modernizer_dll_loaded": modernizer_loaded(pid),
    }

    try:
        place_topmost(hwnd, 100, 100, 1200, 820)
        listview = find_listview(hwnd)
        if args.window_tree:
            result["children"] = child_tree(hwnd)

        left, top, right, bottom = screen_rect(listview)
        w, h = right - left, bottom - top
        result["listview"] = [left, top, right, bottom]

        # Four files fill the first few rows; everything below the middle of the
        # list is empty, so a drag there cannot select anything.
        box = (left + 4, top + h // 2, right - 24, bottom - 4)
        result["capture_box"] = list(box)

        x1, y1 = left + int(w * 0.10), top + int(h * 0.58)
        x2, y2 = left + int(w * 0.62), top + int(h * 0.92)
        result["drag"] = [x1, y1, x2, y2]

        grid = [
            (box[0] + int((box[2] - box[0]) * fx), box[1] + int((box[3] - box[1]) * fy))
            for fx in (0.05, 0.5, 0.95)
            for fy in (0.05, 0.5, 0.95)
        ]
        assert_ours(grid + [(x1, y1), (x2, y2)], listview, pid)

        before = grab(box)
        before.save(out / "1-before.png")

        mid = drag(box, x1, y1, x2, y2)
        mid.save(out / "2-mid-drag.png")

        # Park the cursor well outside the window so its own hover highlight and
        # shape cannot contaminate the capture.
        user32.SetCursorPos(right + 260, bottom + 60)
        time.sleep(1.2)
        assert_ours(grid, listview, pid)

        after = grab(box)
        after.save(out / "3-after.png")

        mid_changed, _ = changed_pixels(before, mid)
        changed, mask = changed_pixels(before, after)
        mask.save(out / "4-diff-mask.png")

        total = mask.size[0] * mask.size[1]
        result["mid_drag_changed_pixels"] = mid_changed
        result["marquee_seen"] = mid_changed > MARQUEE_PIXELS
        result["changed_pixels"] = changed
        result["region_pixels"] = total
        result["changed_pct"] = round(100.0 * changed / total, 4)
        result["diff_bbox"] = list(mask.getbbox()) if mask.getbbox() else None
        result["trails_detected"] = changed > TRAIL_PIXELS
        result["valid"] = result["marquee_seen"]
    finally:
        if pids_named(NANAZIP_PROC):
            user32.SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, 0x0001 | 0x0002 | SWP_NOACTIVATE)

    (out / "result.json").write_text(json.dumps(result, indent=2))
    print(json.dumps(result, indent=2))

    if not args.keep_open:
        kill_nanazip()
    return 0


if __name__ == "__main__":
    sys.exit(main())
