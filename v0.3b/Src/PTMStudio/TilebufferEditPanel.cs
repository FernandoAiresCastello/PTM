using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.File;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public partial class TilebufferEditPanel : UserControl
    {
        private MainWindow MainWindow;
        private TiledDisplay Display;
        private MapRenderer Renderer;
        private ObjectMap TileBuffer;
        private Project Proj;
        private int ActiveLayer;

        private TilebufferEditPanel()
        {
            InitializeComponent();
        }

        public TilebufferEditPanel(MainWindow mainWnd, Tileset tileset, Palette palette)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Display = new TiledDisplay(DisplayPanel, 45, 25, 2);
            Display.Parent = DisplayPanel;
            Display.Graphics.Palette = palette;
            Display.Graphics.Tileset = tileset;
            Display.Graphics.Clear(0);
            Display.ShowGrid = true;
            Display.MouseClick += Display_MouseClick;
            Display.MouseMove += Display_MouseMove;
            Display.MouseLeave += Display_MouseLeave;

            Proj = new Project();
            Proj.Palette = palette;
            Proj.Tileset = tileset;

            TileBuffer = new ObjectMap(Proj, 1, 45, 25);
            Renderer = new MapRenderer(TileBuffer, Display);
            ActiveLayer = 0;
            UpdateLayerComboBox(0);

            LbPos.Text = "";
            UpdateSizeLabel();
        }

        private void UpdateSizeLabel()
        {
            LbSize.Text = string.Format("Layers: {0} Width: {1} Height: {2}", 
                TileBuffer.Layers.Count, TileBuffer.Width, TileBuffer.Height);
        }

        private void UpdateLayerComboBox(int selected)
        {
            CmbLayer.Items.Clear();
            for (int i = 0; i < TileBuffer.Layers.Count; i++)
                CmbLayer.Items.Add("Layer " + i);

            CmbLayer.SelectedIndex = selected;
        }

        private int GetSelectedLayer()
        {
            return CmbLayer.SelectedIndex;
        }

        private void Display_MouseLeave(object sender, EventArgs e)
        {
            LbPos.Text = "";
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            Point pos = Display.GetMouseToCellPos(e.Location);
            LbPos.Text = string.Format("X: {0} Y: {1}", pos.X, pos.Y);

            if (e.Button != MouseButtons.None)
                Display_MouseClick(sender, e);
        }

        private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            Point pos = Display.GetMouseToCellPos(e.Location);
            int x = pos.X;
            int y = pos.Y;

            if (x >= 0 && y >= 0 && x < TileBuffer.Width && y < TileBuffer.Height)
            {
                if (e.Button == MouseButtons.Left)
                {
                    if (ModifierKeys == Keys.Control)
                        DeleteTile(x, y);
                    else
                        PutTile(x, y);
                }
                else if (e.Button == MouseButtons.Right)
                {
                    GrabTile(x, y);
                }
            }
        }

        public void UpdateDisplay()
        {
            Renderer.Render();
        }

        private void AlertEmptyTileRegister()
        {
            MessageBox.Show("Tile register is empty", "Warning",
                MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void PutTile(int x, int y)
        {
            GameObject tile = MainWindow.GetTileRegister();
            if (tile.Animation.Frames.Count > 0)
            {
                TileBuffer.SetObject(tile, new ObjectPosition(GetSelectedLayer(), x, y));
                UpdateDisplay();
            }
            else
            {
                AlertEmptyTileRegister();
            }
        }

        private void DeleteTile(int x, int y)
        {
            TileBuffer.DeleteObject(new ObjectPosition(GetSelectedLayer(), x, y));
        }

        private void GrabTile(int x, int y)
        {
            GameObject obj = TileBuffer.GetObject(new ObjectPosition(GetSelectedLayer(), x, y));

            if (obj != null)
            {
                MainWindow.SetTileRegister(obj);
            }
            else
            {
                MessageBox.Show("No tile found at this buffer position", "Warning",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void BtnSave_Click(object sender, EventArgs e)
        {
            SaveFile();
        }

        private void BtnSetBgColor_Click(object sender, EventArgs e)
        {
            SelectBackColor();
        }

        private void SaveFile()
        {
        }

        private void SelectBackColor()
        {
        }

        private void BtnFill_Click(object sender, EventArgs e)
        {
            FillLayer();
        }

        private void FillLayer()
        {
            GameObject tile = MainWindow.GetTileRegister();
            if (tile.Animation.Frames.Count > 0)
            {
                DialogResult result = MessageBox.Show("Fill entire layer with the tile register data?",
                    "Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

                if (result == DialogResult.Yes)
                {
                    TileBuffer.Fill(tile, GetSelectedLayer());
                }
            }
            else
            {
                AlertEmptyTileRegister();
            }
        }

        private void BtnClear_Click(object sender, EventArgs e)
        {
            ClearLayer();
        }

        private void ClearLayer()
        {
            DialogResult result = MessageBox.Show("Delete all tiles from this layer?",
                            "Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (result == DialogResult.Yes)
            {
                TileBuffer.Clear(GetSelectedLayer());
            }
        }
    }
}
