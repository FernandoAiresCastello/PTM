using System;
using System.Drawing;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace PTMStudio
{
	public partial class TileRegisterPanel : UserControl
    {
        private readonly MainWindow MainWindow;
        private readonly TiledDisplay TileSeqDisplay;
        private readonly TiledDisplay TileFrameDisplay;
        private readonly GameObject TileRegister;
        private readonly int EmptyColor = 0;
        private readonly Tile EmptyTile;
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
            TileRegister = new GameObject();
            TileRegister.Animation.Clear();

            EmptyTile = new Tile(0, EmptyColor, EmptyColor);

            TileSeqDisplay = new TiledDisplay(TileSeqPanel, 7, 1, 3);
            TileSeqDisplay.Graphics.Palette = palette;
            TileSeqDisplay.Graphics.Tileset = tileset;
            TileSeqDisplay.Graphics.Clear(EmptyColor);
            TileSeqDisplay.ShowGrid = true;
			TileSeqDisplay.SetMainGridColor(Color.FromArgb(128, 80, 80, 80));
			TileSeqDisplay.BorderStyle = BorderStyle.None;
            TileSeqDisplay.Cursor = Cursors.Hand;
            TileSeqDisplay.MouseClick += TileSeqDisplay_MouseClick;

            TileFrameDisplay = new TiledDisplay(TileFramePanel, 1, 1, 4);
            TileFrameDisplay.Graphics.Palette = palette;
            TileFrameDisplay.Graphics.Tileset = tileset;
            TileFrameDisplay.Graphics.Clear(EmptyColor);
            TileFrameDisplay.ShowGrid = true;
			TileFrameDisplay.SetMainGridColor(Color.FromArgb(128, 80, 80, 80));
			TileFrameDisplay.BorderStyle = BorderStyle.None;

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
			TileRegisterFrame = new Tile('X', 0, 15);

			FrameCount = 1;
            TileRegister.Animation.Frames.Clear();
            for (int i = 0; i < TileSeqDisplay.Cols; i++)
                TileRegister.Animation.Frames.Add(EmptyTile.Copy());

            TileRegister.Animation.Frames[0] = new Tile(TileRegisterFrame);

			TileRegister.Properties.Entries.Clear();
            UpdatePropertiesPanel();
            MainWindow.CacheTileRegister();
        }

        public void UpdateDisplay()
        {
            TileSeqDisplay.Graphics.Clear(EmptyColor);
            int x = 0;
            int y = 0;
            
            foreach (Tile tile in TileRegister.Animation.Frames)
            {
                TileSeqDisplay.Graphics.PutTile(x, y, tile);
                x++;
            }

            TileSeqDisplay.Refresh();

            TileFrameDisplay.Graphics.Clear(EmptyColor);
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
			(TileRegisterFrame.BackColor, TileRegisterFrame.ForeColor) = 
                (TileRegisterFrame.ForeColor, TileRegisterFrame.BackColor);

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

            obj.Transparent = false;

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

            if (obj.Animation.Frames.Count == 0)
                obj.Animation.Frames.Add(TileRegisterFrame.Copy());


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
                    TileRegister.Animation.Frames.Add(EmptyTile.Copy());
            }

            TileRegister.Transparent = copiedTile.Transparent;
            TileRegister.Properties.SetEqual(copiedTile.Properties);

            TileRegisterFrame = TileRegister.Tile.Copy();

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
