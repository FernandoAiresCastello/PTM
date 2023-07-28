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
        private readonly string MainProgramFile = "files/main.ptm";
        private ProgramEditPanel ProgramPanel;
        private FilesystemPanel FilePanel;
        private TilesetEditPanel TilesetPanel;
        private PaletteEditPanel PalettePanel;

        public MainWindow(string workingDir, string ptmExe)
        {
            InitializeComponent();
            Size = new Size(980, 595);
            MinimumSize = Size;

            WorkingDir = workingDir;
            PtmExe = ptmExe;

            ProgramPanel = new ProgramEditPanel();
            ProgramPanel.Parent = CenterPanel;
            ProgramPanel.Dock = DockStyle.Fill;

            FilePanel = new FilesystemPanel(this);
            FilePanel.Parent = TopRightPanel;
            FilePanel.Dock = DockStyle.Fill;

            TilesetPanel = new TilesetEditPanel();
            TilesetPanel.Parent = TopLeftPanel;
            TilesetPanel.Dock = DockStyle.Fill;

            PalettePanel = new PaletteEditPanel();
            PalettePanel.Parent = BtmLeftPanel;
            PalettePanel.Dock = DockStyle.Fill;

            if (!File.Exists(MainProgramFile))
                File.Create(MainProgramFile).Close();

            LoadFile(MainProgramFile);

            //ResizeEnd += MainWindow_ResizeEnd;
        }

        private void MainWindow_ResizeEnd(object sender, EventArgs e)
        {
            Text = Size.ToString();
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
            RunProgram();
        }

        public void RunProgram()
        {
            ProgramPanel.SaveFile();
            Process.Start(PtmExe, ProgramFile);
        }

        public void LoadFile(string file)
        {
            string ext = Path.GetExtension(file).ToLower();
            
            if (ext == ".ptm")
            {
                ProgramPanel.LoadFile(file);
                ProgramFile = file;
                Text = "PTM Studio - " + FilesystemPanel.RemoveFilesPrefix(file);
            }
            else if (ext == ".chr")
            {
                TilesetPanel.LoadFile(file);
            }
            else if (ext == ".pal")
            {
                PalettePanel.LoadFile(file);
            }
        }
    }
}
