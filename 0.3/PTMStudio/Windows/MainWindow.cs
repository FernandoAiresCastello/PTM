using PTMStudio.Core;
using PTMStudio.Windows;
using SharpConfig;
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
        private const string AutosavedProgramFile = "USR/TEMP" + KnownFileExtensions.Program;
        private const string SettingsFile = "settings.ini";

		private readonly string WindowTitle = "PTM 0.3";
		private readonly string PtmExe;
		private readonly string BuildTimestamp;
		private readonly ProgramEditPanel ProgramPanel;
        private readonly TilebufferEditPanel TilebufferPanel;
        private readonly FilesystemPanel FilePanel;
        private readonly ProgramLabelsPanel LabelsPanel;
        private readonly TilesetEditPanel TilesetPanel;
        private readonly PaletteEditPanel PalettePanel;
        private readonly TileRegisterPanel TileRegPanel;
        
        private HelpWindow HelpWindow;
        private string ProgramFile;

        private class ChangeTracker
        {
            public bool Program { set; get; } = false;
            public bool Tileset { set; get; } = false;
            public bool Palette { set; get; } = false;
            public bool TileBuffer { set; get; } = false;
        }
        private ChangeTracker Changes { get; set; }

        public bool ShouldRestart { get; private set; } = false;

        public MainWindow(string ptmExe)
        {
            InitializeComponent();
            ShouldRestart = false;
			BuildTimestamp = File.ReadAllText("build_timestamp").Trim();

			Text = WindowTitle;
			Size = new Size(1024, 730);
            MinimumSize = Size;
			PtmExe = ptmExe;
			KeyPreview = true;

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

            LoadFile(AutosavedProgramFile);

            FormClosing += MainWindow_FormClosing;
            //Resize += (s, e) => { Text = Size.ToString(); };

            LoadSettings();
		}

		private void LoadSettings()
        {
            if (!File.Exists(SettingsFile))
                return;

            Configuration config = Configuration.LoadFromFile(SettingsFile);

            if (config.Contains("PTM", "INITIAL_PROJECT"))
            {
                string initialProject = config["PTM"]["INITIAL_PROJECT"].StringValue;
                LoadProject(Path.Combine(Filesystem.UserRootDirName, initialProject));
            }
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
            if (e.Cancel) { ShouldRestart = false; return; }

            if (Changes.Tileset)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Tileset");

                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    TilesetPanel.SaveFile();
            }
			if (e.Cancel) { ShouldRestart = false; return; }

			if (Changes.Palette)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Palette");

                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    PalettePanel.SaveFile();
            }
			if (e.Cancel) { ShouldRestart = false; return; }

			if (Changes.TileBuffer)
            {
                DialogResult result = ConfirmModifiedButNotSaved("Tilebuffer");

                if (result == DialogResult.Cancel)
                    e.Cancel = true;
                else if (result == DialogResult.Yes)
                    TilebufferPanel.SaveFile();
            }
			if (e.Cancel) { ShouldRestart = false; return; }
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

        public void LoadFile(string file)
        {
            string ext = Path.GetExtension(file).ToUpper();

            if (ext == KnownFileExtensions.Program)
            {
                if (Changes.Program)
                {
                    DialogResult result = ConfirmModifiedButNotSaved("Program");
                    if (result == DialogResult.Cancel)
                        return;
                    else if (result == DialogResult.Yes)
                        ProgramPanel.SaveFile();
                }

                ProgramPanel.LoadFile(file, true);
            }
            else if (ext == KnownFileExtensions.Charset)
            {
				if (Changes.Tileset)
				{
					DialogResult result = ConfirmModifiedButNotSaved("Tileset");
					if (result == DialogResult.Cancel)
						return;
					else if (result == DialogResult.Yes)
						TilesetPanel.SaveFile();
				}

				TilesetPanel.LoadFile(file);
            }
            else if (ext == KnownFileExtensions.Palette)
            {
				if (Changes.Palette)
				{
					DialogResult result = ConfirmModifiedButNotSaved("Palette");
					if (result == DialogResult.Cancel)
						return;
					else if (result == DialogResult.Yes)
						PalettePanel.SaveFile();
				}

				PalettePanel.LoadFile(file);
            }
            else if (ext == KnownFileExtensions.TileBuffer)
            {
				if (Changes.TileBuffer)
				{
					DialogResult result = ConfirmModifiedButNotSaved("Tilebuffer");
					if (result == DialogResult.Cancel)
						return;
					else if (result == DialogResult.Yes)
						ProgramPanel.SaveFile();
				}

				TilebufferPanel.LoadFile(file, true);
            }
			else if (ext == KnownFileExtensions.Data)
            {
                RecordFile recFile = new RecordFile();
                recFile.Load(file);

                RecordFileWindow wnd = new RecordFileWindow(
                    Filesystem.RemoveAbsoluteRootAndNormalizePath(file), recFile.GetLoadedData());

                wnd.ShowDialog(this);
            }
			else if (ext == KnownFileExtensions.Project)
            {
                if (Changes.Program || Changes.Palette || Changes.Tileset || Changes.TileBuffer)
                {
                    if (!Confirm("There are unsaved changes. Continue without saving?"))
                        return;
				}

                LoadProject(file);
            }
			else if (ext == KnownFileExtensions.PublishProfile)
            {
				PublishWindow wnd = new PublishWindow();
                wnd.LoadProfile(file);
				wnd.ShowDialog(this);
			}
			else
            {
                Warning("Unsupported file format");
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

            Size = new Size(1207, 730);
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
            new AboutWindow(BuildTimestamp).ShowDialog(this);
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

        private void BtnSaveProject_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog
            {
                InitialDirectory = Filesystem.UserRoot,
                DefaultExt = KnownFileExtensions.Project,
				Filter = "PTM Project File (*.PROJ)|*.PROJ"
			};

            if (dialog.ShowDialog() != DialogResult.OK)
                return;

            List<string> lines = new List<string>
            {
                ProgramPanel.LoadedFile,
                TilesetPanel.Filename,
                PalettePanel.Filename,
                TilebufferPanel.Filename
            };

            File.WriteAllLines(dialog.FileName, lines);

            FilePanel.UpdateFileList();
            AlertOnStatusBar("Project saved to: " + dialog.FileName, 2);
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
                Filter = "PTM Project File (*.PROJ)|*.PROJ"
			};

            if (dialog.ShowDialog() != DialogResult.OK)
                return;

            LoadProject(dialog.FileName);
        }

        public void LoadProject(string file)
        {
            try
            {
                var lines = File.ReadAllLines(file);

                if (!string.IsNullOrWhiteSpace(lines[0]))
                    ProgramPanel.LoadFile(lines[0], true);
                if (!string.IsNullOrWhiteSpace(lines[1]))
                    TilesetPanel.LoadFile(lines[1]);
                if (!string.IsNullOrWhiteSpace(lines[2]))
                    PalettePanel.LoadFile(lines[2]);
                if (!string.IsNullOrWhiteSpace(lines[3]))
                    TilebufferPanel.LoadFile(lines[3], false);

                AlertOnStatusBar("Project loaded from: " + file, 2);
            }
            catch (Exception ex)
            {
                Error("Error loading project.", ex);
            }
        }

        public void NewProgramLoaded(string file)
        {
            ProgramFile = file;
            UpdateLabelsPanel();
        }

        public void UpdateLabelsPanel()
        {
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

        public static void Error(string message, Exception ex = null)
        {
            MessageBox.Show(ex != null ? message + "\n\n" + ex.Message : message, 
                "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static void UnexpectedError(string message)
        {
            MessageBox.Show(message, "Unexpected error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

		public void SaveProgramFile()
		{
			ProgramPanel.SaveFile();
		}

		public void CreateNewProgramFile()
        {
			SimpleTextInputDialog dialog = 
                new SimpleTextInputDialog("Create new program", "Enter program name:")
			{
				UppercaseOnly = true
			};

			if (dialog.ShowDialog(this) == DialogResult.OK)
			{
				string programName = dialog.Text.ToUpper();
				if (string.IsNullOrWhiteSpace(programName))
					return;

				if (!programName.EndsWith(KnownFileExtensions.Program))
					programName += KnownFileExtensions.Program;

				string path = Filesystem.GetAbsoluteUserFilePath(programName);
				File.Create(path).Close();
				FilePanel.UpdateFileList();
				ProgramPanel.LoadFile(path, true);
			}
		}

		private void BtnRelaunchIde_Click(object sender, EventArgs e)
		{
            ShouldRestart = true;
            Close();
		}

		private void BtnSaveProgram_Click(object sender, EventArgs e)
		{
            SaveProgramFile();
		}

		private void BtnPublish_Click(object sender, EventArgs e)
		{
            PublishWindow wnd = new PublishWindow();
            wnd.ShowDialog(this);
		}

		private void BtnBugReport_Click(object sender, EventArgs e)
		{
            Process.Start("https://github.com/FernandoAiresCastello/PTM/issues");
		}

		private void BtnSearchInProgram_Click(object sender, EventArgs e)
		{
            ProgramPanel.ActivateSearch();
		}

		private void BtnEditSettingsFile_Click(object sender, EventArgs e)
		{
            if (!File.Exists(SettingsFile))
                File.Create(SettingsFile).Close();

            Process.Start(SettingsFile);
		}
	}
}
