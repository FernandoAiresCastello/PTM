using System.IO;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public static class DefaultTileset
    {
		private static Tileset tileset;

        public static void Init(Tileset t)
        {
            tileset = t;
            tileset.ClearToSize(0);

            if (File.Exists(Filesystem.DefaultTilesetFile))
			{
				LoadDefault();
				return;
			}
		}

		private static void LoadDefault()
		{
			foreach (var line in File.ReadAllLines(Filesystem.DefaultTilesetFile))
                tileset.Add(line);
        }
	}
}
