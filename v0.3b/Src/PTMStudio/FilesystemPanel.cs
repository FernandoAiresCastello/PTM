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
        private string RootDir;

        private FilesystemPanel()
        {
            InitializeComponent();
        }

        public FilesystemPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;
            RootDir = Path.Combine(MainWindow.WorkingDir, "files\\");
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

        private void UpdateFileList()
        {
            LstFiles.Items.Clear();
            var files = Directory.EnumerateFiles(RootDir, "*.*", SearchOption.AllDirectories);
            foreach (string path in files)
            {
                string file = path.Replace(RootDir, "").Replace("\\", "/");
                LstFiles.Items.Add(file);
            }
        }
    }
}
