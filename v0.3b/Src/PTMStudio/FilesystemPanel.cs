using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTMStudio
{
    public partial class FilesystemPanel : UserControl
    {
        private MainWindow MainWindow;
        private static string RootDir;

        private FilesystemPanel()
        {
            InitializeComponent();
        }

        public FilesystemPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;
            RootDir = Path.Combine(MainWindow.WorkingDir, "files/").Replace("\\", "/");
            UpdateFileList();

            LstFiles.DoubleClick += LstFiles_DoubleClick;
        }

        private void LstFiles_DoubleClick(object sender, EventArgs e)
        {
            string file = LstFiles.SelectedItem as string;
            if (file == null)
                return;

            MainWindow.LoadFile("files/" + file);
        }

        public void UpdateFileList()
        {
            LstFiles.Items.Clear();
            var files = Directory.EnumerateFiles(RootDir, "*.*", SearchOption.AllDirectories);
            foreach (string path in files)
            {
                string file = path.Replace("\\", "/").Replace(RootDir, "");
                LstFiles.Items.Add(file);
            }
        }

        public static string NormalizePath(string path)
        {
            return path.Replace("\\", "/");
        }

        public static string RemoveAbsoluteRoot(string path)
        {
            return path.Replace(RootDir, "");
        }

        public static string RemoveFilesPrefix(string path)
        {
            if (path.StartsWith("files/"))
                path = path.Substring(6);

            return path;
        }
    }
}
