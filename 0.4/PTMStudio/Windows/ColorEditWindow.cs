using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public partial class ColorEditWindow : Form
    {
        private readonly PaletteEditPanel PalettePanel;
        private readonly Palette Palette;
        private readonly int Index;

        private ColorEditWindow()
        {
            InitializeComponent();
        }

        public ColorEditWindow(PaletteEditPanel palettePanel, Palette palette, int index, Point pos)
        {
            InitializeComponent();

            StartPosition = FormStartPosition.Manual;
            Location = pos;
            PalettePanel = palettePanel;
            Palette = palette;
            Index = index;
            Text = index.ToString();
            TxtColor.KeyDown += TxtColor_KeyDown;
            TxtColor.KeyUp += TxtColor_KeyUp;

            TxtOriginal.Text = palette.Get(index).ToString("X06");
            TxtColor.Text = palette.Get(index).ToString("X06");

            UpdateSwatches();
        }

        private void UpdateSwatches()
        {
            int rgb;
            bool ok = int.TryParse(TxtColor.Text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out rgb);
            if (!ok)
                return;

            PnlColor.BackColor = Color.FromArgb(255, Color.FromArgb(rgb));
            
            ok = int.TryParse(TxtOriginal.Text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out rgb);
            if (!ok)
                return;

            PnlOriginal.BackColor = Color.FromArgb(255, Color.FromArgb(rgb));
        }

        private void TxtColor_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (TxtColor.TextLength == 6)
                    DialogResult = DialogResult.OK;
                else
                    DialogResult = DialogResult.Cancel;
            }
            else if (e.KeyCode == Keys.Escape)
            {
                DialogResult = DialogResult.Cancel;
            }
        }

        private void TxtColor_KeyUp(object sender, KeyEventArgs e)
        {
            if (TxtColor.TextLength == 6)
            {
                UpdateSwatches();
            }
        }

        public int GetSelectedColor()
        {
            return int.TryParse(TxtColor.Text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out int rgb) ? rgb : 0;
        }
    }
}
