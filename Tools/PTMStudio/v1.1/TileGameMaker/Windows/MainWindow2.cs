using ScintillaNET;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using TileGameLib.Graphics;
using TileGameMaker.MapEditorElements;
using TileGameMaker.Panels;
using TileGameMaker.Properties;
using TileGameMaker.PTMLExporters;
using TileGameMaker.Util;

namespace TileGameMaker.Windows
{
    public partial class MainWindow2 : Form
    {
        private Tileset Tileset;
        private TilePickerPanel TilesetPanel;
        private Palette Palette;
        private ColorPickerPanel PalettePanel;
        private ProgramPanel ProgramPanel;
        private Scintilla Scintilla;
        private UserSettings Settings;
        private string PtmExePath;
        private string ProgramFilePath;

        public MainWindow2()
        {
            InitializeComponent();
            Icon = Global.WindowIcon;
            Settings = new UserSettings();
            PtmExePath = Settings.Get("ptm_exe");
            if (string.IsNullOrWhiteSpace(PtmExePath))
                PtmExePath = "PTM.exe";

            Size = new System.Drawing.Size(1024, 600);

            Tileset = new Tileset();
            TilesetPanel = new TilePickerPanel(Tileset);
            TilesetPanel.Parent = PnlTopLeft;
            TilesetPanel.Dock = DockStyle.Fill;

            Palette = new Palette();
            PalettePanel = new ColorPickerPanel(Palette);
            PalettePanel.Parent = PnlBtmLeft;
            PalettePanel.Dock = DockStyle.Fill;

            Scintilla = new Scintilla();

            ProgramPanel = new ProgramPanel(Scintilla);
            ProgramPanel.Parent = PnlProgram;
            ProgramPanel.Dock = DockStyle.Fill;
        }

        private void BtnRun_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(ProgramFilePath))
            {
                if (!ShowSaveProgramFileDialog())
                    return;
            }
            else
            {
                SaveProgramFile(ProgramFilePath);
            }

            Process.Start(PtmExePath, ProgramFilePath);
        }

        private bool ShowSaveProgramFileDialog()
        {
            SaveFileDialog dialog = new SaveFileDialog();

            if (dialog.ShowDialog(this) == DialogResult.OK)
            {
                SaveProgramFile(dialog.FileName);
                return true;
            }

            return false;
        }

        private void SaveProgramFile(string path)
        {
            ProgramFilePath = path;
            File.WriteAllText(path, Scintilla.Text);
            string programName = GetProgramFileNameWithoutExtension();
            string folder = GetProgramFileDirectory();
            ProjectExporter.ExportGraphics(programName, folder, Tileset, Palette);
        }

        private void BtnLoadProgram_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();

            if (dialog.ShowDialog(this) == DialogResult.OK)
            {
                LoadProgramFile(dialog.FileName);
            }
        }

        private void LoadProgramFile(string path)
        {
            ProgramFilePath = path;
            Scintilla.Text = File.ReadAllText(path);
        }

        private string GetProgramFileDirectory()
        {
            return Path.GetDirectoryName(ProgramFilePath);
        }

        private string GetProgramFileNameWithoutExtension()
        {
            return Path.GetFileNameWithoutExtension(ProgramFilePath);
        }

        private void BtnSaveProgram_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(ProgramFilePath))
            {
                if (!ShowSaveProgramFileDialog())
                    return;
            }
            else
            {
                SaveProgramFile(ProgramFilePath);
            }
        }
    }
}
