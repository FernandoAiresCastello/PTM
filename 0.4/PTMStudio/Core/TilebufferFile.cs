using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TileGameLib.File;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace PTMStudio
{
    public class TilebufferFile
    {
        private static readonly char Separator = '§';

        private static StringBuilder text;
        private static string[] file;
        private static int ptr;

        private static void Append(object o) => text.Append((o != null ? o.ToString() : "") + Separator.ToString());
        private static string NextStr() => file[ptr++];
        private static int NextInt() => int.Parse(file[ptr++]);

        public static ObjectMap Load(Project proj, string path)
        {
            string input = Encoding.Default.GetString(File.ReadAllBytes(path));
            file = input.Split(Separator);
            ptr = 0;

            int width = NextInt();
            int height = NextInt();
            int layers = NextInt();

            ObjectMap buf = new ObjectMap(proj, layers, width, height)
            {
                BackColorIndex = NextInt()
            };

            for (int i = 0; i < layers; i++)
                LoadLayer(buf.Layers[i]);

            return buf;
        }

        private static void LoadLayer(ObjectLayer layer)
        {
            for (int y = 0; y < layer.Height; y++)
            {
                for (int x = 0; x < layer.Width; x++)
                {
                    int exists = NextInt();
                    if (exists != 1)
                        continue;

                    GameObject o = new GameObject();
                    o.Animation.Clear();
                    o.Transparent = NextInt() == 1;

                    int frames = NextInt();
                    for (int i = 0; i < frames; i++)
                    {
                        int ch = NextInt();
                        int fgc = NextInt();
                        int bgc = NextInt();
                        o.Animation.AddFrame(new Tile(ch, fgc, bgc));
                    }

                    int props = NextInt();
                    for (int i = 0; i < props; i++)
                    {
                        string prop = NextStr();
                        string value = NextStr();
                        o.Properties.Set(prop, value);
                    }

                    layer.SetObject(o, x, y);
                }
            }
        }

        public static void Save(ObjectMap tilebuf, string path)
        {
            text = new StringBuilder();

            Append(tilebuf.Width);
            Append(tilebuf.Height);
            Append(tilebuf.Layers.Count);
            Append(tilebuf.BackColorIndex);

            foreach (ObjectLayer layer in tilebuf.Layers)
                SaveLayer(layer);
            
            MemoryFile file = new MemoryFile();
            file.WriteString(text.ToString());
            file.SaveToPhysicalFile(path);
        }

        private static void SaveLayer(ObjectLayer layer)
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
