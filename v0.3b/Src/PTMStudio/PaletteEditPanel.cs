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
        private readonly int MaxColors;

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
            Display.MouseWheel += Display_MouseWheel;
            Display.MouseMove += Display_MouseMove;
            Display.MouseLeave += Display_MouseLeave;
            Display.MouseClick += Display_MouseClick;

            MaxColors = Display.Graphics.Cols * Display.Graphics.Rows;

            UpdateDisplay();
        }

        private void Display_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                ScrollDisplay(-1);
            else
                ScrollDisplay(1);
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
            UpdateIndicator();
        }

        public void LoadFile(string file)
        {
            Display.Graphics.Palette.Clear(256);
            int i = 0;
            foreach (var line in File.ReadAllLines(file))
                Display.Graphics.Palette.Set(i++, int.Parse(line, NumberStyles.HexNumber));

            FirstColor = 0;
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
            int first = FirstColor + (8 * rows);
            if (first >= 0)
                FirstColor = first;

            UpdateDisplay();
        }

        private string GetIndicator()
        {
            return FirstColor + "-" + (FirstColor + MaxColors - 1) + "/" + Display.Graphics.Palette.Size;
        }

        private void UpdateIndicator()
        {
            LblIndicator.Text = GetIndicator();
        }

        private void Display_MouseLeave(object sender, EventArgs e)
        {
            UpdateIndicator();
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            int ix = GetColorIndexFromMousePos(e.Location);
            LblIndicator.Text = GetIndicator() + " (" + ix + ")";
        }

        private int GetColorIndexFromMousePos(Point mousePos)
        {
            return FirstColor + Display.GetMouseToCellIndex(mousePos);
        }

        private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            int ix = GetColorIndexFromMousePos(e.Location);
            EditColor(ix);
        }

        private void EditColor(int index)
        {
            if (index < 0 || index >= Display.Graphics.Palette.Size)
            {
                MessageBox.Show("Index out of bounds", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
        }
    }
}
