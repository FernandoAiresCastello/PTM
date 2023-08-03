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
            TileSeqDisplay.BorderStyle = BorderStyle.FixedSingle;
            TileSeqDisplay.Cursor = Cursors.Hand;
            TileSeqDisplay.MouseClick += TileSeqDisplay_MouseClick;

            TileFrameDisplay = new TiledDisplay(TileFramePanel, 1, 1, 4);
            TileFrameDisplay.Graphics.Palette = palette;
            TileFrameDisplay.Graphics.Tileset = tileset;
            TileFrameDisplay.Graphics.Clear(0);
            TileFrameDisplay.ShowGrid = true;
            TileFrameDisplay.BorderStyle = BorderStyle.FixedSingle;

            ClearTileRegister();
            UpdateDisplay();
        }

        public void ClearTileRegister()
        {
            FrameCount = 0;
            TileRegisterFrame.Set(0, 1, 0);
            TileRegister.Animation.Frames.Clear();
            for (int i = 0; i < TileSeqDisplay.Cols; i++)
                TileRegister.Animation.Frames.Add(new Tile(0, 1, 0));
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
            if (FrameCount == 0 || frameIndex >= FrameCount)
                FrameCount = frameIndex + 1;
            TileRegister.Animation.SetFrame(frameIndex, TileRegisterFrame.Copy());
            UpdateDisplay();
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
            return obj;
        }

        public void SetTileRegister(GameObject tile)
        {
            TileRegister = tile.Copy();
            FrameCount = TileRegister.Animation.Size;
            TileRegisterFrame = TileRegister.Tile.Copy();
            ChkTransparent.Checked = TileRegister.Transparent;
            UpdateDisplay();
        }
    }
}
