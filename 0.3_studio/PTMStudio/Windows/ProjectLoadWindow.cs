using PTMStudio.Core;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio.Windows
{
	public partial class ProjectLoadWindow : Form
	{
		public ProjectFolder SelectedProject { get; private set; }

		public ProjectLoadWindow()
		{
			InitializeComponent();
			FormClosing += ProjectLoadWindow_FormClosing;
			LstProjectFolders.MouseDoubleClick += LstProjectFolders_MouseClick;

			foreach (var path in Directory.EnumerateDirectories(Filesystem.ProjectDirName))
			{
				string name = Path.GetFileName(path);
				if (name != Filesystem.ScratchpadProjectFolder)
					LstProjectFolders.Items.Add(new ProjectFolder(path, name));
			}
		}

		private void ProjectLoadWindow_FormClosing(object sender, FormClosingEventArgs e)
		{
			if (e.CloseReason == CloseReason.UserClosing)
				DialogResult = DialogResult.Cancel;
		}

		private void LstProjectFolders_MouseClick(object sender, MouseEventArgs e)
		{
			if (LstProjectFolders.SelectedItem == null)
				return;

			SelectedProject = LstProjectFolders.SelectedItem as ProjectFolder;
			DialogResult = DialogResult.OK;
		}

		private void BtnOpenProjectsFolder_Click(object sender, System.EventArgs e)
		{
			Process.Start("explorer.exe", Filesystem.ProjectDirName);
		}
	}
}
