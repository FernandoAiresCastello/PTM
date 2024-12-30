﻿using ScintillaNET;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio
{
	public partial class ProgramEditPanel : UserControl
    {
        private MainWindow MainWindow;
        private Scintilla Scintilla;
        
        public string LoadedFile { get; private set; }

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
            Scintilla.KeyDown += Scintilla_KeyDown;

            SetFont("Consolas");
            SetFontSize(9);
        }

        private void Scintilla_KeyDown(object sender, KeyEventArgs e)
        {
            MainWindow.ProgramChanged(true);
        }

        public void LoadFile(string file)
        {
            Scintilla.Text = File.ReadAllText(file);
            LoadedFile = file;
            MainWindow.ShowProgramEditor();
            MainWindow.ProgramChanged(false);
            MainWindow.NewProgramLoaded(file);
        }

        public void SaveFile()
        {
            File.WriteAllText(LoadedFile, Scintilla.Text);
            MainWindow.ProgramChanged(false);
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
    }
}
