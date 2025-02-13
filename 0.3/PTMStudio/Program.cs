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

			string dir = Environment.CurrentDirectory;
			string ptmExe = "PTM_INTP.exe";
            string ptmExePath = Path.Combine(dir, ptmExe);

            if (File.Exists(ptmExePath))
            {
                try
                {
                    MainWindow mainWindow;

					do
                    {
						mainWindow = new MainWindow(ptmExePath);
						Application.Run(mainWindow);
                    }
                    while (mainWindow.ShouldRestart);
                }
                catch (Exception ex)
                {
                    MainWindow.UnexpectedError(ex.ToString());
                }
            }
            else
            {
                MainWindow.FatalError($"PTML interpreter ({ptmExe}) not found");
            }
        }
    }
}
