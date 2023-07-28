using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.IO;
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
        private int FirstColor = 0;

        public PaletteEditPanel()
        {
            InitializeComponent();

            Display = new TiledDisplay(PnlPalette, 8, 8, 3);
            Display.Graphics.Palette.Clear(256, 0x000000);
            Display.Graphics.Palette.Set(0, 0x101010);
            Display.Graphics.Palette.Set(1, 0xf0f0f0);
            Display.Graphics.Tileset.ClearToSize(0);
            Display.Graphics.Tileset.Add("1111111111111111111111111111111111111111111111111111111111111111");
            Display.ShowGrid = true;
            Display.Cursor = Cursors.Hand;
            Display.SetMainGridColor(Color.FromArgb(80, 128, 128, 128));

            UpdateDisplay();
        }

        public void UpdateDisplay()
        {
            Display.Graphics.Clear(0);

            int i = FirstColor;

            for (int y = 0; y < Display.Rows; y++)
            {
                for (int x = 0; x < Display.Cols; x++)
                {
                    if (i < Display.Graphics.Palette.Size)
                        Display.Graphics.PutTile(x, y, 0, i, i);

                    i++;
                }
            }

            Display.Refresh();
        }

        public void LoadFile(string file)
        {
            Display.Graphics.Palette.Clear(0);
            foreach (var line in File.ReadAllLines(file))
                Display.Graphics.Palette.Add(int.Parse(line, NumberStyles.HexNumber));

            FirstColor = 0;
            TxtFilename.Text = FilesystemPanel.RemoveFilesPrefix(file);
            UpdateDisplay();
        }
    }
}
