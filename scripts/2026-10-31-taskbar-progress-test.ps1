# Shows a minimized, non-activated test window with taskbar progress, captures the
# taskbar strip at a few states, then closes. Usage: -Out <png prefix>
param([string]$Out = "$env:TEMP\tbprog")
Add-Type -ReferencedAssemblies System.Windows.Forms, System.Drawing -TypeDefinition @'
using System; using System.Runtime.InteropServices; using System.Windows.Forms; using System.Drawing;
[ComImport, Guid("ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface ITaskbarList3 { void HrInit(); void AddTab(IntPtr h); void DeleteTab(IntPtr h); void ActivateTab(IntPtr h); void SetActiveAlt(IntPtr h);
 void MarkFullscreenWindow(IntPtr h, bool f); void SetProgressValue(IntPtr h, ulong c, ulong t); void SetProgressState(IntPtr h, int s); }
[ComImport, Guid("56FDF344-FD6D-11d0-958A-006097C9A090")] class TaskbarList {}
public static class TbTest {
  [DllImport("user32.dll")] static extern bool ShowWindow(IntPtr h, int c);
  public static void Run(string prefix) {
    var f = new Form { Text = "Progress test", ShowInTaskbar = true, WindowState = FormWindowState.Minimized, ShowIcon = true };
    f.CreateControl(); var h = f.Handle; ShowWindow(h, 7);
    var tb = (ITaskbarList3)new TaskbarList(); tb.HrInit(); var t0 = DateTime.Now; while ((DateTime.Now - t0).TotalMilliseconds < 4000) { Application.DoEvents(); System.Threading.Thread.Sleep(20); }
    Action<string,int,int> shot = (n, state, val) => {
      tb.SetProgressState(h, state); if (val >= 0) tb.SetProgressValue(h, (ulong)val, 100);
      var t = DateTime.Now; while ((DateTime.Now - t).TotalMilliseconds < 1500) { Application.DoEvents(); System.Threading.Thread.Sleep(20); }
      var w = Screen.PrimaryScreen.Bounds.Width; var bmp = new Bitmap(w, 60);
      using (var g = Graphics.FromImage(bmp)) g.CopyFromScreen(0, 0, 0, 0, bmp.Size);
      bmp.Save(prefix + "-" + n + ".png");
    };
    shot("d60", 2, 60); shot("paused", 8, 60); shot("error", 4, 85); shot("busy", 1, -1);
    tb.SetProgressState(h, 0); f.Close();
  }
}
'@
[TbTest]::Run($Out)

