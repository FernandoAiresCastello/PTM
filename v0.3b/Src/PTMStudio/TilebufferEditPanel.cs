﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
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

            Proj = new Project();
            Proj.Palette = palette;
            Proj.Tileset = tileset;

            TileBuffer = new ObjectMap(Proj, 1, 45, 25);
            Renderer = new MapRenderer(TileBuffer, Display);
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
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
                    PutTile(x, y);
                else if (e.Button == MouseButtons.Right)
                    GrabTile(x, y);
            }
        }

        public void UpdateDisplay()
        {
            Renderer.Render();
        }

        private void PutTile(int x, int y)
        {
            GameObject tile = MainWindow.GetTileRegister();
            if (tile.Animation.Frames.Count > 0)
            {
                TileBuffer.SetObject(tile, new ObjectPosition(0, x, y));
                UpdateDisplay();
            }
            else
            {
                MessageBox.Show("Tile register is empty", "Warning", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void GrabTile(int x, int y)
        {
            GameObject obj = TileBuffer.GetObject(new ObjectPosition(0, x, y));

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
    }
}
