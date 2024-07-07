using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public partial class TileRegisterPanel : UserControl
    {
        private MainWindow MainWindow;
        private Tileset Tileset;
        private Palette Palette;
        private TiledDisplay TileSeqDisplay;
        private TiledDisplay TileFrameDisplay;
        private GameObject TileRegister;
        private int FrameCount;

        public Tile TileRegisterFrame { get; private set; }

        private TileRegisterPanel()
        {
            InitializeComponent();
        }

        public TileRegisterPanel(MainWindow mainWnd, Tileset tileset, Palette palette)
        {
            InitializeComponent();
            MainWindow = mainWnd;
            Tileset = tileset;
            Palette = palette;
            TileRegister = new GameObject();
            TileRegister.Animation.Clear();
            TileRegisterFrame = new Tile(0, 1, 0);

            TileSeqDisplay = new TiledDisplay(TileSeqPanel, 7, 1, 3);
            TileSeqDisplay.Graphics.Palette = palette;
            TileSeqDisplay.Graphics.Tileset = tileset;
            TileSeqDisplay.Graphics.Clear(0);
            TileSeqDisplay.ShowGrid = true;
            TileSeqDisplay.BorderStyle = BorderStyle.None;
            TileSeqDisplay.Cursor = Cursors.Hand;
            TileSeqDisplay.MouseClick += TileSeqDisplay_MouseClick;

            TileFrameDisplay = new TiledDisplay(TileFramePanel, 1, 1, 4);
            TileFrameDisplay.Graphics.Palette = palette;
            TileFrameDisplay.Graphics.Tileset = tileset;
            TileFrameDisplay.Graphics.Clear(0);
            TileFrameDisplay.ShowGrid = true;
            TileFrameDisplay.BorderStyle = BorderStyle.None;

            ChkTransparent.CheckedChanged += ChkTransparent_CheckedChanged;
            PropertyGrid.CellValueChanged += PropertyGrid_CellValueChanged;

            ClearTileRegister();
            UpdateDisplay();
        }

        private void PropertyGrid_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            MainWindow.CacheTileRegister();
        }

        private void ChkTransparent_CheckedChanged(object sender, EventArgs e)
        {
            MainWindow.CacheTileRegister();
        }

        public void ClearTileRegister()
        {
            FrameCount = 0;
            ChkTransparent.Checked = false;
            TileRegisterFrame.Set(0, 1, 0);
            TileRegister.Animation.Frames.Clear();
            for (int i = 0; i < TileSeqDisplay.Cols; i++)
                TileRegister.Animation.Frames.Add(new Tile(0, 1, 0));

            TileRegister.Properties.Entries.Clear();
            UpdatePropertiesPanel();
            MainWindow.CacheTileRegister();
        }

        public void UpdateDisplay()
        {
            TileSeqDisplay.Graphics.Clear(0);
            int x = 0;
            int y = 0;
            
            foreach (Tile tile in TileRegister.Animation.Frames)
            {
                TileSeqDisplay.Graphics.PutTile(x, y, tile);
                x++;
            }

            TileSeqDisplay.Refresh();

            TileFrameDisplay.Graphics.Clear(0);
            TileFrameDisplay.Graphics.PutTile(0, 0, TileRegisterFrame);
            TileFrameDisplay.Refresh();

            LbTileRegFrame.Text = string.Format("{0}, {1}, {2}",
                TileRegisterFrame.Index, TileRegisterFrame.ForeColor, TileRegisterFrame.BackColor);

            LblFrameCount.Text = FrameCount.ToString();
        }

        private void TileSeqDisplay_MouseClick(object sender, MouseEventArgs e)
        {
            int frameIndex = TileSeqDisplay.GetMouseToCellPos(e.Location).X;

            if (e.Button == MouseButtons.Left)
            {
                if (FrameCount < frameIndex + 1)
                    FrameCount = frameIndex + 1;

                TileRegister.Animation.SetFrame(frameIndex, TileRegisterFrame.Copy());
                UpdateDisplay();
                MainWindow.CacheTileRegister();
            }
            else if (e.Button == MouseButtons.Right)
            {
                Tile tile = TileRegister.Animation.Frames[frameIndex];
                TileRegisterFrame.SetEqual(tile);
                UpdateDisplay();
            }
        }

        private void BtnSwitchColor_Click(object sender, EventArgs e)
        {
            int temp = TileRegisterFrame.ForeColor;
            TileRegisterFrame.ForeColor = TileRegisterFrame.BackColor;
            TileRegisterFrame.BackColor = temp;
            UpdateDisplay();
        }

        private void BtnNew_Click(object sender, EventArgs e)
        {
            ClearTileRegister();
            UpdateDisplay();
        }

        public GameObject GetTileRegister()
        {
            GameObject obj = new GameObject();
            obj.Animation.Frames.Clear();

            for (int i = 0; i < FrameCount; i++)
            {
                if (i >= TileRegister.Animation.Size)
                    break;

                obj.Animation.Frames.Add(TileRegister.Animation.Frames[i].Copy());
            }

            obj.Transparent = ChkTransparent.Checked;

            obj.Properties.Entries.Clear();
            foreach (DataGridViewRow row in PropertyGrid.Rows)
            {
                if (row.Cells[0].Value != null && row.Cells[1].Value != null)
                {
                    string prop = row.Cells[0].Value.ToString();
                    string value = row.Cells[1].Value.ToString();
                    obj.Properties.Set(prop, value);
                }
            }

            return obj;
        }

        public void SetTileRegister(GameObject tile)
        {
            GameObject copiedTile = tile.Copy();
            FrameCount = copiedTile.Animation.Size;

            TileRegister.Animation.Frames.Clear();
            for (int i = 0; i < TileSeqDisplay.Cols; i++)
            {
                if (i < copiedTile.Animation.Size)
                    TileRegister.Animation.Frames.Add(copiedTile.Animation.Frames[i]);
                else
                    TileRegister.Animation.Frames.Add(new Tile(0, 1, 0));
            }

            TileRegister.Transparent = copiedTile.Transparent;
            TileRegister.Properties.SetEqual(copiedTile.Properties);

            TileRegisterFrame = TileRegister.Tile.Copy();
            ChkTransparent.Checked = TileRegister.Transparent;

            UpdatePropertiesPanel();
            UpdateDisplay();
        }

        private void UpdatePropertiesPanel()
        {
            PropertyGrid.Rows.Clear();
            foreach (var item in TileRegister.Properties.Entries)
            {
                string prop = item.Key;
                string value = item.Value;
                PropertyGrid.Rows.Add(prop, value);
            }
            PropertyGrid.Refresh();
        }
    }
}
