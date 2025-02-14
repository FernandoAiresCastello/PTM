using PTMStudio.Core;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio.Windows
{
	public partial class PublishWindow : Form
	{
		private readonly FilesystemPanel FsPanel;
		private readonly TreeView FileTree;

		private readonly FilesystemPanel PublishPanel;
		private readonly TreeView PublishTree;

		public PublishWindow()
		{
			InitializeComponent();

			FsPanel = new FilesystemPanel(null);
			FsPanel.Parent = FilesystemPanelContainer;
			FsPanel.Dock = DockStyle.Fill;
			FsPanel.UpdateFileList();
			FileTree = FsPanel.FileTreeComponent;
			FileTree.DoubleClick += FileTreeComponent_DoubleClick;

			PublishPanel = new FilesystemPanel(null);
			PublishPanel.Parent = PubPanelContainer;
			PublishPanel.Dock = DockStyle.Fill;
			PublishPanel.ClearFileList();
			PublishTree = PublishPanel.FileTreeComponent;
			PublishTree.DoubleClick += PublishedFilesPanel_DoubleClick;
			PublishTree.Nodes.Add(new TreeNode(Filesystem.UserRootDirName, 0, 0));

			CmbMainProgram.Click += CmbMainProgram_Click;
		}

		private void BtnAdd_Click(object sender, EventArgs e) => AddSelectedFile();
		private void BtnRemove_Click(object sender, EventArgs e) => RemoveSelectedFile();
		private void FileTreeComponent_DoubleClick(object sender, EventArgs e) => AddSelectedFile();
		private void PublishedFilesPanel_DoubleClick(object sender, EventArgs e) => RemoveSelectedFile();
		private void CmbMainProgram_Click(object sender, EventArgs e) => PopulateMainProgramList();

		private void AddSelectedFile()
		{
			if (FileTree.SelectedNode == null || FileTree.SelectedNode.Tag == null)
				return;

			TreeNode root = PublishTree.Nodes[0];
			string filename = FileTree.SelectedNode.Name;
			if (root.Nodes.ContainsKey(filename))
				return;

			TreeNode clone = FileTree.SelectedNode.Clone() as TreeNode;
			root.Nodes.Add(clone);
			root.Expand();
		}

		private void RemoveSelectedFile()
		{
			if (PublishTree.SelectedNode == null || PublishTree.SelectedNode.Tag == null)
				return;

			PublishTree.Nodes.Remove(PublishTree.SelectedNode);
		}

		private void BtnFolder_Click(object sender, EventArgs e)
		{
			FolderBrowserDialog dialog = new FolderBrowserDialog();
			if (dialog.ShowDialog(this) != DialogResult.OK)
				return;

			TxtFolder.Text = dialog.SelectedPath;
		}

		private void PopulateMainProgramList()
		{
			CmbMainProgram.Items.Clear();

			foreach (var file in GetFilesToPublish())
			{
				if (file.EndsWith(KnownFileExtensions.Program))
					CmbMainProgram.Items.Add(Path.GetFileName(file));
			}
		}

		private void BtnPublish_Click(object sender, EventArgs e)
		{
			if (string.IsNullOrWhiteSpace(TxtFolder.Text.Trim()))
			{
				MessageBox.Show("Please specify the output directory.",
					"Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}

			if (CmbMainProgram.SelectedItem == null)
			{
				MessageBox.Show("Please specify the entry point.",
					"Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}

			Publish();
		}

		private void Publish()
		{
			TxtFolder.Text = Path.Combine(TxtFolder.Text.Trim(), TxtProductName.Text.Trim());

			var outputFolder = TryCreateFolder(TxtFolder.Text.Trim());
			if (outputFolder == null)
				return;

			if (!PublishSystemFiles(outputFolder))
				return;

			string mainProgram = CmbMainProgram.SelectedItem.ToString();
			if (!PublishUserFiles(outputFolder, mainProgram))
				return;

			if (ChkZip.Checked)
			{
				if (!GenerateZipPackage())
					return;
			}

			MessageBox.Show($"Publish successful!",
				"Success", MessageBoxButtons.OK, MessageBoxIcon.Information);

			Process.Start("explorer.exe", outputFolder);
		}

		private bool GenerateZipPackage()
		{
			return true;
		}

		private bool PublishSystemFiles(string outputFolder)
		{
			try
			{
				string renamedPtmExe = TxtProductName.Text.Trim() + ".exe";

				CopySystemFileAs("PTM_INTP.exe", renamedPtmExe, outputFolder);
				CopySystemFile("SDL2.dll", outputFolder);

				TryCreateFolder(Path.Combine(outputFolder, Filesystem.SysRootDirName));

				CopySystemFile("SYS/DEFAULT.CHR", outputFolder);
				CopySystemFile("SYS/DEFAULT.PAL", outputFolder);
			}
			catch (Exception ex)
			{
				MessageBox.Show($"Publish aborted.\n\n" + ex.Message,
					"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

				return false;
			}

			return true;
		}

		private void CopySystemFile(string filename, string outputFolder)
		{
			string ptmSystemPath = Directory.GetCurrentDirectory();
			File.Copy(Path.Combine(ptmSystemPath, filename), Path.Combine(outputFolder, filename));
		}

		private void CopySystemFileAs(string originalFilename, string newFilename, string outputFolder)
		{
			string ptmSystemPath = Directory.GetCurrentDirectory();
			File.Copy(Path.Combine(ptmSystemPath, originalFilename), Path.Combine(outputFolder, newFilename));
		}

		private bool PublishUserFiles(string outputFolder, string mainProgram)
		{
			outputFolder = Path.Combine(outputFolder, Filesystem.UserRootDirName);

			try
			{
				TryCreateFolder(outputFolder);

				foreach (var file in GetFilesToPublish())
				{
					string filename = new FileInfo(file).Name;
					File.Copy(file, Path.Combine(outputFolder, filename));
				}

				string autoexec = $"RUN \"{mainProgram}\"";
				File.WriteAllText(Path.Combine(outputFolder, "AUTOEXEC.PTM"), autoexec);
			}
			catch (Exception ex)
			{
				MessageBox.Show($"Publish aborted.\n\n" + ex.Message,
					"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

				return false;
			}

			return true;
		}

		private string TryCreateFolder(string folder)
		{
			try
			{
				if (!Directory.Exists(folder))
					Directory.CreateDirectory(folder);
			}
			catch (Exception ex)
			{
				MessageBox.Show("Could not create output folder: " + ex.Message,
					"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

				return null;
			}

			return folder;
		}

		private string[] GetFilesToPublish()
		{
			var files = new List<string>();
			TreeNode rootNode = PublishTree.Nodes[0];

			foreach (TreeNode node in rootNode.Nodes)
			{
				if (node.Tag == null)
					continue;

				FilesystemEntry file = node.Tag as FilesystemEntry;
				files.Add(file.AbsolutePath);
			}

			return files.ToArray();
		}
	}
}
