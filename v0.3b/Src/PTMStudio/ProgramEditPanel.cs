using ScintillaNET;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTMStudio
{
    public partial class ProgramEditPanel : UserControl
    {
        private MainWindow MainWindow;
        private Scintilla Scintilla;
        private string LoadedFile = "";

        private ProgramEditPanel()
        {
            InitializeComponent();
        }

        public ProgramEditPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Scintilla = new Scintilla();
            Scintilla.Parent = ScintillaPanel;
            Scintilla.Dock = DockStyle.Fill;
            Scintilla.BorderStyle = BorderStyle.Fixed3D;
            Scintilla.HScrollBar = true;
            Scintilla.VScrollBar = true;
            Scintilla.Margins[0].Width = 40;
        }

        public void LoadFile(string file)
        {
            Scintilla.Text = File.ReadAllText(file);
            LoadedFile = file;
            MainWindow.ShowProgramEditor();
        }

        public void SaveFile()
        {
            File.WriteAllText(LoadedFile, Scintilla.Text);
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
    }
}
