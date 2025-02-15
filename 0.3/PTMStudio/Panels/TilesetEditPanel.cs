using PTMStudio.Core;
using PTMStudio.Windows;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using TileGameLib.Components;
using TileGameLib.File;
using TileGameLib.Graphics;

namespace PTMStudio
{
	public partial class TilesetEditPanel : UserControl
    {
        private readonly MainWindow MainWindow;
        private readonly TiledDisplay Display;
        private readonly int MaxTiles;
        private int FirstTile = 0;
        
        public string Filename { get; private set; }

        public Tileset Tileset { get => Display.Graphics.Tileset; }

        private TilesetEditPanel()
        {
            InitializeComponent();
        }

        public TilesetEditPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;

            Display = new TiledDisplay(PnlTileset, 16, 16, 2);
            Display.Graphics.Clear(1);
            Display.ShowGrid = true;
            Display.Cursor = Cursors.Hand;
            Display.MouseClick += Display_MouseClick;
            Display.MouseDoubleClick += Display_MouseDoubleClick;
            Display.MouseMove += Display_MouseMove;
            Display.MouseLeave += Display_MouseLeave;
            Display.MouseWheel += Display_MouseWheel;

            MaxTiles = Display.Graphics.Cols * Display.Graphics.Rows;

			UpdateDisplay();
        }

        private void Display_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                ScrollDisplay(-1);
            else
                ScrollDisplay(1);
        }

        private void Display_MouseLeave(object sender, EventArgs e)
        {
            UpdateIndicator();
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            int ix = GetTileIndexFromMousePos(e.Location);
            LblIndicator.Text = GetIndicator() + " (" + ix + ")";
        }

        private void UpdateIndicator()
        {
            LblIndicator.Text = GetIndicator();
        }

        private void Display_MouseClick(object sender, MouseEventArgs e)
        {
            int ix = GetTileIndexFromMousePos(e.Location);
            if (ix < 0 || ix >= Display.Graphics.Tileset.Size)
            {
                AlertIndexOutOfBounds();
                return;
            }

            if (e.Button == MouseButtons.Left)
                SelectTile(ix);
        }

        private void SelectTile(int index)
        {
            MainWindow.SetTileRegisterTile(index);
        }

        private void Display_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            int ix = GetTileIndexFromMousePos(e.Location);

            if (e.Button == MouseButtons.Left)
                EditTile(ix);
        }

        private string GetIndicator()
        {
            return FirstTile + "-" + (FirstTile + MaxTiles - 1) + "/" + Display.Graphics.Tileset.Size;
        }

        private int GetTileIndexFromMousePos(Point mousePos)
        {
            return FirstTile + Display.GetMouseToCellIndex(mousePos);
        }

        public void UpdateDisplay()
        {
            Display.Graphics.Clear(1);

            int i = FirstTile;

            for (int y = 0; y < Display.Rows; y++)
            {
                for (int x = 0; x < Display.Cols; x++)
                {
                    if (i < Display.Graphics.Tileset.Size)
                        Display.Graphics.PutTile(x, y, i, 0, 1, false);
                    
                    i++;
                }
            }

            Display.Refresh();
            UpdateIndicator();
        }

        public void LoadFile(string file)
        {
            Display.Graphics.Tileset.ClearToSize(0);
            foreach (var line in File.ReadAllLines(file))
                Display.Graphics.Tileset.Add(line);

            FirstTile = 0;
            Filename = file;
            TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(file);
            MainWindow.TilesetChanged(false);
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
            int first = FirstTile + (Display.Cols * rows);

            if (first >= 0 && first <= Tileset.Size - (Display.Cols * Display.Rows))
                FirstTile = first;

            UpdateDisplay();
        }

        private void AlertIndexOutOfBounds()
        {
            MainWindow.Warning("Tile index out of bounds");
        }

        private void EditTile(int index)
        {
            if (index < 0 || index >= Display.Graphics.Tileset.Size)
            {
                AlertIndexOutOfBounds();
                return;
            }

            TileEditWindow wnd = new TileEditWindow(this, Display.Graphics.Tileset, index);
            wnd.ShowDialog(this);

            MainWindow.UpdateTilebufferEditorDisplay();
            MainWindow.UpdateTileRegisterPanelDisplay();
            MainWindow.TilesetChanged(true);
        }

        private void BtnSave_Click(object sender, EventArgs e)
        {
            SaveFile();
        }

        public void SaveFile()
        {
			if (string.IsNullOrWhiteSpace(Filename))
			{
                SimpleTextInputDialog dialog = new SimpleTextInputDialog("Save charset file", "Enter file name:")
                {
                    UppercaseOnly = true
                };

				if (dialog.ShowDialog(this) == DialogResult.OK)
					Filename = dialog.Text.ToUpper();
				else
					return;

				Filename = Filesystem.GetUserFilePath(Filename);
			}

            if (!Filename.EndsWith(KnownFileExtensions.Charset))
                Filename += KnownFileExtensions.Charset;

			TilesetFile.SaveAsBinaryStrings(Display.Graphics.Tileset, Filename);
			TxtFilename.Text = Filesystem.RemoveAbsoluteRootAndNormalizePath(Filename);
			MainWindow.UpdateFilePanel();
            MainWindow.TilesetChanged(false);
        }

        private void BtnNew_Click(object sender, EventArgs e)
        {
			LoadFile(Filesystem.DefaultTilesetFile);
			
            Filename = null;
            TxtFilename.Text = "<Unsaved>";
            FirstTile = 0;
            MainWindow.TilesetChanged(false);
            UpdateDisplay();
        }
    }
}
