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

namespace TGLTilePaint
{
    public partial class BinaryWindow : Form
    {
        public Color TileForeColor = Color.FromArgb(0, 0, 0);
        public Color TileBackColor = Color.FromArgb(255, 255, 255);

        private TileEditPanel PnlTileEdit;
        private MosaicPanel PnlMosaic;

        public BinaryWindow()
        {
            InitializeComponent();
            PnlTileEdit = new TileEditPanel(this);
            PnlTileEdit.Parent = PnlTileEditContainer;
            PnlTileEdit.Dock = DockStyle.Fill;
            UpdateBinaryString();

            PnlMosaic = new MosaicPanel();
            PnlMosaic.Parent = PnlMosaicContainer;
            PnlMosaic.Dock = DockStyle.Fill;
            PnlMosaic.TileImage = PnlTileEdit.GetBitmapRGB();

            //Size = new Size(418, 570);
            ResizeEnd += BinaryWindow_ResizeEnd;
            KeyPreview = true;
        }

        private void BinaryWindow_ResizeEnd(object sender, EventArgs e)
        {
        }

        private void BtnClear_Click(object sender, EventArgs e)
        {
            PnlTileEdit.FillPixelsColor(TileBackColor);
            UpdateMosaicAndBinaryString();
        }

        public void UpdateMosaicAndBinaryString()
        {
            UpdateBinaryString();
            UpdateMosaic();
        }

        private void UpdateMosaic()
        {
            PnlMosaic.TileImage = PnlTileEdit.GetBitmapRGB();
            PnlMosaic.Refresh();
        }

        private void UpdateBinaryString()
        {
            Bitmap bmp = PnlTileEdit.GetBitmapRGB();
            StringBuilder binary = new StringBuilder();
            
            for (int y = 0; y < bmp.Height; y++)
            {
                for (int x = 0; x < bmp.Width; x++)
                {
                    Color pixel = bmp.GetPixel(x, y);

                    if (pixel == TileForeColor)
                        binary.Append('1');
                    else if (pixel == TileBackColor)
                        binary.Append('0');
                    else
                        binary.Append('?');
                }
            }

            TxtBinary.Text = binary.ToString();
        }

        private string Get16x16BinaryString()
        {
            Bitmap bmp = PnlTileEdit.GetBitmapRGB();

            StringBuilder binary1 = new StringBuilder();
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    Color pixel = bmp.GetPixel(x, y);

                    if (pixel == TileForeColor)
                        binary1.Append('1');
                    else if (pixel == TileBackColor)
                        binary1.Append('0');
                    else
                        binary1.Append('?');
                }
            }
            StringBuilder binary2 = new StringBuilder();
            for (int y = 0; y < 8; y++)
            {
                for (int x = 8; x < 16; x++)
                {
                    Color pixel = bmp.GetPixel(x, y);

                    if (pixel == TileForeColor)
                        binary2.Append('1');
                    else if (pixel == TileBackColor)
                        binary2.Append('0');
                    else
                        binary2.Append('?');
                }
            }
            StringBuilder binary3 = new StringBuilder();
            for (int y = 8; y < 16; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    Color pixel = bmp.GetPixel(x, y);

                    if (pixel == TileForeColor)
                        binary3.Append('1');
                    else if (pixel == TileBackColor)
                        binary3.Append('0');
                    else
                        binary3.Append('?');
                }
            }
            StringBuilder binary4 = new StringBuilder();
            for (int y = 8; y < 16; y++)
            {
                for (int x = 8; x < 16; x++)
                {
                    Color pixel = bmp.GetPixel(x, y);

                    if (pixel == TileForeColor)
                        binary4.Append('1');
                    else if (pixel == TileBackColor)
                        binary4.Append('0');
                    else
                        binary4.Append('?');
                }
            }

            string binary =
                binary1.ToString() + Environment.NewLine +
                binary2.ToString() + Environment.NewLine +
                binary3.ToString() + Environment.NewLine +
                binary4.ToString() + Environment.NewLine;

            return binary.ToString();
        }

        private void BtnCopy_Click(object sender, EventArgs e)
        {
            if (PnlTileEdit.Is8x8())
            {
                Clipboard.SetText(TxtBinary.Text);
            }
            else if (PnlTileEdit.Is16x16())
            {
                string binary = Get16x16BinaryString();
                Clipboard.SetText(binary);
            }
        }

        private void BtnPaste_Click(object sender, EventArgs e)
        {
            if (PnlTileEdit.Is8x8())
                Paste8x8();
            else if (PnlTileEdit.Is16x16())
                Paste16x16();
        }

        private void Paste8x8()
        {
            string text = Clipboard.GetText();

            if (text.Length != 64)
            {
                MessageBox.Show("Invalid tile data", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            int x = 0;
            int y = 0;

            foreach (char ch in text)
            {
                Color color;
                if (ch == '0')
                    color = TileBackColor;
                else if (ch == '1')
                    color = TileForeColor;
                else
                {
                    MessageBox.Show("Invalid tile data", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                PnlTileEdit.Tile.SetPixel(x, y, color);
                x++;
                if (x >= 8)
                {
                    x = 0;
                    y++;
                }
            }

            PnlTileEdit.Refresh();
            UpdateMosaic();
            TxtBinary.Text = text;
        }

        private void Paste16x16()
        {
            string text = Clipboard.GetText();

            MessageBox.Show("Cannot paste 16x16 tile", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void Paste16x16_Linear()
        {
            string text = Clipboard.GetText();

            if (text.Length != 262)
            {
                MessageBox.Show("Invalid tile data", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            int x = 0;
            int y = 0;

            foreach (char ch in text)
            {
                Color color;
                if (ch == '0')
                    color = TileBackColor;
                else if (ch == '1')
                    color = TileForeColor;
                else if (ch == '\r' || ch == '\n')
                    continue;
                else
                {
                    MessageBox.Show("Invalid tile data", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                PnlTileEdit.Tile.SetPixel(x, y, color);
                x++;
                if (x >= 16)
                {
                    x = 0;
                    y++;
                }
            }

            PnlTileEdit.Refresh();
            UpdateMosaic();
            TxtBinary.Text = text;
        }

        private void BtnMode_Click(object sender, EventArgs e)
        {
            PnlTileEdit.ToggleMode();
            BtnClear_Click(sender, e);

            TxtBinary.Visible = !PnlTileEdit.Is16x16();
        }

        private void BinaryWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.C)
            {
                BtnCopy_Click(sender, e);
            }
            else if (e.Control && e.KeyCode == Keys.V)
            {
                BtnPaste_Click(sender, e);
            }
            else if (e.KeyCode == Keys.Delete)
            {
                BtnClear_Click(sender, e);
            }
            else if (e.KeyCode == Keys.F1)
            {
                BtnMode_Click(sender, e);
            }
        }
    }
}
