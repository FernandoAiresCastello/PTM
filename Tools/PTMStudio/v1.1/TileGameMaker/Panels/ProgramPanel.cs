using ScintillaNET;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TileGameMaker.Panels
{
    public partial class ProgramPanel : UserControl
    {
        private Scintilla Scintilla;

        public ProgramPanel()
        {
            InitializeComponent();
        }

        public ProgramPanel(Scintilla scintilla)
        {
            InitializeComponent();
            Scintilla = scintilla;
            Scintilla.Parent = PnlScintilla;
            Scintilla.Dock = DockStyle.Fill;
            Scintilla.BorderStyle = BorderStyle.Fixed3D;
            Scintilla.HScrollBar = true;
            Scintilla.VScrollBar = true;
            Scintilla.Margins[0].Width = 40;
        }
    }
}
