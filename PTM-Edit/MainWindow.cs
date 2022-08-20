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
using ScintillaNET;

namespace PTM_Edit
{
    public partial class MainWindow : Form
    {
        private Scintilla TxtProgram;
        private string _ProgramFilePath;
        private string ProgramFilePath
        {
            get => _ProgramFilePath;
            set {
                _ProgramFilePath = value;
                Text = "PTM-Edit";
                if (!string.IsNullOrWhiteSpace(_ProgramFilePath))
                    Text += " - " + _ProgramFilePath;
            }
        }
        private string SelectedFont;
        private int SelectedFontSize;

        public MainWindow()
        {
            InitializeComponent();
            LoadConfig();
            FormClosing += MainWindow_FormClosing;

            TxtProgram = new Scintilla();
            TxtProgram.Parent = RootPanel;
            TxtProgram.Dock = DockStyle.Fill;
            TxtProgram.BorderStyle = BorderStyle.None;
            TxtProgram.Margins[0].Width = 48;
            TxtProgram.HScrollBar = false;

            TxtProgram.StyleResetDefault();
            TxtProgram.Styles[Style.Default].Font = SelectedFont;
            TxtProgram.Styles[Style.Default].Size = SelectedFontSize;
            TxtProgram.StyleClearAll();
        }

        private void LoadConfig()
        {
            if (File.Exists("config.ini"))
            {
                var config = File.ReadAllLines("config.ini");
                SelectedFont = config[0];
                SelectedFontSize = int.Parse(config[1]);
            }
            else
            {
                SelectedFont = "Courier";
                SelectedFontSize = 10;
            }
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            List<string> config = new List<string>();
            config.Add(SelectedFont);
            config.Add(SelectedFontSize.ToString());
            File.WriteAllLines("config.ini", config);
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                TxtProgram.Text = File.ReadAllText(dialog.FileName);
                ProgramFilePath = dialog.FileName;
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (ProgramFilePath == null)
            {
                SaveFileDialog dialog = new SaveFileDialog();

                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    File.WriteAllText(dialog.FileName, TxtProgram.Text);
                    ProgramFilePath = dialog.FileName;
                }
            }
            else
            {
                File.WriteAllText(ProgramFilePath, TxtProgram.Text);
            }
        }

        private void runToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (ProgramFilePath == null)
            {
                saveToolStripMenuItem_Click(sender, e);
                if (ProgramFilePath == null) return;
            }
            else
            {
                File.WriteAllText(ProgramFilePath, TxtProgram.Text);
            }

            if (!File.Exists("PTM.exe"))
            {
                MessageBox.Show("PTM.exe not found in current directory", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Process.Start("PTM.exe", ProgramFilePath);
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProgramFilePath = null;
            TxtProgram.ClearAll();
        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FontDialog dialog = new FontDialog();

            try
            {
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    TxtProgram.StyleResetDefault();
                    TxtProgram.Styles[Style.Default].Font = dialog.Font.Name;
                    TxtProgram.Styles[Style.Default].Size = Convert.ToInt32(dialog.Font.Size);
                    TxtProgram.StyleClearAll();
                    SelectedFont = dialog.Font.Name;
                    SelectedFontSize = Convert.ToInt32(dialog.Font.Size);
                }
            }
            catch
            {
                MessageBox.Show("Unable to use selected font", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
