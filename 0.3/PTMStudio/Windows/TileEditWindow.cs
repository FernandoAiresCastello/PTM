using System;
using System.Drawing;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.Graphics;

namespace PTMStudio
{
	public partial class TileEditWindow : Form
    {
        private readonly TilesetEditPanel TilesetPanel;
        private readonly TiledDisplay Display;
        private TiledDisplay MosaicDisplay;
        private readonly Tileset Tileset;
        private readonly int Index;
        private readonly TilePixels Original;

        private TileEditWindow()
        {
            InitializeComponent();
        }

        public TileEditWindow(TilesetEditPanel tsetPanel, Tileset tileset, int index)
        {
            InitializeComponent();

            TilesetPanel = tsetPanel;
            Tileset = tileset;
            Index = index;
            Original = Tileset.Get(index).Copy();
            Text = index.ToString();

            StartPosition = FormStartPosition.CenterParent;
            KeyPreview = true;
            KeyDown += TileEditWindow_KeyDown;

            Display = new TiledDisplay(TilePanel, 8, 8, 3);
            Display.Graphics.Tileset.ClearToSize(0);
            Display.Graphics.Tileset.Add("1111111111111111111111111111111111111111111111111111111111111111");
            Display.Graphics.Palette.Clear(2);
            Display.Graphics.Palette.Set(0, 0x000000);
            Display.Graphics.Palette.Set(1, 0xffffff);
            Display.Graphics.Clear(1);
            Display.ShowGrid = true;
            Display.SetMainGridColor(Color.FromArgb(80, 128, 128, 128));
            Display.MouseMove += Display_MouseMove;
            Display.MouseClick += Display_MouseClick;
            Display.MouseDown += Display_MouseDown;

            InitMosaic();
            UpdateView();
        }

        private void InitMosaic()
        {
            MosaicDisplay = new TiledDisplay(MosaicPanel, 9, 9, 3);
            MosaicDisplay.Graphics.Tileset = Tileset;
            MosaicDisplay.Graphics.Palette = Display.Graphics.Palette;
            MosaicDisplay.Graphics.Clear(1);
        }

        private void DrawMosaic()
        {
            for (int y = 0; y < MosaicDisplay.Rows; y++)
                for (int x = 0; x < MosaicDisplay.Cols; x++)
                    MosaicDisplay.Graphics.PutTile(x, y, Index, 0, 1, false);

            MosaicDisplay.Refresh();
        }

        private void Display_MouseDown(object sender, MouseEventArgs e)
        {
            SetPixel(e);
        }

        private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            SetPixel(e);
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            SetPixel(e);
        }

        private void TileEditWindow_ResizeEnd(object sender, EventArgs e)
        {
            Text = Size.ToString();
        }

        private void UpdateView()
        {
            string pixels = Tileset.Get(Index).ToBinaryString();
            int i = 0;

            for (int y = 0; y < Display.Rows; y++)
            {
                for (int x = 0; x < Display.Cols; x++)
                {
                    char ch = pixels[i++];
                    if (ch == '0')
                        Display.Graphics.PutTile(x, y, 0, 1, 0, false);
                    else if (ch == '1')
                        Display.Graphics.PutTile(x, y, 0, 0, 1, false);
                }
            }

            Display.Refresh();
            DrawMosaic();
            UpdateBinary();
        }

        private void SetPixel(MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left && e.Button != MouseButtons.Right)
                return;

            Point pos = Display.GetMouseToCellPos(e.Location);
            if (pos.X < 0 || pos.Y < 0 || pos.X >= Display.Cols || pos.Y >= Display.Rows)
                return;

            int pixelIndex = Display.GetMouseToCellIndex(e.Location);
            if (pixelIndex < 0 || pixelIndex > 63)
                return;

            char[] pixels = Tileset.Get(Index).ToBinaryString().ToCharArray();

            if (e.Button == MouseButtons.Left)
                pixels[pixelIndex] = '1';
            else if (e.Button == MouseButtons.Right)
                pixels[pixelIndex] = '0';

            string newPixels = new string(pixels);
            Tileset.Set(Index, newPixels);
            OnPixelsChanged();
        }

        private void UpdateBinary()
        {
            TxtBinary.Text = Tileset.Get(Index).ToBinaryString();
        }

        private void OnPixelsChanged()
        {
            UpdateView();
            TilesetPanel.UpdateDisplay();
        }

        private void BtnUndo_Click(object sender, EventArgs e)
        {
            UndoChanges();
        }

        private void UndoChanges()
        {
            Tileset.Set(Index, Original);
            OnPixelsChanged();
        }

        private void BtnClear_Click(object sender, EventArgs e)
        {
            ClearAllPixels();
        }

        private void ClearAllPixels()
        {
            Tileset.Get(Index).Clear();
            OnPixelsChanged();
        }

        private void BtnFlipH_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).FlipHorizontal();
            OnPixelsChanged();
        }

        private void BtnFlipV_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).FlipVertical();
            OnPixelsChanged();
        }

        private void BtnRotateR_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).RotateRight();
            OnPixelsChanged();
        }

        private void BtnRotateD_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).RotateDown();
            OnPixelsChanged();
        }

        private void BtnRotateL_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).RotateLeft();
            OnPixelsChanged();
        }

        private void BtnRotateU_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).RotateUp();
            OnPixelsChanged();
        }

        private void BtnInvert_Click(object sender, EventArgs e)
        {
            Tileset.Get(Index).Invert();
            OnPixelsChanged();
        }

		private void BtnCopyBinary_Click(object sender, EventArgs e)
		{
            CopyBinaryString();
		}

		private void BtnPasteBinary_Click(object sender, EventArgs e)
        {
            PasteBinaryString();
        }

		private void CopyBinaryString()
        {
            Clipboard.SetText(TxtBinary.Text);
		}

		private void PasteBinaryString()
        {
            string text = Clipboard.GetText();
            if (text.Length != 64)
            {
                AlertInvalidBinaryString();
                return;
            }

            foreach (char ch in text)
            {
                if (ch != '0' && ch != '1')
                {
                    AlertInvalidBinaryString();
                    return;
                }
            }

            Tileset.Get(Index).FromBinaryString(text);
            OnPixelsChanged();
        }

        private void AlertInvalidBinaryString()
        {
            MainWindow.Warning("Invalid binary string");
        }

        private void TileEditWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.C)
                CopyBinaryString();
            else if (e.Control && e.KeyCode == Keys.V)
                PasteBinaryString();
            else if (e.Control && e.KeyCode == Keys.Z)
                UndoChanges();
            else if (e.KeyCode == Keys.Delete)
                ClearAllPixels();
            else if (e.KeyCode == Keys.Escape)
                Close();
        }
	}
}
