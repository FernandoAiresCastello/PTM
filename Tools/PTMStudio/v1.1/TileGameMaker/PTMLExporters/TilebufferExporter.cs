using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TileGameLib.File;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace TileGameMaker.PTMLExporters
{
    public class TilebufferExporter
    {
        private static readonly char Separator = '§';

        static StringBuilder text;
        static void Append(object o) => text.Append((o != null ? o.ToString() : "") + Separator.ToString());

        public static void Export(ObjectMap tilebuf, string path)
        {
            text = new StringBuilder();

            Append(tilebuf.Width);
            Append(tilebuf.Height);
            Append(tilebuf.Layers.Count);
            Append(tilebuf.BackColorIndex);

            foreach (ObjectLayer layer in tilebuf.Layers)
                ExportLayer(layer);
            
            MemoryFile file = new MemoryFile();
            file.WriteString(text.ToString());
            file.SaveToPhysicalFile(path);
        }

        private static void ExportLayer(ObjectLayer layer)
        {
            for (int y = 0; y < layer.Height; y++)
            {
                for (int x = 0; x < layer.Width; x++)
                {
                    GameObject o = layer.GetObject(x, y);

                    if (o != null)
                    {
                        Append(1);

                        Append(o.Transparent ? 1 : 0);

                        Append(o.Animation.Size);
                        foreach (Tile tile in o.Animation.Frames)
                        {
                            Append((short)tile.Index);
                            Append((byte)tile.ForeColor);
                            Append((byte)tile.BackColor);
                        }

                        Append(o.Properties.Entries.Count);
                        foreach (var property in o.Properties.Entries)
                        {
                            Append(property.Key);
                            Append(property.Value);
                        }
                    }
                    else
                    {
                        Append(0);
                    }
                }
            }
        }
    }
}
