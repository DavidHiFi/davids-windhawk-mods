# Keys helper for Seamless Launchpad

Windows keeps keys you press in an app running as administrator away from
apps that don't run that way, Explorer included. So while such an app is in
front, the mod never sees Shift + Windows key, and the grid doesn't open.

This small program runs as administrator in the background and passes that
key on to the mod. Without it, everything else still works: the Windows key,
Ctrl+Esc and the Start button aren't affected.

## Install

1. Build it with the clang that comes with Windhawk:

   ```
   "C:\Program Files\Windhawk\Compiler\bin\clang++.exe" -std=c++23 -O2 -municode -mwindows -static -target x86_64-w64-mingw32 launchpad-keys.cpp -o launchpad-keys.exe
   ```

2. In PowerShell as administrator, run `.\install.ps1` from this folder. It
   copies the program to `C:\Program Files\SeamlessLaunchpad` and adds a
   scheduled task, `SeamlessLaunchpadKeys`, that starts it when you sign in.

To remove it, run `.\install.ps1 -Uninstall` as administrator.
