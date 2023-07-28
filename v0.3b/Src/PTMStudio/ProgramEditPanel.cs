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
        private Scintilla Scintilla;
        private string LoadedFile = "";

        public ProgramEditPanel()
        {
            InitializeComponent();

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
        }

        public void SaveFile()
        {
            File.WriteAllText(LoadedFile, Scintilla.Text);
        }
    }
}
