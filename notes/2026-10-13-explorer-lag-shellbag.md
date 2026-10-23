# Size on disk left in saved folder views: removed

2026-10-13. Follows `notes\2026-10-13-explorer-lag-bisect.md`. That note's verification
line said Size on disk was absent. It was absent from the module census, but folders
still showed the column on screen. Checked by screenshot: `C:\Users\localuser\AppData\Local`
still had a "Size on disk" column.

## Cause

`explorer-size-on-disk-column` only changes what Explorer reads from its folder templates
(it hooks the `ColumnList` read). It writes nothing. The column survived because Explorer
had saved it into each folder's view memory (shell bags) while the mod was active. Disabling
the mod does not remove those saved entries.

## Change

67 `ColInfo` values under the two shell-bag roots each had one Size-on-disk entry. Each entry
was removed and the column count decremented by one. Nothing else in those values was touched.

- Layout (measured): a 40-byte header, with the column count at offset 32 and the entry size
  (24) at offset 36. Each entry is a 16-byte property-set GUID, a 4-byte property ID and a
  4-byte width. Size on disk is property ID 18 in the storage set.
- Roots: `HKCU\Software\Microsoft\Windows\Shell\Bags` (no matches) and
  `HKCU\Software\Classes\Local Settings\Software\Microsoft\Windows\Shell\Bags` (67 matches).
- Explorer was stopped during the edit so it could not rewrite the views, then restarted.
- Script: `scripts\2026-10-13-explorer-lag-shellbag-size-on-disk.ps1` (`-Audit`, `-Apply`,
  `-Rollback <folder>`).

## Verification

- Audit before the edit: 67 values, 67 entries, each count 5 to 6 going down by one.
- After the edit, readback: 0 values still contain Size on disk. Explorer restarted with
  87 Windhawk DLLs loaded.
- Screenshot (`reports\2026-10-13-explorer-lag\visual-after-shellbag-fix-2.png`):
  AppData\Local shows Name, Date modified, Type, Size. No "Size on..." column.

## Rollback

Stop Explorer, then run (elevation is not needed, since these are per-user keys):

    scripts\2026-10-13-explorer-lag-shellbag-size-on-disk.ps1 -Rollback "H:\Windhawk Configuration\backups\2026-10-13\explorer-lag\shellbags"

That re-imports both exports, so any folder view changes made after 2026-10-13 are overwritten
by the saved state. Backups: `backups\2026-10-13\explorer-lag\shellbags\`.

## Left as is

- Date modified and Type columns truncate on navigation because auto-fit no longer runs then
  (see the bisect note). F5 fits them.
- Folder sizes show in Size only while Shift is held on load or refresh.
