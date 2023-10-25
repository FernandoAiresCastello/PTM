using System;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio
{
    internal static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            string ptmExe = Path.Combine(Filesystem.AbsoluteRootPath, "PTM.exe");

            if (File.Exists(ptmExe))
            {
                try
                {
                    Application.Run(new MainWindow(ptmExe));
                }
                catch (Exception ex)
                {
                    MainWindow.UnexpectedError(ex.ToString());
                }
            }
            else
            {
                MainWindow.FatalError("PTM.exe not found");
            }
        }
    }
}
