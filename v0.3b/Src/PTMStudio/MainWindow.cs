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
using TileGameLib.GameElements;

namespace PTMStudio
{
    public partial class MainWindow : Form
    {
        public string WorkingDir { get; private set; }
        private string PtmExe;
        private string ProgramFile = "";
        private readonly string MainProgramFile = "files/main.ptm";
        private ProgramEditPanel ProgramPanel;
        private TilebufferEditPanel TilebufferPanel;
        private FilesystemPanel FilePanel;
        private ProgramLabelsPanel LabelsPanel;
        private TilesetEditPanel TilesetPanel;
        private PaletteEditPanel PalettePanel;
        private TileRegisterPanel TileRegPanel;

        public MainWindow(string workingDir, string ptmExe)
        {
            InitializeComponent();
            Size = new Size(1024, 605);
            MinimumSize = Size;

            WorkingDir = workingDir;
            PtmExe = ptmExe;

            ProgramPanel = new ProgramEditPanel(this);
            ProgramPanel.Parent = CenterPanel;
            ProgramPanel.Dock = DockStyle.Fill;

            FilePanel = new FilesystemPanel(this);
            FilePanel.Parent = TopRightPanel;
            FilePanel.Dock = DockStyle.Fill;

            LabelsPanel = new ProgramLabelsPanel(this);
            LabelsPanel.Parent = BtmRightPanel;
            LabelsPanel.Dock = DockStyle.Fill;

            TilesetPanel = new TilesetEditPanel(this);
            TilesetPanel.Parent = TopLeftPanel;
            TilesetPanel.Dock = DockStyle.Fill;

            PalettePanel = new PaletteEditPanel(this);
            PalettePanel.Parent = BtmLeftPanel;
            PalettePanel.Dock = DockStyle.Fill;

            TilebufferPanel = new TilebufferEditPanel(this, 
                TilesetPanel.Tileset, PalettePanel.Palette);
            TilebufferPanel.Parent = CenterPanel;
            TilebufferPanel.Dock = DockStyle.Fill;
            TilebufferPanel.Visible = false;

            TileRegPanel = new TileRegisterPanel(this, 
                TilesetPanel.Tileset, PalettePanel.Palette);
            TileRegPanel.Parent = BtmRightPanel;
            TileRegPanel.Dock = DockStyle.Fill;
            TileRegPanel.Visible = false;

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
                LabelsPanel.UpdateLabels();
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

        public void UpdateFilePanel()
        {
            FilePanel.UpdateFileList();
        }

        public List<string> GetProgramSource()
        {
            return ProgramPanel.GetProgramSource();
        }

        public void GoToLabel(string label)
        {
            ProgramPanel.GoToLabel(label);
        }

        private void BtnViewPrgEdit_Click(object sender, EventArgs e)
        {
            ShowProgramEditor();
        }

        private void BtnViewTilebufEdit_Click(object sender, EventArgs e)
        {
            ShowTilebufferEditor();
        }

        public void UpdateTilebufferEditorDisplay()
        {
            TilebufferPanel.UpdateDisplay();
        }

        public void UpdateTileRegisterPanelDisplay()
        {
            TileRegPanel.UpdateDisplay();
        }

        private void ShowProgramEditor()
        {
            ProgramPanel.Visible = true;
            LabelsPanel.Visible = true;
            TilebufferPanel.Visible = false;
            TileRegPanel.Visible = false;
            ProgramPanel.Focus();
        }

        private void ShowTilebufferEditor()
        {
            TilebufferPanel.Visible = true;
            TileRegPanel.Visible = true;
            ProgramPanel.Visible = false;
            LabelsPanel.Visible = false;
        }
        
        private void BtnAlternateEditor_Click(object sender, EventArgs e)
        {
            if (ProgramPanel.Visible)
                ShowTilebufferEditor();
            else
                ShowProgramEditor();
        }

        public void SetTileRegisterForeColor(int index)
        {
            TileRegPanel.TileRegisterFrame.ForeColor = index;
            TileRegPanel.UpdateDisplay();
        }

        public void SetTileRegisterBackColor(int index)
        {
            TileRegPanel.TileRegisterFrame.BackColor = index;
            TileRegPanel.UpdateDisplay();
        }

        public void SetTileRegisterTile(int index)
        {
            TileRegPanel.TileRegisterFrame.Index = index;
            TileRegPanel.UpdateDisplay();
        }

        private GameObject CachedTileRegister;

        public GameObject GetTileRegister()
        {
            if (CachedTileRegister == null)
                CachedTileRegister = TileRegPanel.GetTileRegister();

            return CachedTileRegister;
        }

        public void CacheTileRegister()
        {
            if (TileRegPanel != null)
                CachedTileRegister = TileRegPanel.GetTileRegister();
        }

        public void SetTileRegister(GameObject tile)
        {
            TileRegPanel.SetTileRegister(tile);
            CacheTileRegister();
        }
    }
}
