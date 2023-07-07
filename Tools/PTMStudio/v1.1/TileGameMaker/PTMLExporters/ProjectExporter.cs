using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TileGameLib.File;
using TileGameLib.GameElements;
using TileGameLib.Graphics;
using TileGameLib.Util;
using TileGameMaker.MapEditorElements;

namespace TileGameMaker.PTMLExporters
{
    public class ProjectExporter
    {
        public static void ExportEverything(Project proj)
        {
            string folder = proj.Folder;
            string chrFile = Path.Combine(folder, proj.Name + ".chr.dat");
            string palFile = Path.Combine(folder, proj.Name + ".pal.dat");

            TilesetFile.Export(TilesetExportFormat.BinaryStrings, proj.Tileset, chrFile);
            PaletteFile.Export(PaletteExportFormat.HexadecimalRgb, proj.Palette, palFile);

            foreach (ObjectMap tilebuf in proj.Maps)
            {
                string bufFile = Path.Combine(folder, tilebuf.Id + ".buf.dat");
                TilebufferExporter.Export(tilebuf, bufFile);
            }
        }

        public static void ExportGraphics(string programFileName, string folderPath, Tileset tileset, Palette palette)
        {
            string chrFile = Path.Combine(folderPath, programFileName + ".chr.dat");
            string palFile = Path.Combine(folderPath, programFileName + ".pal.dat");

            TilesetFile.Export(TilesetExportFormat.BinaryStrings, tileset, chrFile);
            PaletteFile.Export(PaletteExportFormat.HexadecimalRgb, palette, palFile);
        }
    }
}
