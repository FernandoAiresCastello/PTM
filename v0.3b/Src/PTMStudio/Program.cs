using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTMStudio
{
    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            string workingDir = Environment.CurrentDirectory;
            string ptmExe = Path.Combine(workingDir, "PTM.exe");

            if (File.Exists(ptmExe))
            {
                Application.Run(new MainWindow(workingDir, ptmExe));
            }
            else
            {
                MessageBox.Show("PTM.exe not found", "Fatal Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
