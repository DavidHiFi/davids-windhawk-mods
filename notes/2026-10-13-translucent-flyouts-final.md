# Translucent Flyouts: final menu look (2026-10-13)

Live: local@translucent-flyouts 0.6.16 (LibraryFileName=local@translucent-flyouts_0.6.16_1.dll).
Public repo: DavidHiFi/davids-windhawk-mods PR #10 (merged), mods/local/translucent-flyouts at 0.6.16.

## Verified after an Explorer restart (pixel samples, screen.png)

- Outline: Catppuccin Mocha blue #89B4FA on all four edges of the main menu, and on the submenu.
- Fill: Mocha-tinted acrylic. Tint is #1E1E2E at 80% (0xCC1E1E2E), read from the registry after a restart
  (a red test colour came through, so the setting is applied).
- Measured interior fill over the same backdrop: about (67,68,84), against a backdrop of about (44,47,64)
  and a Mocha base of (30,30,46). Windows acrylic lightens dark tints, so the interior reads as blue-grey,
  not pure base. Solid base would remove the blur.

## Persistent

- Registry (HKLM Mods\local@translucent-flyouts\Settings): menu and global dark and light
  BorderColor = 0xFF89B4FA; GradientColor = 0xCC1E1E2E.
- Source defaults in the settings block and the 10-settings fallbacks use the same values, so a settings reset
  falls back to Mocha.

## Rollback

    H:\System Configuration\scripts\Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-13-translucent-flyouts-0.6.16.ps1" -ArgumentList "-Rollback"

Goes back to 0.6.15 (source backup: backups\2026-10-13\translucent-flyouts-corners\local@translucent-flyouts.wh.cpp.0.6.15).

## Not checked

- Tooltips and dropdowns: the drop-shadow and theme-colouring settings are global, so they follow the same
  values. Not checked on screen.

## Update (2026-10-13, after the 0.6.16 merge): background effect

- menu.effectType = blurred (registry). Measured fill inside the menu: about (36,36,36), against a backdrop of about (42,42,57).
- Measured for comparison (same backdrop, after restart): modern acrylic about (66,67,83) at any tint alpha; classic acrylic about (66,67,83);
  solid at 80% about (62,62,78); opaque tint with acrylic about (68,68,84). Acrylic adds a lightening layer that dark tints cannot remove.
- Blurred keeps the blur and matches the base brightness, but it ignores the tint colour, so the fill is neutral grey, not the Mocha blue cast.
- The repo (0.6.16) still defaults the menu effect to inherit the global acrylic. The blurred choice is in the registry only.
