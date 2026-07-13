using PTMStudio.Core;
using TileGameLib.File;
using TileGameLib.GameElements;
using TileGameLib.Graphics;

namespace PTMStudio
{
	public class TilebufferFile
    {
        private RecordFile RecFile;

        public ObjectMap Load(Project proj, string path)
        {
            RecFile = new RecordFile();
			RecFile.Load(path);

            int width = RecFile.NextInt();
            int height = RecFile.NextInt();
            int layers = RecFile.NextInt();

            ObjectMap buf = new ObjectMap(proj, layers, width, height)
            {
                BackColorIndex = RecFile.NextInt()
            };

            for (int i = 0; i < layers; i++)
                LoadLayer(buf.Layers[i]);

            return buf;
        }

        private void LoadLayer(ObjectLayer layer)
        {
            for (int y = 0; y < layer.Height; y++)
            {
                for (int x = 0; x < layer.Width; x++)
                {
                    int exists = RecFile.NextInt();
                    if (exists != 1)
                        continue;

                    GameObject o = new GameObject();
                    o.Animation.Clear();
                    o.Transparent = RecFile.NextInt() == 1;

                    int frames = RecFile.NextInt();
                    for (int i = 0; i < frames; i++)
                    {
                        int ch = RecFile.NextInt();
                        int fgc = RecFile.NextInt();
                        int bgc = RecFile.NextInt();
                        o.Animation.AddFrame(new Tile(ch, fgc, bgc));
                    }

                    int props = RecFile.NextInt();
                    for (int i = 0; i < props; i++)
                    {
                        string prop = RecFile.NextStr();
                        string value = RecFile.NextStr();
                        o.Properties.Set(prop, value);
                    }

                    layer.SetObject(o, x, y);
                }
            }
        }

        public void Save(ObjectMap tilebuf, string path)
        {
            RecFile = new RecordFile();

			RecFile.Append(tilebuf.Width);
			RecFile.Append(tilebuf.Height);
			RecFile.Append(tilebuf.Layers.Count);
			RecFile.Append(tilebuf.BackColorIndex);

            foreach (ObjectLayer layer in tilebuf.Layers)
                SaveLayer(layer);

            RecFile.Save(path);
        }

        private void SaveLayer(ObjectLayer layer)
        {
            for (int y = 0; y < layer.Height; y++)
            {
                for (int x = 0; x < layer.Width; x++)
                {
                    GameObject o = layer.GetObject(x, y);

                    if (o != null)
                    {
						RecFile.Append(1);

                        RecFile.Append(o.Transparent ? 1 : 0);

                        RecFile.Append(o.Animation.Size);
                        foreach (Tile tile in o.Animation.Frames)
                        {
                            RecFile.Append((short)tile.Index);
                            RecFile.Append((byte)tile.ForeColor);
                            RecFile.Append((byte)tile.BackColor);
                        }

                        RecFile.Append(o.Properties.Entries.Count);
                        foreach (var property in o.Properties.Entries)
                        {
                            RecFile.Append(property.Key);
                            RecFile.Append(property.Value);
                        }
                    }
                    else
                    {
                        RecFile.Append(0);
                    }
                }
            }
        }
    }
}
