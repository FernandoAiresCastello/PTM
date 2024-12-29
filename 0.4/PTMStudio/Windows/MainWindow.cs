using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using TileGameLib.GameElements;
using Timer = System.Windows.Forms.Timer;

namespace PTMStudio
{
	public partial class MainWindow : Form
    {
        private string PtmExe;
        private string ProgramFile = "";
        private readonly string MainProgramFile = "root/TEMP.PTM";
        private ProgramEditPanel ProgramPanel;
        private TilebufferEditPanel TilebufferPanel;
        private FilesystemPanel FilePanel;
        private ProgramLabelsPanel LabelsPanel;
        private TilesetEditPanel TilesetPanel;
        private PaletteEditPanel PalettePanel;
        private TileRegisterPanel TileRegPanel;
        private HelpWindow HelpWindow;
        private string ProjectFile;

        private class ChangeTracker
        {
            public bool Program { set; get; } = false;
            public bool Tileset { set; get; } = false;
            public bool Palette { set; get; } = false;
            public bool TileBuffer { set; get; } = false;
        }
        private ChangeTracker Changes { get; set; }

        public MainWindow(string ptmExe)
        {
            InitializeComponent();
            Size = new Size(1024, 605);
            MinimumSize = Size;
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

            Changes = new ChangeTracker();
            UpdateChangesLabel();
            LoadFile(MainProgramFile);
        }

        private void MainWindow_ResizeEnd(object sender, EventArgs e)
        {
            Text = Size.ToString();
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
            string ext = Path.GetExtension(file).ToUpper();
            
            if (ext == ".PTM")
            {
                ProgramPanel.LoadFile(file);
            }
            else if (ext == ".CHR")
            {
                TilesetPanel.LoadFile(file);
            }
            else if (ext == ".PAL")
            {
                PalettePanel.LoadFile(file);
            }
            else if (ext == ".BUF")
            {
                TilebufferPanel.LoadFile(file);
            }
            else if (ext == ".PTMS")
            {
                LoadProject(file);
            }
            else
            {
                MainWindow.Warning("Unsupported file format");
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

        public void ShowProgramEditor()
        {
            ProgramPanel.Visible = true;
            LabelsPanel.Visible = true;
            TilebufferPanel.Visible = false;
            TileRegPanel.Visible = false;
            ProgramPanel.Focus();
        }

        public void ShowTilebufferEditor()
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

        private void BtnQuit_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void BtnHelp_Click(object sender, EventArgs e)
        {
            if (HelpWindow == null || HelpWindow.IsDisposed)
                HelpWindow = new HelpWindow();

            if (!HelpWindow.Visible)
                HelpWindow.Show();

            HelpWindow.WindowState = FormWindowState.Normal;
            HelpWindow.BringToFront();
        }

        private void BtnAbout_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                "PTM\n\nVersion 0.4\n\n(C) 2023-2024 Developed by Fernando Aires Castello\n\n" +
                "https://fernandoairescastello.itch.io/ptm\n" +
                "https://github.com/FernandoAiresCastello/PTM",
                "About", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void BtnSaveEverything_Click(object sender, EventArgs e)
        {
            ProgramPanel.SaveFile();
            TilesetPanel.SaveFile();
            PalettePanel.SaveFile();
            TilebufferPanel.SaveFile();
        }

        public void ProgramChanged(bool changed)
        {
            Changes.Program = changed;
            UpdateChangesLabel();
        }

        public void TilesetChanged(bool changed)
        {
            Changes.Tileset = changed;
            UpdateChangesLabel();
        }

        public void PaletteChanged(bool changed)
        {
            Changes.Palette = changed;
            UpdateChangesLabel();
        }

        public void TilebufferChanged(bool changed)
        {
            if (Changes != null)
            {
                Changes.TileBuffer = changed;
                UpdateChangesLabel();
            }
        }

        private void UpdateChangesLabel()
        {
            List<string> entries = new List<string>();

            if (Changes.Program)
                entries.Add("Program");
            if (Changes.Tileset)
                entries.Add("Tileset");
            if (Changes.Palette)
                entries.Add("Palette");
            if (Changes.TileBuffer)
                entries.Add("Tilebuffer");

            if (entries.Count == 0)
            {
                LbChanges.Text = "";
            }
            else
            {
                LbChanges.Text = "Unsaved data: " + string.Join(", ", entries);
            }
        }

        private void AlertOnStatusBar(string msg, int seconds)
        {
            string prevText = LbChanges.Text;

            LbChanges.Text = msg;

            Timer timer = new Timer();
            timer.Interval = seconds * 1000;
            timer.Tick += Timer_Tick;
            timer.Tag = prevText;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            Timer timer = sender as Timer;
            timer.Stop();
            LbChanges.Text = timer.Tag.ToString();
        }

        private void BtnSaveProgram_Click(object sender, EventArgs e)
        {
            ProgramPanel.SaveFile();
        }

        private void BtnSaveProject_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(ProjectFile))
            {
                SaveFileDialog dialog = new SaveFileDialog();
                dialog.InitialDirectory = Path.Combine(Filesystem.AbsoluteRootPath, "files");
                dialog.Filter = "PTM Studio Project File (*.ptms)|*.ptms";
                if (dialog.ShowDialog() == DialogResult.OK)
                    ProjectFile = dialog.FileName;
                else
                    return;
            }

            List<string> lines = new List<string>
            {
                ProgramPanel.LoadedFile,
                TilesetPanel.Filename,
                PalettePanel.Filename,
                TilebufferPanel.Filename
            };

            File.WriteAllLines(ProjectFile, lines);

            FilePanel.UpdateFileList();
            AlertOnStatusBar("Project saved to: " + ProjectFile, 2);
        }

        private void BtnLoadProject_Click(object sender, EventArgs e)
        {
            LoadProject();
        }

        private void LoadProject()
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.InitialDirectory = Path.Combine(Filesystem.AbsoluteRootPath, "files");
            dialog.Filter = "PTM Studio Project File (*.ptms)|*.ptms";
            if (dialog.ShowDialog() != DialogResult.OK)
                return;

            LoadProject(dialog.FileName);
        }

        public void LoadProject(string file)
        {
            ProjectFile = file;

            var lines = File.ReadAllLines(ProjectFile);

            ProgramPanel.LoadFile(lines[0]);
            TilesetPanel.LoadFile(lines[1]);
            PalettePanel.LoadFile(lines[2]);
            TilebufferPanel.LoadFile(lines[3]);

            AlertOnStatusBar("Project loaded from: " + ProjectFile, 2);
        }

        public void NewProgramLoaded(string file)
        {
            ProgramFile = file;
            Text = "PTM Studio - " + 
                Filesystem.RemoveAbsoluteRootAndFilesPrefix(
                Filesystem.NormalizePath(file));

            LabelsPanel.UpdateLabels();
        }

        public static bool Confirm(string message)
        {
            return Confirm("Confirm", message);
        }

        public static bool Confirm(string title, string message)
        {
            DialogResult result = MessageBox.Show(message, title, 
                MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            return result == DialogResult.Yes;
        }

        public static void Warning(string message)
        {
            Warning("Warning", message);
        }

        public static void Warning(string title, string message)
        {
            MessageBox.Show(message, title, MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        public static void FatalError(string message)
        {
            MessageBox.Show(message, "Fatal error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static void UnexpectedError(string message)
        {
            MessageBox.Show(message, "Unexpected error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void BtnNewProgram_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.InitialDirectory = Path.Combine(Filesystem.AbsoluteRootPath, "files");
            dialog.Filter = "PTM Program File (*.ptm)|*.ptm";

            if (dialog.ShowDialog(this) == DialogResult.OK)
            {
                File.Create(dialog.FileName).Close();
                ProgramPanel.LoadFile(dialog.FileName);
            }
        }
    }
}
