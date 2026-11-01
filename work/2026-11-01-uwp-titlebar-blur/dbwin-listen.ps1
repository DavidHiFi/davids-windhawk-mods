# Collects OutputDebugString lines from one process for a few seconds (DBWIN protocol).
param([int]$ProcessId, [int]$Seconds = 20, [string]$Out)
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text; using System.Threading;
public static class Dbwin {
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] static extern IntPtr CreateFileMapping(IntPtr h, IntPtr a, uint p, uint hi, uint lo, string n);
  [DllImport("kernel32.dll")] static extern IntPtr MapViewOfFile(IntPtr h, uint a, uint hi, uint lo, UIntPtr n);
  public static string Run(int pid, int seconds) {
    var ready = new EventWaitHandle(false, EventResetMode.AutoReset, "DBWIN_BUFFER_READY");
    var data = new EventWaitHandle(false, EventResetMode.AutoReset, "DBWIN_DATA_READY");
    IntPtr map = CreateFileMapping(new IntPtr(-1), IntPtr.Zero, 4, 0, 4096, "DBWIN_BUFFER");
    IntPtr view = MapViewOfFile(map, 4, 0, 0, new UIntPtr(4096));
    var sb = new StringBuilder(); var end = DateTime.Now.AddSeconds(seconds);
    ready.Set();
    while (DateTime.Now < end) {
      if (data.WaitOne(200)) {
        int p = Marshal.ReadInt32(view);
        if (pid == 0 || p == pid) sb.AppendLine(p + ": " + Marshal.PtrToStringAnsi(view + 4).TrimEnd());
        ready.Set();
      }
    }
    return sb.ToString();
  }
}
'@
$r = [Dbwin]::Run($ProcessId, $Seconds)
if ($Out) { $r | Out-File $Out -Encoding utf8 } else { $r }
