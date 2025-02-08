using PTMStudio.Windows;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using TileGameLib.GameElements;
using TileGameLib.Graphics;
using Timer = System.Windows.Forms.Timer;

namespace PTMStudio
{
	public partial class MainWindow : Form
    {
        private const string ProgramFileExt = ".PTM";
        private const string AutosavedProgramFile = "ROOT/TEMP" + ProgramFileExt;
        
        private readonly string PtmExe;
        private readonly ProgramEditPanel ProgramPanel;
        private readonly TilebufferEditPanel TilebufferPanel;
        private readonly FilesystemPanel FilePanel;
        private readonly ProgramLabelsPanel LabelsPanel;
        private readonly TilesetEditPanel TilesetPanel;
        private readonly PaletteEditPanel PalettePanel;
        private readonly TileRegisterPanel TileRegPanel;
        
        private HelpWindow HelpWindow;
        private string ProjectFile;
        private string ProgramFile;

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

            Size = new Size(1024, 730);
            MinimumSize = Size;
            PtmExe = ptmExe;

			Changes = new ChangeTracker();
			UpdateChangesLabel();

			ProgramPanel = new ProgramEditPanel(this)
            {
                Parent = CenterBottomPanel,
                Dock = DockStyle.Fill
            };

            FilePanel = new FilesystemPanel(this)
            {
                Parent = TopRightPanel,
                Dock = DockStyle.Fill
            };

            LabelsPanel = new ProgramLabelsPanel(this)
            {
                Parent = BtmRightPanel,
                Dock = DockStyle.Fill
            };

            TilesetPanel = new TilesetEditPanel(this)
            {
                Parent = TopLeftPanel,
                Dock = DockStyle.Fill
            };

            PalettePanel = new PaletteEditPanel(this)
            {
                Parent = BtmLeftPanel,
                Dock = DockStyle.Fill
            };

			PalettePanel.LoadFile(Filesystem.DefaultPaletteFile);
			TilesetPanel.LoadFile(Filesystem.DefaultTilesetFile);

			TilebufferPanel = new TilebufferEditPanel(this,
                TilesetPanel.Tileset, PalettePanel.Palette)
            {
                Parent = CenterBottomPanel,
                Dock = DockStyle.Fill,
                Visible = false
            };

            TileRegPanel = new TileRegisterPanel(this,
                TilesetPanel.Tileset, PalettePanel.Palette)
            {
                Parent = BtmRightPanel,
                Dock = DockStyle.Fill,
                Visible = false
            };

            if (!File.Exists(AutosavedProgramFile))
            {
                File.Create(AutosavedProgramFile).Close();
				FilePanel.UpdateFileList();
			}

            LoadProgramFile(AutosavedProgramFile);

            FormClosing += MainWindow_FormClosing;
        }

		private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (Changes.Program)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Program");
                
                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    ProgramPanel.SaveFile();
            }
            if (e.Cancel) return;

            if (Changes.Tileset)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Tileset");

                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    TilesetPanel.SaveFile();
            }
            if (e.Cancel) return;

            if (Changes.Palette)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Palette");

                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    PalettePanel.SaveFile();
            }
            if (e.Cancel) return;

            if (Changes.TileBuffer)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Tilebuffer");

                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    TilebufferPanel.SaveFile();
            }
            if (e.Cancel) return;
        }

        private void BtnRun_Click(object sender, EventArgs e)
        {
            RunProgram();
        }

        private void BtnRunEmpty_Click(object sender, EventArgs e)
        {
            Process.Start(PtmExe);
        }

        public void RunProgram()
        {
            ProgramPanel.SaveFile();
			FilePanel.UpdateFileList();
			Process.Start(PtmExe, ProgramFile);
        }

        public void LoadProgramFile(string file)
        {
            if (Changes.Program)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Program");
                if (result == DialogResult.Cancel)
                    return;
                else if (result == DialogResult.Yes)
                    ProgramPanel.SaveFile();
            }

            string ext = Path.GetExtension(file).ToUpper();
            
            if (ext == ".PTM")
                ProgramPanel.LoadFile(file);
            else if (ext == ".CHR")
                TilesetPanel.LoadFile(file);
            else if (ext == ".PAL")
                PalettePanel.LoadFile(file);
            else if (ext == ".BUF")
                TilebufferPanel.LoadFile(file);
            else if (ext == ".PTMS")
                LoadProject(file);
            else
                Warning("Unsupported file format");
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

		public Tile GetTileRegisterFrame()
        {
            return TileRegPanel.TileRegisterFrame;
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
                "PTM - Programmable Tile Machine\n\nVersion 0.4\n\n" + 
                "(C) 2023-2025 Developed by Fernando Aires Castello\n\n" +
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
                LbChanges.Text = "";
            else
                LbChanges.Text = "Unsaved data: " + string.Join(", ", entries);
        }

        private void AlertOnStatusBar(string msg, int seconds)
        {
            string prevText = LbChanges.Text;
            LbChanges.Text = msg;

			Timer timer = new Timer
			{
				Interval = seconds * 1000,
				Tag = prevText
			};

			timer.Tick += Timer_Tick;
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
                SaveFileDialog dialog = new SaveFileDialog
                {
                    InitialDirectory = Filesystem.UserRoot,
                    Filter = "PTM Project File (*.PTMS)|*.PTMS"
                };
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
            OpenFileDialog dialog = new OpenFileDialog
            {
                InitialDirectory = Filesystem.UserRoot,
                Filter = "PTM Project File (*.PTMS)|*.PTMS"
            };

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
            Text = "PTM 0.4";

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

        private static DialogResult ConfirmModifiedButNotSaved(string what)
        {
            return YesNoCancel("Confirm", what + " is modified and not yet saved. Save now?");
        }

        public static DialogResult YesNoCancel(string title, string message)
        {
            return MessageBox.Show(message, title,
                MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
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
            CreateNewProgramFile();
        }

        public void CreateNewProgramFile()
        {
			SimpleTextInputDialog dialog = new
				SimpleTextInputDialog("Create new program", "Enter program name:")
			{
				UppercaseOnly = true
			};

			if (dialog.ShowDialog(this) == DialogResult.OK)
			{
				string programName = dialog.Text.ToUpper();
				if (string.IsNullOrWhiteSpace(programName))
					return;

				if (!programName.EndsWith(ProgramFileExt))
					programName += ProgramFileExt;

				string path = Filesystem.GetAbsoluteUserFilePath(programName);
				File.Create(path).Close();
				FilePanel.UpdateFileList();
				ProgramPanel.LoadFile(path);
			}
		}
    }
}
