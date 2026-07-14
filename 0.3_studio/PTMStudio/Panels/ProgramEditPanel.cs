using PTMStudio.Core;
using PTMStudio.Windows;
using ScintillaNET;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace PTMStudio
{
	public partial class ProgramEditPanel : UserControl
    {
        private readonly MainWindow MainWindow;
        private readonly Scintilla Scintilla;
        
        public string LoadedFile { get; private set; }

        private ProgramEditPanel()
        {
            InitializeComponent();
        }

        public ProgramEditPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Scintilla = new Scintilla
            {
                Parent = ScintillaPanel,
                Dock = DockStyle.Fill,
                BorderStyle = BorderStyle.None,
                HScrollBar = true,
                VScrollBar = true,
                Lexer = Lexer.Cpp,
            };

			Scintilla.Margins[0].Width = 40;
            Scintilla.KeyDown += Scintilla_KeyDown;
            Scintilla.SetSelectionBackColor(true, SystemColors.Highlight);
			Scintilla.SetSelectionForeColor(true, SystemColors.HighlightText);

            Scintilla.SetKeywords(0, GetPtmlCommands());

			Scintilla.Styles[Style.Cpp.Default].ForeColor = Color.Black;
			Scintilla.Styles[Style.Cpp.Word].ForeColor = Color.Blue;
			Scintilla.Styles[Style.Cpp.String].ForeColor = Color.Green;
			Scintilla.Styles[Style.Cpp.Number].ForeColor = Color.Red;
			Scintilla.Styles[Style.Cpp.Character].ForeColor = Color.Red;
			Scintilla.Styles[Style.Cpp.Preprocessor].ForeColor = Color.Gray;

			SetFont("Consolas");
            SetFontSize(8);

            LbFilename.Text = GlobalConstants.Unsaved;
			SearchPanel.Visible = false;
			TxtSearch.KeyDown += TxtSearch_KeyDown;
		}

        private string GetPtmlCommands()
        {
            StringBuilder commands = new StringBuilder();
            var files = Directory.EnumerateFiles(Path.Combine(Filesystem.CurrentDir, "HELP"));

			foreach (var path in files)
            {
                if (!path.EndsWith(".html"))
                    continue;

                string filename = Path.GetFileNameWithoutExtension(path);
                commands.Append(filename.ToUpper().Trim() + " ");
				commands.Append(filename.ToLower().Trim() + " ");
			}

			return commands.ToString().Trim();
        }

		private void TxtSearch_KeyDown(object sender, KeyEventArgs e)
		{
            if (e.KeyCode == Keys.Enter)
            {
				e.Handled = true;
				Search();
            }
		}

		private void Scintilla_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Control || e.KeyCode == Keys.Shift || e.KeyCode == Keys.Alt || 
                e.KeyCode == Keys.Home || e.KeyCode == Keys.End || e.KeyCode == Keys.Insert || 
                e.KeyCode == Keys.PageUp || e.KeyCode == Keys.PageDown || e.KeyCode == Keys.CapsLock)

            MainWindow.ProgramChanged(true);
        }

        public void LoadFile(string file, bool showPanel)
        {
            Scintilla.Text = File.ReadAllText(file);
            LoadedFile = file;
			LbFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(file);
            MainWindow.ProgramChanged(false);
            MainWindow.NewProgramLoaded(file);

            if (showPanel)
			    MainWindow.ShowProgramEditor();
		}

        public void SaveFile()
        {
            if (string.IsNullOrWhiteSpace(LoadedFile))
            {
                SimpleTextInputDialog dialog = new SimpleTextInputDialog("Save program file", "Enter file name:")
                {
                    UppercaseOnly = true
                };

                if (dialog.ShowDialog(this) == DialogResult.OK)
                    LoadedFile = dialog.Text.ToUpper();
                else
                    return;

                LoadedFile = Filesystem.GetUserFilePath(LoadedFile);
                if (!LoadedFile.EndsWith(KnownFileExtensions.Program))
                    LoadedFile += KnownFileExtensions.Program;

				File.WriteAllText(LoadedFile, Scintilla.Text);
				MainWindow.ProgramChanged(false);
				MainWindow.LoadFile(LoadedFile);
            }
            else
            {
                File.WriteAllText(LoadedFile, Scintilla.Text);
                MainWindow.ProgramChanged(false);
                MainWindow.UpdateLabelsPanel();
            }

            MainWindow.CopyFileFromUsrFolderToProjectFolder(LoadedFile);
		}

        private void BtnRun_Click(object sender, EventArgs e)
        {
            MainWindow.RunProgram();
        }

        public List<string> GetProgramSource()
        {
            List<string> program = new List<string>();
            foreach (var line in Scintilla.Lines)
                program.Add(line.Text);

            return program;
        }

        public void GoToLabel(string label)
        {
            int lineNumber = -1;

            foreach (var rawLine in Scintilla.Lines)
            {
                lineNumber++;
                string line = rawLine.Text.Trim();
                if (string.IsNullOrEmpty(line) || !line.EndsWith(":"))
                    continue;

                string curLabel = line.Substring(0, line.Length - 1);
                if (curLabel == label)
                {
                    Scintilla.FirstVisibleLine = lineNumber;
                    return;
                }
            }
        }

        public void SetFont(string name)
        {
            for (int i = 0; i < Scintilla.Styles.Count; i++)
                Scintilla.Styles[i].Font = name;
        }

        public void SetFontSize(int size)
        {
            for (int i = 0; i < Scintilla.Styles.Count; i++)
                Scintilla.Styles[i].Size = size;
        }

        public void IncreaseFontSize()
        {
            for (int i = 0; i < Scintilla.Styles.Count; i++)
                Scintilla.Styles[i].Size++;
        }

        public void DecreaseFontSize()
        {
            for (int i = 0; i < Scintilla.Styles.Count; i++)
                Scintilla.Styles[i].Size--;
        }

        private void BtnIncFont_Click(object sender, EventArgs e)
        {
            IncreaseFontSize();
        }

        private void BtnDecFont_Click(object sender, EventArgs e)
        {
            DecreaseFontSize();
        }

		private void BtnNew_Click(object sender, EventArgs e)
		{
            MainWindow.CreateNewProgramFile();
		}

		private void BtnSave_Click(object sender, EventArgs e)
		{
            MainWindow.SaveProgramFile();
		}

		private void BtnActivateSearch_Click(object sender, EventArgs e)
		{
            ActivateSearch();
		}

        public void ActivateSearch()
        {
			SearchPanel.Visible = !SearchPanel.Visible;
			if (SearchPanel.Visible)
				TxtSearch.Focus();
		}

		private void BtnSearch_Click(object sender, EventArgs e)
		{
            Search();
		}

        private void Search()
        {
            try
            {
                string substring = TxtSearch.Text;

                Scintilla.TargetStart = Scintilla.CurrentPosition;
                Scintilla.TargetEnd = Scintilla.TextLength;

                int pos = Scintilla.SearchInTarget(substring);
                if (pos < 0)
                    MainWindow.Warning("Text not found starting from current cursor position.");
                else
                    Scintilla.SetSel(pos, pos + substring.Length);
            }
            catch (Exception ex)
            {
                MainWindow.Error("An error occurred during search.", ex);
            }
		}
	}
}
