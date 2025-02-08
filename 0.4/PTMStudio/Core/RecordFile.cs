using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using TileGameLib.File;

namespace PTMStudio.Core
{
	public class RecordFile
	{
		private const char Separator = '§';
		
		private readonly StringBuilder OutputBuffer = new StringBuilder();
		private List<string> LoadedContents = new List<string>();
		private int Ptr;

		public void Append(object o) => OutputBuffer.Append((o != null ? o.ToString() : "") + Separator.ToString());
		public string NextStr() => LoadedContents[Ptr++];
		public int NextInt() => int.Parse(LoadedContents[Ptr++]);

		public RecordFile()
		{
			OutputBuffer.Append(Separator); // Append the first separator character
		}

		public void Load(string path)
		{
			string input = Encoding.Default.GetString(File.ReadAllBytes(path));
			input = input.Substring(1); // Remove the first separator character
			LoadedContents = input.Split(Separator).ToList();
			OutputBuffer.Clear();
			Ptr = 0;
		}

		public void Save(string path)
		{
			MemoryFile file = new MemoryFile();
			file.WriteString(OutputBuffer.ToString());
			file.SaveToPhysicalFile(path);

			OutputBuffer.Clear();
			LoadedContents.Clear();
		}
	}
}
