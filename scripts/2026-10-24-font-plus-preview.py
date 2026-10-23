"""Render the Shell Font Changer Plus before/after preview from real font files.

The live engine is stopped (freeze investigation), so the preview is drawn with
the font files the mod would use. The Explorer layout is a mock; the text uses
each font's real glyph outlines. The folder icon comes from Segoe Fluent Icons in
both panels, because the mod leaves icon fonts alone.

Usage: python 2026-10-24-font-plus-preview.py <output.png>
"""
import sys
from PIL import Image, ImageDraw, ImageFont

OUT = sys.argv[1]
SS = 2  # draw at 2x, downsample for smooth edges
W, H = 1200, 675

SEGOE = r"C:\Windows\Fonts\segoeui.ttf"
SEGOE_BOLD = r"C:\Windows\Fonts\segoeuib.ttf"
ICONS = r"C:\Windows\Fonts\SegoeIcons.ttf"
FIRA = r"C:\Users\localuser\AppData\Local\Microsoft\Windows\Fonts\FiraCodeNerdFont-Regular.ttf"
FIRA_BOLD = r"C:\Users\localuser\AppData\Local\Microsoft\Windows\Fonts\FiraCodeNerdFont-Bold.ttf"

BG = (14, 15, 20)
PANEL = (32, 33, 38)
PANEL_EDGE = (58, 60, 68)
ROW_SELECTED = (48, 62, 84)
ROW_LINE = (48, 50, 58)
TEXT = (240, 241, 245)
MUTED = (150, 154, 166)
ACCENT = (96, 205, 255)
FOLDER = (245, 196, 81)

FOLDER_GLYPH = "\ue8b7"  # Segoe Fluent Icons: Folder
ROWS = [
    ("Documents", "10/24/2026 9:14 AM", "File folder"),
    ("Downloads", "10/23/2026 6:02 PM", "File folder"),
    ("Pictures", "10/20/2026 8:30 AM", "File folder"),
]


def font(path, size):
    return ImageFont.truetype(path, int(size * SS))


def px(v):
    return int(round(v * SS))


def draw_panel(d, top, tag, accent, face, face_bold):
    """One Explorer-style panel. `face` and `face_bold` are the font under test."""
    left, right = 36, W - 36
    d.rounded_rectangle([px(left), px(top), px(right), px(top + 306)],
                        radius=px(22), fill=PANEL, outline=PANEL_EDGE, width=px(2))

    # The tag stays in Segoe UI so only the Explorer content changes.
    tag_font = font(SEGOE_BOLD, 22)
    tag_w = d.textlength(tag, font=tag_font) / SS
    d.text((px(right - 28 - tag_w), px(top + 24)), tag, font=tag_font, fill=accent)

    d.text((px(left + 30), px(top + 22)), "This PC  \u203a  Documents",
           font=font(face_bold, 28), fill=TEXT)

    head = font(face, 21)
    header_y = top + 82
    d.text((px(left + 110), px(header_y)), "Name", font=head, fill=MUTED)
    d.text((px(left + 480), px(header_y)), "Date modified", font=head, fill=MUTED)
    d.text((px(left + 830), px(header_y)), "Type", font=head, fill=MUTED)

    icon = font(ICONS, 30)
    name_font = font(face, 30)
    body = font(face, 26)
    for i, (name, date, kind) in enumerate(ROWS):
        y = top + 116 + i * 60
        if i == 0:
            d.rounded_rectangle([px(left + 14), px(y - 6), px(right - 14), px(y + 48)],
                                radius=px(10), fill=ROW_SELECTED)
        else:
            d.line([px(left + 30), px(y + 52), px(right - 30), px(y + 52)],
                   fill=ROW_LINE, width=px(1))
        d.text((px(left + 36), px(y + 2)), FOLDER_GLYPH, font=icon, fill=FOLDER)
        d.text((px(left + 110), px(y)), name, font=name_font, fill=TEXT)
        d.text((px(left + 480), px(y + 4)), date, font=body, fill=MUTED)
        d.text((px(left + 830), px(y + 4)), kind, font=body, fill=MUTED)


def main():
    img = Image.new("RGB", (W * SS, H * SS), BG)
    d = ImageDraw.Draw(img)
    draw_panel(d, 24, "WINDOWS DEFAULT  Segoe UI", MUTED,
               SEGOE, SEGOE_BOLD)
    draw_panel(d, 345, "SHELL FONT CHANGER PLUS  FiraCode Nerd Font", ACCENT,
               FIRA, FIRA_BOLD)
    img = img.resize((W, H), Image.LANCZOS)
    img.save(OUT, optimize=True)
    print("wrote", OUT, img.size)


if __name__ == "__main__":
    main()
