namespace PTMStudio.Core
{
	public class ProjectFolder
	{
		public string Path { set; get; }
		public string Name { set; get; }

		public ProjectFolder(string path, string name)
		{
			Path = path;
			Name = name;
		}

		public override string ToString()
		{
			return Name;
		}
	}
}
