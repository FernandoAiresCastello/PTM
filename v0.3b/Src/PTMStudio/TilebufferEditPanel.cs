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

            Proj = new Project();
            Proj.Palette = palette;
            Proj.Tileset = tileset;

            TileBuffer = new ObjectMap(Proj, 1, 45, 25);
            Renderer = new MapRenderer(TileBuffer, Display);
        }

        public void UpdateDisplay()
        {
            Renderer.Render();
        }
    }
}
