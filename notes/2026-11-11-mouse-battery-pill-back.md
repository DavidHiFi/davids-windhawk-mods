# 2026-11-11: mouse battery pill vanished, brought back (5:19 pm)

- Symptom: the Logitech battery dock between the tray and the clock was gone.
- Cause: logitech-battery-tray hides its dock when it has no devices. Its direct receiver
  link (HID++) had found nothing and does not retry on its own. Styler rules 56-60 were
  untouched (last change 2026-11-10 6:35 pm); G HUB is not installed, so HID++ is the only source.
- Fix: reloaded the mod (SettingsChangeTime bump). The log then read "HID++ battery endpoint:
  USB Receiver, feature=0x1004" and the dock came back showing 93%.
- LoggingEnabled was turned on for the diagnosis and left on (no extra reload risk).
- Backup: backups\2026-11-11\battery-reload\logitech-battery-tray-before.reg.
  Rollback: reg import it, bump SettingsChangeTime.
- Not caused by the volume mixer work. The exact trigger of the lost link is not proven.
- Fan Control icons in the left dock are icon-only; the earlier big "100" was Taskbar Volume
  Control's volume number (now off), not a fan speed. The mixer's own number shows instead.
