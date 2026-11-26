# Crisp tray icons (2026-11-26)

Owner: "The icons look kind of low resolution. They look kind of aliased. Can you audit and
make sure that they're like high fidelity, high quality?"

## Cause

- The tray shows icons at 16 px on Warden (glyph about 13 px, measured on a live capture;
  the earlier guess of a 32 px box was wrong).
- Our mods drew tray icons straight at SM_CXSMICON (16) with GDI.
- GDI drawing (ellipses, polygons, text) has no smoothing, so edges were stair-stepped.
- Several mods handed Windows premultiplied colour, which darkens the soft edge pixels.

## Fix

- `work\2026-11-26-crisp-icons\crisp.py <live> <out>` patches a mod source:
  - adds `Crisp_ShrinkIcon(HICON big, int factor)`: reads the bits, box-averages, outputs
    straight alpha at the small size, destroys the big icon;
  - renames each icon maker to `NAME_Big`, draws it at 4x SM_CXICON, and adds a wrapper
    `NAME(...) { return Crisp_ShrinkIcon(NAME_Big(...), 4); }`;
  - moves tray callers from SM_CXSMICON to SM_CXICON; bumps the version.
- `install-crisp.sh [mods]` installs one at a time under the engine lock through
  Install-StagedMod (which publishes). A mod another thread moved is re-patched from live.
- Etcher (mocha-audio `app.rs`) already draws with analytic coverage at 32 px: no change.

## Rule

- `docs\settings-gui-standard.md` (tray icon bullets) and the rice style reference,
  "App and tray icons". Memory: crisp-tray-icons. Board note posted for the suite threads.

## Result

(filled in below as mods go live)
