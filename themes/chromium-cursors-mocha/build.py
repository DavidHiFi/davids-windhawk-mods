r"""Build Catppuccin Mocha Dark .cur files for the ten cursors Chromium draws itself.

Source: github.com/catppuccin/cursors src/svgs (GPL-2.0). Colors follow its
svgs.tera template for the "dark" accent: inner = base, border = text,
special = per-file accent (alias mauve, copy green). Hotspot = top-left of the
SVG's id="hotspot" path, floored like upstream generate-metadata.

Usage: .venv\Scripts\python build.py <out_dir>
"""
import io, math, re, struct, sys, urllib.request
from pathlib import Path

import resvg_py
from PIL import Image

SRC = "https://raw.githubusercontent.com/catppuccin/cursors/main/src/svgs/"
BASE, TEXT = "1e1e2e", "cdd6f4"
SPECIAL = {"alias": "cba6f7", "copy": "a6e3a1"}
# output name -> upstream svg (aliases from upstream src/cursorList)
CURSORS = {
    "grab": "openhand", "grabbing": "dnd-move", "zoom-in": "zoom-in",
    "zoom-out": "zoom-out", "cell": "cell", "vertical-text": "vertical-text",
    "alias": "alias", "copy": "copy", "col-resize": "col-resize",
    "row-resize": "row-resize",
}
SIZES = (32, 48, 64)  # same set as the installed Catppuccin pack


def hotspot(svg: str):
    m = re.search(r'<path[^>]*id="hotspot"[^>]*>', svg, re.S)
    d = re.search(r'\sd="([^"]+)"', m.group(0)).group(1)
    x = y = 0.0
    pts = []
    for cmd, args in re.findall(r"([mMlLhHvVzZ])([^mMlLhHvVzZ]*)", d):
        nums = [float(n) for n in re.findall(r"-?[\d.]+(?:e-?\d+)?", args)]
        rel = cmd.islower()
        c = cmd.lower()
        if c in "ml":
            for i in range(0, len(nums), 2):
                x, y = (x + nums[i], y + nums[i + 1]) if rel else (nums[i], nums[i + 1])
                pts.append((x, y))
        elif c == "h":
            for n in nums:
                x = x + n if rel else n
                pts.append((x, y))
        elif c == "v":
            for n in nums:
                y = y + n if rel else n
                pts.append((x, y))
    return min(p[0] for p in pts), min(p[1] for p in pts)


def bmp_entry(img: Image.Image) -> bytes:
    w, h = img.size
    px = img.tobytes("raw", "BGRA")
    rows = [px[r * w * 4:(r + 1) * w * 4] for r in range(h)][::-1]
    xor = b"".join(rows)
    mask_stride = ((w + 31) // 32) * 4
    andmask = b"\x00" * (mask_stride * h)  # alpha carries transparency
    hdr = struct.pack("<IiiHHIIiiII", 40, w, h * 2, 1, 32, 0, len(xor) + len(andmask), 0, 0, 0, 0)
    return hdr + xor + andmask


def write_cur(path: Path, images, hot32):
    entries, blobs = [], []
    off = 6 + 16 * len(images)
    for img in images:
        s = img.size[0]
        hx = math.floor((hot32[0] * s / 32 * 100 + 1) / 100)
        hy = math.floor((hot32[1] * s / 32 * 100 + 1) / 100)
        blob = bmp_entry(img)
        entries.append(struct.pack("<BBBBHHII", s % 256, s % 256, 0, 0, hx, hy, len(blob), off))
        blobs.append(blob)
        off += len(blob)
    path.write_bytes(struct.pack("<HHH", 0, 2, len(images)) + b"".join(entries) + b"".join(blobs))


def main(out: Path):
    out.mkdir(parents=True, exist_ok=True)
    for name, src in CURSORS.items():
        svg = urllib.request.urlopen(SRC + src + ".svg", timeout=30).read().decode()
        svg = re.sub("FF0000", BASE, svg, flags=re.I)
        svg = re.sub("00FF00", TEXT, svg, flags=re.I)
        svg = re.sub("0000FF", SPECIAL.get(src, BASE), svg, flags=re.I)
        hot = hotspot(svg)
        imgs = []
        for s in SIZES:
            png = bytes(resvg_py.svg_to_bytes(svg_string=svg, width=s, height=s))
            imgs.append(Image.open(io.BytesIO(png)).convert("RGBA"))
        write_cur(out / f"{name}.cur", imgs, hot)
        print(f"{name}.cur  <- {src}.svg  hotspot32={hot}")


if __name__ == "__main__":
    main(Path(sys.argv[1]))
