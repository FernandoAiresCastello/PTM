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
    public partial class TilesetEditPanel : UserControl
    {
        private TiledDisplay Display;

        public TilesetEditPanel()
        {
            InitializeComponent();
            Display = new TiledDisplay(PnlTileset, 8, 8, 3);
            Display.Graphics.Palette.Clear();
            Display.Graphics.Clear(1);
            Display.ShowGrid = true;
        }
    }
}
