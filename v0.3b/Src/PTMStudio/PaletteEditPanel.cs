using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TileGameLib.Components;

namespace PTMStudio
{
    public partial class PaletteEditPanel : UserControl
    {
        private TiledDisplay Display;

        public PaletteEditPanel()
        {
            InitializeComponent();
            Display = new TiledDisplay(PnlPalette, 8, 8, 3);
            Display.Graphics.Palette.Clear();
            Display.Graphics.Clear(1);
            Display.ShowGrid = true;
        }
    }
}
