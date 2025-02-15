using System;
using System.ComponentModel;
using System.IO;

namespace PTMStudio.Core
{
	public class HelpTopics
	{
		public readonly string HelpBaseDir = Path.Combine(Environment.CurrentDirectory, "HELP/");
		public readonly BindingList<CommandHelp> Commands = new BindingList<CommandHelp>();

		public HelpTopics()
		{
			//CreateInitialHtmlFiles();
			LoadCommands();
		}

		private void LoadCommands()
		{
			Commands.Clear();

			var files = Directory.EnumerateFiles(HelpBaseDir, "*.html");

			foreach (var file in files)
			{
				string filename = Path.GetFileNameWithoutExtension(file);
				if (filename == "_template")
					continue;

				Commands.Add(new CommandHelp(filename, file));
			}
		}

		private void CreateInitialHtmlFiles()
		{
			string[] lines = File.ReadAllLines($"{HelpBaseDir}commands.txt");
			string htmlTemplate = File.ReadAllText($"{HelpBaseDir}_template.html");

			foreach (string line in lines)
			{
				string[] lineParts = line.Split('|');
				string name = lineParts[0];
				string description = lineParts[1];

				string html = htmlTemplate
					.Replace("{CMD}", name)
					.Replace("{DESC}", description);

				File.WriteAllText($"{HelpBaseDir}{name}.html", html);
			}
		}
	}

	public class CommandHelp
	{
		public string Command;
		public string HtmlFilePath;

		public override string ToString() => Command;

		public CommandHelp(string command, string htmlFile)
		{
			Command = command;
			HtmlFilePath = htmlFile;
		}
	}
}
