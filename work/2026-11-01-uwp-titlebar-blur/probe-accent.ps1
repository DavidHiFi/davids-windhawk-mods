# Opens the Store, reads the frame's accent policy and system backdrop, closes it.
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class P {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc p, IntPtr l);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [StructLayout(LayoutKind.Sequential)] public struct ACCENT { public int State, Flags, Color, Anim; }
  [StructLayout(LayoutKind.Sequential)] public struct DATA { public int Attr; public IntPtr Data; public IntPtr Size; }
  [DllImport("user32.dll")] public static extern bool GetWindowCompositionAttribute(IntPtr h, ref DATA d);
  [DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h, int a, out int v, int s);
  public static string Accent(IntPtr h) {
    var a = new ACCENT(); var p = Marshal.AllocHGlobal(16); Marshal.StructureToPtr(a, p, false);
    var d = new DATA { Attr = 19, Data = p, Size = (IntPtr)16 };
    bool ok = GetWindowCompositionAttribute(h, ref d);
    a = (ACCENT)Marshal.PtrToStructure(p, typeof(ACCENT)); Marshal.FreeHGlobal(p);
    return "ok=" + ok + " err=" + Marshal.GetLastWin32Error() + " state=" + a.State + " flags=" + a.Flags + " color=0x" + a.Color.ToString("X8");
  }
  public static IntPtr Find(string title) {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => {
      var c = new StringBuilder(64); GetClassName(h, c, 64);
      var t = new StringBuilder(64); GetWindowText(h, t, 64);
      if (c.ToString() == "ApplicationFrameWindow" && t.ToString() == title && IsWindowVisible(h)) { found = h; return false; }
      return true; }, IntPtr.Zero);
    return found;
  }
}
'@
$h = [P]::Find('Microsoft Store'); $opened = $false
if ($h -eq [IntPtr]::Zero) {
  Start-Process 'ms-windows-store:'; $opened = $true
  for ($i = 0; $i -lt 80 -and $h -eq [IntPtr]::Zero; $i++) { Start-Sleep -Milliseconds 250; $h = [P]::Find('Microsoft Store') }
}
if ($h -eq [IntPtr]::Zero) { 'no store frame'; exit 1 }
Start-Sleep -Seconds 4
$bd = 0; [void][P]::DwmGetWindowAttribute($h, 38, [ref]$bd, 4)
"frame=$h backdrop=$bd accent: $([P]::Accent($h))"
if ($opened) { [void][P]::PostMessage($h, 0x10, [IntPtr]::Zero, [IntPtr]::Zero) }
