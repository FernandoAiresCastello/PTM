using PTMStudio.Windows;
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

			string ptmExe = "ptml.exe";
			string dir = Environment.CurrentDirectory;
			string ptmExePath = Path.Combine(dir, ptmExe);

			if (!File.Exists(ptmExePath))
			{
				MainWindow.Error($"PTML interpreter ({ptmExe}) not found");
				return;
			}

			try
			{
				MainWindow mainWindow;
				StartWindow startWindow;

				do
				{
					startWindow = new StartWindow();
					if (startWindow.ShowDialog() == DialogResult.Cancel)
						break;

					mainWindow = new MainWindow(ptmExePath, startWindow.ProjectFolder);
					Application.Run(mainWindow);
				}
				while (mainWindow.ShouldRestart);
			}
			catch (Exception ex)
			{
				MainWindow.UnexpectedError(ex.ToString());
			}
		}
    }
}
