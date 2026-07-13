using PTMStudio.Core;
using PTMStudio.Windows;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.File;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace PTMStudio
{
	public partial class TilebufferEditPanel : UserControl
    {
		private readonly MainWindow MainWindow;
        private readonly TiledDisplay Display;
        private MapRenderer Renderer;
        private ObjectMap TileBuffer;
        private readonly Size TileBufferSize = new Size(41, 23);
		private readonly Project Proj;
		private static readonly Random random = new Random();
		private bool TextMode = false;
        private bool SelectionMode = false;
        private Point? SelectionTopLeft = null;
		private Point? SelectionBtmRight = null;
        private bool HasSelection => SelectionTopLeft != null && SelectionBtmRight != null;
        private readonly List<GameObject> ClipboardObjects = new List<GameObject>();
        private Size ClipboardSize;

		public string Filename { get; private set; }

        private TilebufferEditPanel()
        {
            InitializeComponent();
        }

        public TilebufferEditPanel(MainWindow mainWnd, Tileset tileset, Palette palette)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Display = new TiledDisplay(DisplayPanel, TileBufferSize.Width, TileBufferSize.Height, 2);
            Display.Graphics.Palette = palette;
            Display.Graphics.Tileset = tileset;
            Display.Graphics.Clear(0);
            Display.ShowGrid = true;
            Display.Parent = DisplayPanel;
			Display.MouseDown += Display_MouseDown;
			Display.MouseClick += Display_MouseClick;
            Display.MouseMove += Display_MouseMove;
            Display.MouseLeave += Display_MouseLeave;

            Proj = new Project
            {
                Palette = palette,
                Tileset = tileset
            };

            CreateNewBuffer();

            LbPos.Text = "";
			LbPos.BorderSides = ToolStripStatusLabelBorderSides.None;
			LbObject.Text = "";
			LbObject.BorderSides = ToolStripStatusLabelBorderSides.None;
			LbSelection.Text = "";
			LbSelection.BorderSides = ToolStripStatusLabelBorderSides.None;

			UpdateSizeLabel();
        }

        private void UpdateSizeLabel()
        {
            LbSize.Text = $"{TileBuffer.Width} x {TileBuffer.Height}";
        }

        private void Display_MouseLeave(object sender, EventArgs e)
        {
            LbPos.Text = "";
            LbPos.BorderSides = ToolStripStatusLabelBorderSides.None;
			LbObject.Text = "";
            LbObject.BorderSides = ToolStripStatusLabelBorderSides.None;
		}

		private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            Point pos = Display.GetMouseToCellPos(e.Location);
            int x = pos.X;
            int y = pos.Y;

            if (x < 0 || y < 0 || x >= TileBuffer.Width || y >= TileBuffer.Height)
                return;

            LbPos.Text = string.Format("X: {0} Y: {1}", pos.X, pos.Y);
			LbPos.BorderSides = ToolStripStatusLabelBorderSides.Left;

            GameObject o = GetObjectAt(pos.X, pos.Y);

            if (o != null)
            {
                LbObject.Text = "OBJ ";
                LbObject.BorderSides = ToolStripStatusLabelBorderSides.Left;

                if (o.Properties.Entries.Count > 0)
                {
                    var props = new List<string>();
                    foreach (var prop in o.Properties.Entries)
                        props.Add($"{prop.Key}={prop.Value}");

                    LbObject.Text += string.Join(" | ", props);
                }
			}
            else
            {
                LbObject.Text = "";
				LbObject.BorderSides = ToolStripStatusLabelBorderSides.None;
			}

			if (e.Button != MouseButtons.None)
                Display_MouseDown(sender, e);
        }

		private void Display_MouseDown(object sender, MouseEventArgs e)
        {
            if (ModifierKeys == Keys.Control)
                return;

			Point pos = Display.GetMouseToCellPos(e.Location);
			int x = pos.X;
			int y = pos.Y;

			if (x >= 0 && y >= 0 && x < TileBuffer.Width && y < TileBuffer.Height)
			{
				if (SelectionMode)
				{
					if (e.Button == MouseButtons.Left)
						SelectTiles(pos);
					else if (e.Button == MouseButtons.Right || e.Button == MouseButtons.Middle)
						DeselectAllTiles();
				}
				else if (TextMode)
				{
					if (e.Button == MouseButtons.Left)
						PrintText(x, y, false);
					else if (e.Button == MouseButtons.Right)
						PrintText(x, y, true);
				}
				else
				{
					if (e.Button == MouseButtons.Left)
						PutTile(x, y);
					else if (e.Button == MouseButtons.Right)
						GrabTile(x, y);
					else if (e.Button == MouseButtons.Middle)
						DeleteTile(x, y);
				}
			}
		}

		private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            if (SelectionMode || TextMode)
                return;

			Point pos = Display.GetMouseToCellPos(e.Location);
			int x = pos.X;
			int y = pos.Y;

            if (x >= 0 && y >= 0 && x < TileBuffer.Width && y < TileBuffer.Height)
            {
                if (e.Button == MouseButtons.Left && ModifierKeys == Keys.Control)
                    AppendTile(x, y);
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
                TileBuffer.SetObject(tile, new ObjectPosition(0, x, y));
                UpdateDisplay();
                MainWindow.TilebufferChanged(true);
            }
            else
            {
                AlertEmptyTileRegister();
            }
        }

		private void AppendTile(int x, int y)
        {
			GameObject tile = MainWindow.GetTileRegister();

			if (tile.Animation.Frames.Count > 0)
			{
                GameObject o = TileBuffer.GetObject(new ObjectPosition(0, x, y));
                if (o == null)
                    return;

                foreach (var frame in tile.Animation.Frames)
                    o.Animation.AddFrame(frame);
				
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
            TileBuffer.DeleteObject(new ObjectPosition(0, x, y));
            MainWindow.TilebufferChanged(true);
        }

        private void GrabTile(int x, int y)
        {
            GameObject obj = GetObjectAt(x, y);

            if (obj != null)
            {
                MainWindow.SetTileRegister(obj);
            }
            else
            {
                MainWindow.Warning("No tile found at this buffer position");
            }
        }

		private GameObject GetObjectAt(int x, int y) => 
            TileBuffer.GetObject(new ObjectPosition(0, x, y));

		private GameObject GetObjectAt(Point pos) =>
			TileBuffer.GetObject(new ObjectPosition(0, pos));

		private void BtnSave_Click(object sender, EventArgs e) => SaveFile();
        private void BtnSetBgColor_Click(object sender, EventArgs e) => SelectBackColor();

        public void SaveFile()
        {
            if (string.IsNullOrWhiteSpace(Filename))
            {
				SimpleTextInputDialog dialog = new SimpleTextInputDialog("Save tilebuffer file", "Enter file name:")
				{
					UppercaseOnly = true
				};

				if (dialog.ShowDialog(this) == DialogResult.OK)
					Filename = dialog.Text.ToUpper();
				else
					return;

				Filename = Filesystem.GetUserFilePath(Filename);
			}

			if (!Filename.EndsWith(KnownFileExtensions.TileBuffer))
				Filename += KnownFileExtensions.TileBuffer;

			new TilebufferFile().Save(TileBuffer, Filename);
			TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(Filename);
			MainWindow.UpdateFilePanel();
			MainWindow.TilebufferChanged(false);
			MainWindow.CopyFileFromUsrFolderToProjectFolder(Filename);
		}

        public void LoadFile(string file, bool showPanel)
        {
            TileBuffer = new TilebufferFile().Load(Proj, file);
            Filename = file;
            TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(file);
            Renderer.Map = TileBuffer;
            UpdateDisplay();
            UpdateSizeLabel();
            MainWindow.TilebufferChanged(false);

            if (showPanel)
			    MainWindow.ShowTilebufferEditor();
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

        private void BtnFill_Click(object sender, EventArgs e) => FillBuffer();

        private void FillBuffer()
        {
            GameObject tile = MainWindow.GetTileRegister();

            if (!HasSelection)
            {
                if (!MainWindow.Confirm("Fill entire tile buffer with current tile register?"))
                    return;
            }

            if (HasSelection)
                TileBuffer.SetObjects(tile, GetSelectedObjectPositions());
            else
				TileBuffer.Fill(tile, 0);

			MainWindow.TilebufferChanged(true);
        }

        private void DeleteTiles()
        {
            if (!HasSelection)
            {
                if (!MainWindow.Confirm("Delete all tiles?"))
                    return;
            }

            if (HasSelection)
                foreach (var pos in GetSelectedObjectPositions())
                    TileBuffer.DeleteObject(pos);
            else
                TileBuffer.Clear(0);

            MainWindow.TilebufferChanged(true);
        }

		private void BtnClear_Click(object sender, EventArgs e) => DeleteTiles();
		private void BtnZoomIn_Click(object sender, EventArgs e) => Display.ZoomIn();
		private void BtnZoomOut_Click(object sender, EventArgs e) => Display.ZoomOut();
		private void BtnNew_Click(object sender, EventArgs e) => CreateNewBuffer();

        private void CreateNewBuffer()
        {
			TileBuffer = new ObjectMap(Proj, 1, TileBufferSize.Width, TileBufferSize.Height)
			{
				BackColorIndex = 15
			};

			if (Renderer == null)
                Renderer = new MapRenderer(TileBuffer, Display);
            else
                Renderer.Map = TileBuffer;

            Renderer.AnimationInterval = MainWindow.TileAnimationInterval;

			Filename = null;
            TxtFilename.Text = GlobalConstants.Unsaved;

            UpdateDisplay();
            UpdateSizeLabel();
            MainWindow.TilebufferChanged(false);
        }

		private void BtnText_Click(object sender, EventArgs e)
		{
            TextMode = BtnText.Checked;
            BtnSelect.Checked = SelectionMode = false;
		}

        private void PrintText(int x, int y, bool vertical)
        {
			Tile tile = MainWindow.GetTileRegisterFrame();

			SimpleTextInputDialog dialog = new SimpleTextInputDialog(
                "Print text", "Enter text " + (vertical ? "(vertical mode):" : "(horizontal mode):"));

			if (dialog.ShowDialog(MainWindow) != DialogResult.OK)
				return;

            if (vertical)
				TileBuffer.SetVerticalStringOfObjects(dialog.Text,
					new ObjectPosition(0, x, y), tile.ForeColor, tile.BackColor);
			else
				TileBuffer.SetHorizontalStringOfObjects(dialog.Text, 
                    new ObjectPosition(0, x, y), tile.ForeColor, tile.BackColor);

			MainWindow.TilebufferChanged(true);
		}

		private void BtnToggleGrid_Click(object sender, EventArgs e)
		{
            Display.ShowGrid = BtnToggleGrid.Checked;
            Display.Refresh();
		}

		private void BtnSelect_Click(object sender, EventArgs e)
		{
            SelectionMode = BtnSelect.Checked;
            BtnText.Checked = TextMode = false;
		}

		private void SelectTiles(Point pos)
        {
            if (SelectionTopLeft == null || (pos.X < SelectionTopLeft.Value.X || pos.Y < SelectionTopLeft.Value.Y))
            {
                SelectionTopLeft = pos;
                SelectionBtmRight = pos;
				Display.DeselectAllTiles();
				Display.SelectTile(pos);
                Display.Refresh();
                UpdateSelectionStatusLabel();
				return;
            }

            SelectionBtmRight = pos;

            Display.SelectTiles(GetSelectedPoints());
			Display.Refresh();
			UpdateSelectionStatusLabel();
		}

        private void UpdateSelectionStatusLabel()
        {
            if (HasSelection)
            {
                int w = SelectionBtmRight.Value.X - SelectionTopLeft.Value.X + 1;
                int h = SelectionBtmRight.Value.Y - SelectionTopLeft.Value.Y + 1;

				LbSelection.Text = $"Selection: {w} x {h} (total: {w * h})";
				LbSelection.BorderSides = ToolStripStatusLabelBorderSides.Left;
			}
			else
            {
                LbSelection.Text = "";
                LbSelection.BorderSides = ToolStripStatusLabelBorderSides.None;
            }
		}

		private List<Point> GetSelectedPoints()
        {
            if (SelectionTopLeft == null || SelectionBtmRight == null)
                return new List<Point>();

            return GetPointsInsideRectangle(SelectionTopLeft, SelectionBtmRight);
		}

		private List<ObjectPosition> GetSelectedObjectPositions() => 
            GetObjectPositions(GetSelectedPoints());

		private List<ObjectPosition> GetObjectPositions(Point topLeft, Point btmRight) => 
            GetObjectPositions(GetPointsInsideRectangle(topLeft, btmRight));

		private List<ObjectPosition> GetObjectPositions(List<Point> points)
        {
			var positions = new List<ObjectPosition>();

			foreach (var point in points)
				positions.Add(new ObjectPosition(0, point));

			return positions;
		}

		private static List<Point> GetPointsInsideRectangle(Point? topLeft, Point? bottomRight)
		{
			var points = new List<Point>();

			for (int y = topLeft.Value.Y; y <= bottomRight.Value.Y; y++)
				for (int x = topLeft.Value.X; x <= bottomRight.Value.X; x++)
					points.Add(new Point(x, y));

			return points;
		}

		private void DeselectAllTiles()
		{
            SelectionTopLeft = null;
            SelectionBtmRight = null;
            Display.DeselectAllTiles();
			Display.Refresh();
			UpdateSelectionStatusLabel();
		}

		private void BtnDeselect_Click(object sender, EventArgs e) => DeselectAllTiles();
		private void BtnSetRandomly_Click(object sender, EventArgs e) => SetObjectsRandomly();

		private void SetObjectsRandomly()
        {
			SimpleTextInputDialog dialog = new SimpleTextInputDialog("Set objects randomly", "Enter spawn rate (0-100):");
			if (dialog.ShowDialog(MainWindow) != DialogResult.OK)
				return;

			if (!int.TryParse(dialog.Text, out int rate))
				return;

			Point topLeft, btmRight;

			if (HasSelection)
			{
				topLeft = SelectionTopLeft.Value;
				btmRight = SelectionBtmRight.Value;
			}
			else
			{
				topLeft = new Point(0, 0);
				btmRight = new Point(TileBuffer.Width - 1, TileBuffer.Height - 1);
			}

			GameObject tile = MainWindow.GetTileRegister();

			foreach (var pos in GetObjectPositions(topLeft, btmRight))
			{
				if (Chance(rate))
					TileBuffer.SetObject(tile, pos);
			}

			MainWindow.TilebufferChanged(true);
		}

		private static bool Chance(int percentage)
		{
			if (percentage < 0 || percentage > 100)
				throw new ArgumentOutOfRangeException(nameof(percentage), "Percentage must be between 0 and 100.");

			return random.Next(100) < percentage;
		}

		private void BtnCopy_Click(object sender, EventArgs e) => CopySelectedTiles(true);
		private void BtnPaste_Click(object sender, EventArgs e) => PasteSelectedTiles();

		private void CopySelectedTiles(bool deselectAfter)
        {
            if (!HasSelection)
            {
                MainWindow.Warning("Can't copy tiles without a selection rectangle.");
                return;
            }

			int w = SelectionBtmRight.Value.X - SelectionTopLeft.Value.X;
			int h = SelectionBtmRight.Value.Y - SelectionTopLeft.Value.Y;
			ClipboardSize = new Size(w, h);
			ClipboardObjects.Clear();

            foreach (var pos in GetSelectedPoints())
                ClipboardObjects.Add(GetObjectAt(pos)?.Copy());

            if (deselectAfter)
                DeselectAllTiles();
		}

		private void PasteSelectedTiles()
		{
            if (!HasSelection)
            {
				MainWindow.Warning("Can't paste tiles without a selected position.");
				return;
            }

            int initialY = SelectionTopLeft.Value.Y;
			int initialX = SelectionTopLeft.Value.X;
            int clipboardIndex = 0;

            for (int y = initialY; y <= initialY + ClipboardSize.Height; y++)
            {
                for (int x = initialX; x <= initialX + ClipboardSize.Width; x++)
                {
                    GameObject o = ClipboardObjects[clipboardIndex++];
                    
                    if (o != null)
                    {
                        try
                        {
                            TileBuffer.SetObject(o, new ObjectPosition(0, x, y));
                        }
                        catch
                        {
                        }
                    }
                }
            }

			DeselectAllTiles();
			Display.Refresh();
            MainWindow.TilebufferChanged(true);
		}

		private void BtnCut_Click(object sender, EventArgs e)
		{
			if (!HasSelection)
			{
				MainWindow.Warning("Can't cut tiles without a selection rectangle.");
				return;
			}

			CopySelectedTiles(false);

			foreach (var pos in GetSelectedObjectPositions())
				TileBuffer.DeleteObject(pos);

			DeselectAllTiles();
			Display.Refresh();
			MainWindow.TilebufferChanged(true);
		}
	}
}
