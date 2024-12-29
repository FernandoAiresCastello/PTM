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
using TileGameLib.Graphics;

namespace PTMStudio
{
    public partial class ColorSelectWindow : Form
    {
        private TiledDisplay Display;
        private int FirstColor = 0;
        private readonly int MaxColors;

        public int SelectedIndex { get; private set; }

        private ColorSelectWindow()
        {
            InitializeComponent();
        }

        public ColorSelectWindow(Palette palette, string title)
        {
            InitializeComponent();
            Text = title;
            Size = new Size(212, 235);
            StartPosition = FormStartPosition.Manual;
            Location = MousePosition;
            KeyPreview = true;

            Display = new TiledDisplay(PnlPalette, 8, 8, 3);
            Display.Graphics.Palette = palette;
            Display.Graphics.Tileset.ClearToSize(0);
            Display.Graphics.Tileset.Add("1111111111111111111111111111111111111111111111111111111111111111");
            Display.ShowGrid = true;
            Display.Cursor = Cursors.Hand;
            Display.SetMainGridColor(Color.FromArgb(80, 128, 128, 128));
            Display.MouseWheel += Display_MouseWheel;
            Display.MouseClick += Display_MouseClick;
            KeyDown += ColorSelectWindow_KeyDown;

            MaxColors = Display.Graphics.Cols * Display.Graphics.Rows;

            UpdateDisplay();

            //ResizeEnd += ColorSelectWindow_ResizeEnd;
        }

        private void ColorSelectWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                DialogResult = DialogResult.Cancel;
        }

        private void ColorSelectWindow_ResizeEnd(object sender, EventArgs e)
        {
            Text = Size.ToString();
        }

        private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            int ix = GetColorIndexFromMousePos(e.Location);
            if (ix < 0 || ix >= Display.Graphics.Palette.Size)
            {
                AlertIndexOutOfBounds();
                return;
            }

            SelectedIndex = ix;
            DialogResult = DialogResult.OK;
        }

        private int GetColorIndexFromMousePos(Point mousePos)
        {
            return FirstColor + Display.GetMouseToCellIndex(mousePos);
        }

        private void AlertIndexOutOfBounds()
        {
            MainWindow.Warning("Color index out of bounds");
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
                        Display.Graphics.PutTile(x, y, 0, i, i, false);

                    i++;
                }
            }

            Display.Refresh();
        }

        private void ScrollDisplay(int rows)
        {
            int first = FirstColor + (8 * rows);
            if (first >= 0)
                FirstColor = first;

            UpdateDisplay();
        }
    }
}
