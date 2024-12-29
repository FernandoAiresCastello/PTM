using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
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

        public string Filename { get; private set; }

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

            CreateNewBuffer();
            CmbLayer.SelectedIndexChanged += CmbLayer_SelectedIndexChanged;

            LbPos.Text = "";
            UpdateSizeLabel();
        }

        private void CmbLayer_SelectedIndexChanged(object sender, EventArgs e)
        {
            Renderer.SetSingleLayerToRender(GetSelectedLayer());
            UpdateDisplay();
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
            MainWindow.Warning("Tile register is empty");
        }

        private void PutTile(int x, int y)
        {
            GameObject tile = MainWindow.GetTileRegister();
            if (tile.Animation.Frames.Count > 0)
            {
                TileBuffer.SetObject(tile, new ObjectPosition(GetSelectedLayer(), x, y));
                UpdateDisplay();
                MainWindow.TilebufferChanged(true);
            }
            else
            {
                AlertEmptyTileRegister();
            }
        }

        private void DeleteTile(int x, int y)
        {
            TileBuffer.DeleteObject(new ObjectPosition(GetSelectedLayer(), x, y));
            MainWindow.TilebufferChanged(true);
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
                MainWindow.Warning("No tile found at this buffer position");
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

        public void SaveFile()
        {
            if (string.IsNullOrWhiteSpace(Filename))
            {
                SaveFileDialog dialog = new SaveFileDialog();
                dialog.InitialDirectory = Path.Combine(Filesystem.AbsoluteRootPath, "files");
                dialog.Filter = "PTM Tilebuffer File (*.ptm.buf)|*.ptm.buf";
                if (dialog.ShowDialog() == DialogResult.OK)
                    Filename = dialog.FileName;
                else
                    return;
            }

            TilebufferFile.Save(TileBuffer, Filename);
            Filename = Filesystem.NormalizePath(Filename);
            TxtFilename.Text = Filesystem.RemoveAbsoluteRoot(Filename);
            TxtFilename.Text = Filesystem.RemoveFilesPrefix(TxtFilename.Text);
            MainWindow.UpdateFilePanel();
            MainWindow.TilebufferChanged(false);
        }

        public void LoadFile(string file)
        {
            TileBuffer = TilebufferFile.Load(Proj, file);
            Filename = file;
            TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndFilesPrefix(file);
            Renderer.Map = TileBuffer;
            UpdateDisplay();
            UpdateSizeLabel();
            UpdateLayerComboBox(0);
            MainWindow.ShowTilebufferEditor();
            MainWindow.TilebufferChanged(false);
        }

        private void SelectBackColor()
        {
            ColorSelectWindow wnd = new ColorSelectWindow(
                Display.Graphics.Palette, "Select background color");

            if (wnd.ShowDialog(MainWindow) == DialogResult.OK)
            {
                TileBuffer.BackColorIndex = wnd.SelectedIndex;
                UpdateDisplay();
                MainWindow.TilebufferChanged(true);
            }
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
                bool ok = MainWindow.Confirm("Fill entire layer with the tile register data?");

                if (ok)
                {
                    TileBuffer.Fill(tile, GetSelectedLayer());
                    MainWindow.TilebufferChanged(true);
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
            bool ok = MainWindow.Confirm("Delete all tiles from this layer?");

            if (ok)
            {
                TileBuffer.Clear(GetSelectedLayer());
                MainWindow.TilebufferChanged(true);
            }
        }

        private void BtnAddLayer_Click(object sender, EventArgs e)
        {
            AddLayer();
        }

        private void BtnDeleteLayer_Click(object sender, EventArgs e)
        {
            DeleteLayer();
        }

        private void AddLayer()
        {
            TileBuffer.AddLayer();
            UpdateLayerComboBox(TileBuffer.Layers.Count - 1);
            UpdateDisplay();
            MainWindow.TilebufferChanged(true);
        }

        private void DeleteLayer()
        {
            if (TileBuffer.Layers.Count == 1)
            {
                MainWindow.Warning("Layer 0 cannot be removed");
                return;
            }

            int layer = GetSelectedLayer();
            TileBuffer.RemoveLayer(layer);
            UpdateLayerComboBox(0);
            UpdateDisplay();
            MainWindow.TilebufferChanged(true);
        }

        private void BtnViewAllLayers_Click(object sender, EventArgs e)
        {
            if (BtnViewAllLayers.Checked)
                Renderer.SetRenderSingleLayer(false, 0);
            else
                Renderer.SetRenderSingleLayer(true, GetSelectedLayer());

            UpdateDisplay();
        }

        private void BtnZoomIn_Click(object sender, EventArgs e)
        {
            Display.ZoomIn();
        }

        private void BtnZoomOut_Click(object sender, EventArgs e)
        {
            Display.ZoomOut();
        }

        private void BtnNew_Click(object sender, EventArgs e)
        {
            CreateNewBuffer();
        }

        private void CreateNewBuffer()
        {
            TileBuffer = new ObjectMap(Proj, 1, 45, 25);
            if (Renderer == null)
                Renderer = new MapRenderer(TileBuffer, Display);
            else
                Renderer.Map = TileBuffer;

            Filename = null;
            TxtFilename.Text = "<Unsaved>";

            UpdateDisplay();
            UpdateSizeLabel();
            UpdateLayerComboBox(0);
            MainWindow.TilebufferChanged(false);
        }

        private void BtnSelectMode_Click(object sender, EventArgs e)
        {
            // todo
        }
    }
}
