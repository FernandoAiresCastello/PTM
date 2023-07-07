using System;
using System.Collections.Generic;
using System.Windows.Forms;
using TileGameLib.Graphics;
using TileGameMaker.MapEditorElements;
using TileGameMaker.Panels;
using TileGameMaker.Util;

namespace TileGameMaker.Windows
{
    public partial class MainWindow2 : Form
    {
        private Tileset Tileset;
        private TilePickerPanel TilesetPanel;
        private Palette Palette;
        private ColorPickerPanel PalettePanel;

        public MainWindow2()
        {
            InitializeComponent();
            Icon = Global.WindowIcon;
            Size = new System.Drawing.Size(1024, 600);

            Tileset = new Tileset();
            TilesetPanel = new TilePickerPanel(Tileset);
            TilesetPanel.Parent = PnlTopLeft;
            TilesetPanel.Dock = DockStyle.Fill;

            Palette = new Palette();
            PalettePanel = new ColorPickerPanel(Palette);
            PalettePanel.Parent = PnlBtmLeft;
            PalettePanel.Dock = DockStyle.Fill;
        }
    }
}
