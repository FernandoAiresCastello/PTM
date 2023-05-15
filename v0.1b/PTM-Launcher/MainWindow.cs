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

namespace PTM_Launcher
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
            UpdateFileList();

            LstFiles.DoubleClick += LstFiles_DoubleClick;
        }

        public void UpdateFileList()
        {
            string dir = AppDomain.CurrentDomain.BaseDirectory;
            var files = Directory.EnumerateFiles(dir, "*.ptm");

            LstFiles.Items.Clear();
            LstFiles.HeaderStyle = ColumnHeaderStyle.None;

            foreach (var file in files)
            {
                ListViewItem item = new ListViewItem();
                item.Text = new FileInfo(file).Name;
                item.Tag = file;
                LstFiles.Items.Add(item);
            }

            LstFiles.Columns[0].AutoResize(ColumnHeaderAutoResizeStyle.ColumnContent);
        }

        private void LstFiles_DoubleClick(object sender, EventArgs e)
        {
            if (LstFiles.SelectedItems.Count == 0 || LstFiles.SelectedItems[0] == null)
                return;

            string file = LstFiles.SelectedItems[0].Tag as string;

            Process.Start("PTM.exe", "\"" + file + "\"");
        }
    }
}
