using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio.Windows
{
	public partial class StartWindow : Form
	{
		public string ProjectFolder { get; private set; }

		public StartWindow()
		{
			InitializeComponent();
		}

		private void BtnExit_Click(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
		}

		private void BtnLoad_Click(object sender, System.EventArgs e)
		{
			ProjectLoadWindow wnd = new ProjectLoadWindow();
			if (wnd.ShowDialog(this) != DialogResult.OK)
				return;

			ProjectFolder = wnd.SelectedProject.Path;
			CopyFiles(ProjectFolder, Filesystem.UserRootDirName);
			DialogResult = DialogResult.OK;
		}

		private void BtnScratchpad_Click(object sender, System.EventArgs e)
		{
			ProjectFolder = Path.Combine(Filesystem.ProjectDirName, Filesystem.ScratchpadProjectFolder);
			if (!Directory.Exists(ProjectFolder))
				Directory.CreateDirectory(ProjectFolder);

			CopyFiles(ProjectFolder, Filesystem.UserRootDirName);
			DialogResult = DialogResult.OK;
		}

		private void BtnNew_Click(object sender, System.EventArgs e)
		{
			bool ok = false;

			while (!ok)
			{
				SimpleTextInputDialog dialog = new SimpleTextInputDialog(
					"Create new project", "Enter project name:")
				{ UppercaseOnly = true };

				string newProjectFolder;
				if (dialog.ShowDialog(this) == DialogResult.OK)
					newProjectFolder = dialog.Text.ToUpper();
				else
					return;

				string folderToCreate = Path.Combine(Filesystem.ProjectDirName, newProjectFolder);

				if (Directory.Exists(folderToCreate))
				{
					MainWindow.Warning($"Project \"{newProjectFolder}\" already exists. Please enter another name.");
					continue;
				}

				ok = true;
				ProjectFolder = folderToCreate;
				Directory.CreateDirectory(ProjectFolder);
				File.Create(Path.Combine(ProjectFolder, Filesystem.DefaultMainProgramFileName)).Close();
				CopyFiles(ProjectFolder, Filesystem.UserRootDirName);
				DialogResult = DialogResult.OK;
			}
		}

		private static void CopyFiles(string sourceDir, string destDir)
		{
			if (Directory.Exists(destDir))
				DeleteAllFiles(destDir);
			else
				Directory.CreateDirectory(destDir);

			foreach (string file in Directory.GetFiles(sourceDir))
			{
				string destFile = Path.Combine(destDir, Path.GetFileName(file));
				File.Copy(file, destFile, true);
			}
		}

		private static void DeleteAllFiles(string folderPath)
		{
			foreach (string file in Directory.GetFiles(folderPath))
				File.Delete(file);
		}

		private void BtnItchio_Click(object sender, System.EventArgs e)
		{
			Process.Start("https://fernandoairescastello.itch.io/ptm");
		}

		private void BtnGitHub_Click(object sender, System.EventArgs e)
		{
			Process.Start("https://github.com/FernandoAiresCastello/PTM");
		}
	}
}
