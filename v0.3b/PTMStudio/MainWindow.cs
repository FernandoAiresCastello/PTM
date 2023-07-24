using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ScintillaNET;

namespace PTMStudio
{
    public partial class MainWindow : Form
    {
        public string WorkingDir { get; private set; }
        private string PtmExe;
        private string ProgramFile = "";
        private ProgramEditPanel PrgPanel;
        private Scintilla Scintilla;
        private FilesystemPanel FilePanel;

        public MainWindow(string workingDir, string ptmExe)
        {
            InitializeComponent();

            WorkingDir = workingDir;
            PtmExe = ptmExe;

            PrgPanel = new ProgramEditPanel();
            PrgPanel.Parent = SplitContainer.Panel1;
            PrgPanel.Dock = DockStyle.Fill;

            Scintilla = new Scintilla();
            Scintilla.Parent = PrgPanel.ScintillaPanel;
            Scintilla.Dock = DockStyle.Fill;
            Scintilla.BorderStyle = BorderStyle.Fixed3D;
            Scintilla.HScrollBar = true;
            Scintilla.VScrollBar = true;
            Scintilla.Margins[0].Width = 40;

            FilePanel = new FilesystemPanel(this);
            FilePanel.Parent = TopRightPanel;
            FilePanel.Dock = DockStyle.Fill;
        }

        public void Abort(string message)
        {
            ErrorMessage(message);
            Application.Exit();
        }

        public void ErrorMessage(string message)
        {
            MessageBox.Show(this,
                message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void BtnRun_Click(object sender, EventArgs e)
        {
            Process.Start(PtmExe, ProgramFile);
        }

        public void OpenFile(string file)
        {
            ProgramFile = file;
            string program = File.ReadAllText(file);
            Scintilla.Text = program;
        }
    }
}
