using System.Globalization;
using System.IO;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public class DefaultPalette
    {
        private static Palette palette;

        public static void Init(Palette p)
        {
			palette = p;
			palette.Clear();

            if (File.Exists(Filesystem.DefaultPaletteFile))
            {
                LoadDefault();
                return;
            }
		}

        private static void LoadDefault()
        {
            int i = 0;

            foreach (var line in File.ReadAllLines(Filesystem.DefaultPaletteFile))
                palette.Set(i++, int.Parse(line, NumberStyles.HexNumber));
        }
    }
}
