using PTMStudio.Core;
using PTMStudio.Windows;
using System;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.File;
using TileGameLib.Graphics;

namespace PTMStudio
{
	public partial class PaletteEditPanel : UserControl
    {
		public string Filename { get; private set; }
		public Palette Palette { get => Display.Graphics.Palette; }
		
        private readonly MainWindow MainWindow;
        private readonly TiledDisplay Display;
        private int FirstColor = 0;
        private readonly int MaxColors;
        private int? SelectedColorIndexForMoving = null;

        private PaletteEditPanel()
        {
            InitializeComponent();
		}

        public PaletteEditPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Display = new TiledDisplay(PnlPalette, 16, 16, 2)
            {
                ShowGrid = true,
                Cursor = Cursors.Hand
            };

            Display.SetMainGridColor(Color.FromArgb(80, 128, 128, 128));
            Display.MouseWheel += Display_MouseWheel;
            Display.MouseMove += Display_MouseMove;
            Display.MouseLeave += Display_MouseLeave;
            Display.MouseClick += Display_MouseClick;
            Display.MouseDoubleClick += Display_MouseDoubleClick;
			Display.MouseDown += Display_MouseDown;
			Display.MouseUp += Display_MouseUp;

			MaxColors = Display.Graphics.Cols * Display.Graphics.Rows;

			UpdateDisplay();
        }

		private void Display_MouseDown(object sender, MouseEventArgs e)
		{
            if (!BtnArrange.Checked || e.Button != MouseButtons.Left)
                return;

            if (SelectedColorIndexForMoving == null)
				SelectedColorIndexForMoving = GetColorIndexFromMousePos(e.Location);
		}

		private void Display_MouseUp(object sender, MouseEventArgs e)
		{
			if (!BtnArrange.Checked || e.Button != MouseButtons.Left)
				return;

            Point pos = GetColorPosFromMousePos(e.Location);
            if (pos.X < 0 || pos.Y < 0 || pos.X >= Display.Cols || pos.Y >= Display.Rows)
            {
                SelectedColorIndexForMoving = null;
				return;
            }

			if (SelectedColorIndexForMoving != null)
            {
				int startingColor = Palette.Get(SelectedColorIndexForMoving.Value);
                int destinationIndex = GetColorIndexFromMousePos(e.Location);
				int destinationColor = Palette.Get(destinationIndex);

				// Copy the starting color to the destination index
				Palette.Set(destinationIndex, startingColor);
                // Copy the destination color back to the starting index
                Palette.Set(SelectedColorIndexForMoving.Value, destinationColor);

				SelectedColorIndexForMoving = null;
				UpdateDisplay();

                MainWindow.PaletteChanged(true);
			}
		}

		private void Display_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                ScrollDisplay(-1);
            else
                ScrollDisplay(1);
        }

        public void UpdateDisplay()
        {
            Display.Graphics.Clear(0);

            int i = FirstColor;

            for (int y = 0; y < Display.Rows; y++)
            {
                for (int x = 0; x < Display.Cols; x++)
                {
                    if (i < Display.Graphics.Palette.Size)
                        Display.Graphics.PutTile(x, y, 0, i, i, false);

                    i++;
                }
            }

            Display.Refresh();
            UpdateIndicator();
        }

        public void LoadFile(string file)
        {
            Display.Graphics.Palette.Clear(256);
            int i = 0;
            foreach (var line in File.ReadAllLines(file))
                Display.Graphics.Palette.Set(i++, int.Parse(line, NumberStyles.HexNumber));

            FirstColor = 0;
            Filename = file;
            TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(file);
            MainWindow.PaletteChanged(false);
            UpdateDisplay();
        }

        private void BtnNext_Click(object sender, EventArgs e)
        {
            ScrollDisplay(1);
        }

        private void BtnPrev_Click(object sender, EventArgs e)
        {
            ScrollDisplay(-1);
        }

        private void ScrollDisplay(int rows)
        {
            int first = FirstColor + (Display.Cols * rows);

            if (first >= 0 && first <= Palette.Size - (Display.Cols * Display.Rows))
                FirstColor = first;

            UpdateDisplay();
        }

        private string GetIndicator()
        {
            return FirstColor + "-" + (FirstColor + MaxColors - 1) + "/" + Display.Graphics.Palette.Size;
        }

        private void UpdateIndicator()
        {
            LblIndicator.Text = GetIndicator();
        }

        private void Display_MouseLeave(object sender, EventArgs e)
        {
            UpdateIndicator();
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            int ix = GetColorIndexFromMousePos(e.Location);
            LblIndicator.Text = GetIndicator() + " (" + ix + ")";
        }

        private int GetColorIndexFromMousePos(Point mousePos)
        {
            return FirstColor + Display.GetMouseToCellIndex(mousePos);
        }

		private Point GetColorPosFromMousePos(Point mousePos)
		{
			return Display.GetMouseToCellPos(mousePos);
		}

		private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            int ix = GetColorIndexFromMousePos(e.Location);
            if (ix < 0 || ix >= Display.Graphics.Palette.Size)
            {
                AlertIndexOutOfBounds();
                return;
            }

            if (e.Button == MouseButtons.Left)
                SelectForeColor(ix);
            else if (e.Button == MouseButtons.Right)
                SelectBackColor(ix);
        }

        private void SelectForeColor(int index)
        {
            MainWindow.SetTileRegisterForeColor(index);
        }

        private void SelectBackColor(int index)
        {
            MainWindow.SetTileRegisterBackColor(index);
        }

        private void Display_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            int ix = GetColorIndexFromMousePos(e.Location);

            if (e.Button == MouseButtons.Left)
                EditColor(ix, MousePosition);
        }

        private void AlertIndexOutOfBounds()
        {
            MainWindow.Warning("Color index out of bounds");
        }

        private void EditColor(int index, Point windowPos)
        {
            if (index < 0 || index >= Display.Graphics.Palette.Size)
            {
                AlertIndexOutOfBounds();
                return;
            }

            ColorEditWindow wnd = new ColorEditWindow(this, Display.Graphics.Palette, index, windowPos);
            
            if (wnd.ShowDialog(this) == DialogResult.OK)
            {
                Display.Graphics.Palette.Set(index, wnd.GetSelectedColor());
                UpdateDisplay();
                MainWindow.UpdateTilebufferEditorDisplay();
                MainWindow.UpdateTileRegisterPanelDisplay();
                MainWindow.PaletteChanged(true);
            }
        }

        private void BtnSave_Click(object sender, EventArgs e)
        {
            SaveFile();
        }

        public void SaveFile()
        {
            if (string.IsNullOrWhiteSpace(Filename))
            {
                SimpleTextInputDialog dialog = new SimpleTextInputDialog("Save palette file", "Enter file name:")
                {
                    UppercaseOnly = true
                };

                if (dialog.ShowDialog(this) == DialogResult.OK)
                    Filename = dialog.Text.ToUpper();
                else
                    return;

				Filename = Filesystem.GetUserFilePath(Filename);
			}

			if (!Filename.EndsWith(KnownFileExtensions.Palette))
				Filename += KnownFileExtensions.Palette;

			PaletteFile.SaveAsHexadecimalRgb(Display.Graphics.Palette, Filename);
			TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(Filename);
			MainWindow.UpdateFilePanel();
            MainWindow.PaletteChanged(false);
        }

        private void BtnNew_Click(object sender, EventArgs e)
        {
            Display.Graphics.Palette.SetEmpty();
            for (int i = 0; i < 256; i++)
                Display.Graphics.Palette.Add(0xffffff);

			Filename = null;
            TxtFilename.Text = "<Unsaved>";
            FirstColor = 0;
            MainWindow.PaletteChanged(false);
            UpdateDisplay();
        }

		private void BtnArrange_Click(object sender, EventArgs e)
		{
		}
	}
}
