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
		public GameObject TileRegister { get; private set; }

		private readonly MainWindow MainWindow;
        private readonly TiledDisplay TileFrameDisplay;
		private readonly int EmptyColor = 0;
		private int FrameCount;
        private int AnimationFrameIndex = 0;

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

            TileFrameDisplay = new TiledDisplay(TileFramePanel, 1, 1, 4);
            TileFrameDisplay.Graphics.Palette = palette;
            TileFrameDisplay.Graphics.Tileset = tileset;
            TileFrameDisplay.Graphics.Clear(EmptyColor);
            TileFrameDisplay.ShowGrid = true;
			TileFrameDisplay.SetMainGridColor(Color.FromArgb(128, 80, 80, 80));
			TileFrameDisplay.BorderStyle = BorderStyle.None;

            ClearTileRegister();
            UpdateInfoLabels();

            Timer tileRegAnimTimer = new Timer();
			tileRegAnimTimer.Tick += TileRegAnimTimer_Tick;
			tileRegAnimTimer.Interval = MainWindow.TileAnimationInterval;
			tileRegAnimTimer.Start();
		}

		private void TileRegAnimTimer_Tick(object sender, EventArgs e)
		{
            UpdateTileFrameDisplay();
		}

		public void ClearTileRegister()
        {
            TileRegister.Animation.Frames.Clear();
			TileRegister.Animation.Frames.Add(new Tile('?', 0, 15));
			TileRegister.Properties.Entries.Clear();

            FrameCount = TileRegister.Animation.Frames.Count;

            UpdatePropertiesPanel();
        }

        public void UpdateInfoLabels()
        {
            UpdateTileFrameDisplay();

			LbTileRegFrame.Text = string.Format("{0}, {1}, {2}",
                TileRegister.Tile.Index, TileRegister.Tile.ForeColor, TileRegister.Tile.BackColor);

            LblFrameCount.Text = FrameCount.ToString();
        }

        private void UpdateTileFrameDisplay()
        {
            Tile frame = TileRegister.Animation.Frames[AnimationFrameIndex % TileRegister.Animation.Frames.Count];
			TileFrameDisplay.Graphics.PutTile(0, 0, frame);
			TileFrameDisplay.Refresh();

            AnimationFrameIndex++;
		}

		private void BtnSwitchColor_Click(object sender, EventArgs e)
        {
			(TileRegister.Tile.BackColor, TileRegister.Tile.ForeColor) = 
                (TileRegister.Tile.ForeColor, TileRegister.Tile.BackColor);

			UpdateInfoLabels();
        }

        private void BtnNew_Click(object sender, EventArgs e)
        {
            ClearTileRegister();
            UpdateInfoLabels();
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
                obj.Animation.Frames.Add(TileRegister.Tile.Copy());

			return obj;
        }

        public void SetTileRegister(GameObject tile)
        {
            GameObject copiedTile = tile.Copy();
            FrameCount = copiedTile.Animation.Size;

            TileRegister.Animation.Frames.Clear();
            for (int i = 0; i < FrameCount; i++)
                TileRegister.Animation.Frames.Add(copiedTile.Animation.Frames[i]);

            TileRegister.Transparent = copiedTile.Transparent;
            TileRegister.Properties.SetEqual(copiedTile.Properties);

            UpdatePropertiesPanel();
            UpdateInfoLabels();
        }

		public void SetTileRegisterForeColor(int color)
        {
            Tile firstTile = new Tile(TileRegister.Animation.Frames[0]);
            firstTile.ForeColor = color;
			SetSingleTileRegisterFrame(firstTile);
		}

		public void SetTileRegisterBackColor(int color)
		{
			Tile firstTile = new Tile(TileRegister.Animation.Frames[0]);
			firstTile.BackColor = color;
			SetSingleTileRegisterFrame(firstTile);
		}

		public void SetTileRegisterChar(int ch)
		{
			Tile firstTile = new Tile(TileRegister.Animation.Frames[0]);
			firstTile.Index = ch;
            SetSingleTileRegisterFrame(firstTile);
		}

        private void SetSingleTileRegisterFrame(Tile firstTile)
        {
			TileRegister.Animation.Frames.Clear();
			TileRegister.Animation.Frames.Add(firstTile);
			FrameCount = TileRegister.Animation.Frames.Count;
			UpdateInfoLabels();
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
