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
        private readonly int MaxTiles;
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
            Display.Cursor = Cursors.Hand;
            Display.MouseClick += Display_MouseClick;
            Display.MouseMove += Display_MouseMove;
            Display.MouseLeave += Display_MouseLeave;
            Display.MouseWheel += Display_MouseWheel;

            MaxTiles = Display.Graphics.Cols * Display.Graphics.Rows;

            DefaultTileset.Init(Display.Graphics.Tileset);
            UpdateDisplay();
        }

        private void Display_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                ScrollDisplay(-1);
            else
                ScrollDisplay(1);
        }

        private void Display_MouseLeave(object sender, EventArgs e)
        {
            UpdateIndicator();
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            int ix = GetTileIndexFromMousePos(e.Location);
            LblIndicator.Text = GetIndicator() + " (" + ix + ")";
        }

        private void UpdateIndicator()
        {
            LblIndicator.Text = GetIndicator();
        }

        private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            int ix = GetTileIndexFromMousePos(e.Location);
            EditTile(ix);
        }

        private string GetIndicator()
        {
            return FirstTile + "-" + (FirstTile + MaxTiles - 1) + "/" + Display.Graphics.Tileset.Size;
        }

        private int GetTileIndexFromMousePos(Point mousePos)
        {
            return FirstTile + Display.GetMouseToCellIndex(mousePos);
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
            UpdateIndicator();
        }

        public void LoadFile(string file)
        {
            Display.Graphics.Tileset.ClearToSize(0);
            foreach (var line in File.ReadAllLines(file))
                Display.Graphics.Tileset.Add(line);

            FirstTile = 0;
            TxtFilename.Text = FilesystemPanel.RemoveFilesPrefix(file);
            UpdateDisplay();
        }

        private void BtnNext_Click(object sender, EventArgs e)
        {
            ScrollDisplay(1);
        }

        private void BtnPrev_Click(object sender, EventArgs e)
        {
            ScrollDisplay(-1);
        }

        private void ScrollDisplay(int rows)
        {
            int first = FirstTile + (8 * rows);
            if (first >= 0)
                FirstTile = first;

            UpdateDisplay();
        }

        private void EditTile(int index)
        {
            if (index < 0 || index >= Display.Graphics.Tileset.Size)
            {
                MessageBox.Show("Index out of bounds", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            TileEditWindow wnd = new TileEditWindow(this, Display.Graphics.Tileset, index);
            wnd.ShowDialog(this);
        }
    }
}
