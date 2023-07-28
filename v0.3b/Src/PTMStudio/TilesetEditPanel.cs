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
using TileGameLib.Components;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public partial class TilesetEditPanel : UserControl
    {
        private TiledDisplay Display;
        private int FirstTile = 0;

        public TilesetEditPanel()
        {
            InitializeComponent();
            
            Display = new TiledDisplay(PnlTileset, 8, 8, 3);
            Display.Graphics.Palette.Clear(2);
            Display.Graphics.Palette.Set(0, 0x000000);
            Display.Graphics.Palette.Set(1, 0xffffff);
            Display.Graphics.Clear(1);
            Display.ShowGrid = true;

            DefaultTileset.Init(Display.Graphics.Tileset);

            UpdateDisplay();
        }

        public void UpdateDisplay()
        {
            Display.Graphics.Clear(1);

            int i = FirstTile;

            for (int y = 0; y < Display.Rows; y++)
            {
                for (int x = 0; x < Display.Cols; x++)
                {
                    if (i < Display.Graphics.Tileset.Size)
                        Display.Graphics.PutTile(x, y, i, 0, 1);
                    
                    i++;
                }
            }

            Display.Refresh();
        }

        public void LoadFile(string file)
        {
            Display.Graphics.Tileset.ClearToSize(0);
            foreach (var line in File.ReadAllLines(file))
                Display.Graphics.Tileset.Add(line);

            FirstTile = 0;
            UpdateDisplay();
        }
    }
}
