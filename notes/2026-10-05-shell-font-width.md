# Readability floor for shell font fitting

The user reported that "Object name:" in the drive Properties Security tab was squeezed into tiny, cramped text, and that the "Permissions for ..." line was flattened until it couldn't be read. Both came from the fit logic in 1.2.1 through 1.2.2_2. When Fira Code overflowed a fixed box, it shrank height or character width as far as needed, sometimes to 1 pixel. Fira Code is much wider than Segoe UI, so narrow labels in dialogs drawn for Segoe UI were hit hard.

Installed Shell Font Changer 1.2.2_4 on 2026-10-05. Text with enough space keeps its normal size. Overflowing text may shrink to 85% height (`kMinScale`) and 80% average character width (`kMinWidth`). If it still overflows, `FontScope::revert()` hands that run back to the original UI font, because the control was laid out for that font. The user confirmed 1.2.2_3 looked good. 1.2.2_4 changes only comments and drops an unused parameter.

**Rule for later changes:** never fit text by shrinking without a floor. Readable text in the original font beats unreadable text in Fira Code. The tests now check "fits, or kept the original font, and stays readable", so don't put back the old "always fits" assertions. The old assertions made the shrinking look correct.

Both architectures pass every test. The live probe passed, with GDI handles flat at 9. The installed DLL hashes match the build. Explorer, Start, ShellHost and SearchHost load 1.2.2_4. Older DLLs were deleted from the engine folder, except a locked 64-bit 1.2.2_3, which the engine clears later.

Evidence: reports/2026-10-05-shell-font-width. Backup: backups/2026-10-05-shell-font-width. Run scripts/2026-10-05-shell-font-width-verify.cmd elevated to check the install. Roll back by restoring backups/2026-10-05-shell-font-width/old-*.dll, which brings back 1.2.2_1 and its tiny text. Earlier rollbacks are in the shell-font-readable and shell-font-fit notes.
