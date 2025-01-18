using System;
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
        private readonly Project Proj;

        public string Filename { get; private set; }

        private TilebufferEditPanel()
        {
            InitializeComponent();
        }

        public TilebufferEditPanel(MainWindow mainWnd, Tileset tileset, Palette palette)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Display = new TiledDisplay(DisplayPanel, 45, 25, 2)
            {
                Parent = DisplayPanel
            };

            Display.Graphics.Palette = palette;
            Display.Graphics.Tileset = tileset;
            Display.Graphics.Clear(0);
            Display.ShowGrid = true;
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
            UpdateSizeLabel();
        }

        private void UpdateSizeLabel()
        {
            LbSize.Text = $"{TileBuffer.Width} x {TileBuffer.Height}";
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
                TileBuffer.SetObject(tile, new ObjectPosition(0, x, y));
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
            GameObject obj = TileBuffer.GetObject(new ObjectPosition(0, x, y));

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
                SaveFileDialog dialog = new SaveFileDialog
                {
                    InitialDirectory = Filesystem.UserRoot,
                    Filter = "PTM Tilebuffer File (*.buf)|*.buf"
                };
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
                bool ok = MainWindow.Confirm("Fill entire tilebuffer with current tile register?");

                if (ok)
                {
                    TileBuffer.Fill(tile, 0);
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
            bool ok = MainWindow.Confirm("Delete all tiles?");

            if (ok)
            {
                TileBuffer.Clear(0);
                MainWindow.TilebufferChanged(true);
            }
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
			TileBuffer = new ObjectMap(Proj, 1, 45, 25)
			{
				BackColorIndex = 15
			};

			if (Renderer == null)
                Renderer = new MapRenderer(TileBuffer, Display);
            else
                Renderer.Map = TileBuffer;

            Filename = null;
            TxtFilename.Text = "<Unsaved>";

            UpdateDisplay();
            UpdateSizeLabel();
            MainWindow.TilebufferChanged(false);
        }
    }
}
