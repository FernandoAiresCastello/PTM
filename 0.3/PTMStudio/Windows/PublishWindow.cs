using PTMStudio.Core;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Linq;
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

        private void AddFileFromPublishProfile(string path)
        {
            TreeNode root = PublishTree.Nodes[0];
            string filename = Path.GetFileName(path);
            if (root.Nodes.ContainsKey(filename))
                return;

			var nodes = FileTree.Nodes[0].Nodes.Find(filename, false);
			if (nodes == null || nodes.Length == 0)
			{
				Error("File not found: " + filename);
				return;
			}

			var node = nodes[0];
            TreeNode clone = node.Clone() as TreeNode;
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
			if (!ValidatePublishProfile())
				return;

			Publish();
		}

		private void Publish()
		{
			string basePublishFolder = TxtFolder.Text.Trim();
			string productName = TxtProductName.Text.Trim();
			string publishFolder = Path.Combine(basePublishFolder, productName);

			if (!TryCreateFolder(publishFolder))
				return;

			if (!PublishSystemFiles(publishFolder))
				return;

			string mainProgram = CmbMainProgram.SelectedItem.ToString();
			if (!PublishUserFiles(publishFolder, mainProgram))
				return;

			if (ChkZip.Checked)
			{
				if (!GenerateZipPackage(publishFolder, Path.Combine(basePublishFolder, productName + ".zip")))
					return;
			}

			Success("Publish successful!");

			if (ChkOpenPublishFolder.Checked)
				Process.Start("explorer.exe", ChkZip.Checked ? basePublishFolder : publishFolder);
		}

		private bool GenerateZipPackage(string sourceFolderPath, string zipPath)
		{
			try
			{
				ZipFile.CreateFromDirectory(sourceFolderPath, zipPath, CompressionLevel.Optimal, true);
			}
			catch (Exception ex)
			{
				Error("Could not generate ZIP file.", ex);
                return false;
			}

			try
			{
				Directory.Delete(sourceFolderPath, true);
			}
            catch (Exception ex)
            {
				Error("Could not delete publish folder after generating ZIP file.", ex);
                return false;
            }

            return true;
		}

		private bool PublishSystemFiles(string outputFolder)
		{
			try
			{
				string renamedPtmExe = TxtProductName.Text.Trim() + ".exe";

				CopySystemFileAs("ptml.exe", renamedPtmExe, outputFolder);
				CopySystemFile("SDL2.dll", outputFolder);

				TryCreateFolder(Path.Combine(outputFolder, Filesystem.SysRootDirName));

				CopySystemFile("SYS/DEFAULT.CHR", outputFolder);
				CopySystemFile("SYS/DEFAULT.PAL", outputFolder);
			}
			catch (Exception ex)
			{
				Error("Publish aborted.", ex);
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
			string userOutputFolder = Path.Combine(outputFolder, Filesystem.UserRootDirName);

			try
			{
				TryCreateFolder(userOutputFolder);

				foreach (var file in GetFilesToPublish())
				{
					string filename = new FileInfo(file).Name;
					File.Copy(file, Path.Combine(userOutputFolder, filename));
				}

				string autoexec = $"RUN \"{mainProgram}\"";
				File.WriteAllText(Path.Combine(userOutputFolder, "AUTOEXEC.PTM"), autoexec);
			}
			catch (Exception ex)
			{
                Error("Publish aborted.", ex);
                return false;
			}

			return true;
		}

		private bool TryCreateFolder(string folder)
		{
			try
			{
				if (!Directory.Exists(folder))
					Directory.CreateDirectory(folder);
			}
			catch (Exception ex)
			{
                Error("Could not create folder.", ex);
				return false;
			}

			return true;
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

        private void Success(string msg)
		{
            MessageBox.Show(msg, "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void Warning(string msg)
		{
            MessageBox.Show(msg, "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void Error(string msg, Exception ex = null)
        {
            MessageBox.Show(ex != null ? $"{msg}\n\n{ex.Message}" : msg,
                "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void BtnLoadProfile_Click(object sender, EventArgs e)
        {
			var dialog = new OpenFileDialog
			{
				InitialDirectory = Filesystem.UserRoot,
				Filter = "PTM Publish Profile (*.PUB)|*.PUB"
			};

			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			LoadProfile(dialog.FileName);
		}

		public void LoadProfile(string path)
		{
			var lines = File.ReadAllLines(path);

			TxtProductName.Text = lines[0];
			TxtFolder.Text = lines[1];
			CmbMainProgram.Items.Add(lines[2]);
			CmbMainProgram.SelectedIndex = 0;
			ChkZip.Checked = bool.Parse(lines[3]);
			ChkOpenPublishFolder.Checked = bool.Parse(lines[4]);

			foreach (TreeNode node in PublishTree.Nodes)
			{
				if (node.Text != Filesystem.UserRootDirName)
					PublishTree.Nodes.Remove(node);
			}

			for (int i = 5; i < lines.Length; i++)
				AddFileFromPublishProfile(lines[i]);
		}

        private void BtnSaveProfile_Click(object sender, EventArgs e)
        {
			if (!ValidatePublishProfile())
				return;

			var dialog = new SaveFileDialog
			{
				InitialDirectory = Filesystem.UserRoot,
				DefaultExt = KnownFileExtensions.PublishProfile,
				Filter = "PTM Publish Profile (*.PUB)|*.PUB"
			};

			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			var lines = new List<string>
            {
                TxtProductName.Text.Trim(),
                TxtFolder.Text.Trim(),
                CmbMainProgram.Text.Trim(),
                ChkZip.Checked.ToString(),
				ChkOpenPublishFolder.Checked.ToString()
            };

            lines.AddRange(GetFilesToPublish());

            File.WriteAllLines(dialog.FileName, lines);
        }

		private bool ValidatePublishProfile()
		{
            if (!GetFilesToPublish().Any(file => file.EndsWith(KnownFileExtensions.Program)))
            {
                Warning("Please include at least one program file (.PTM).");
                return false;
            }

            if (string.IsNullOrWhiteSpace(TxtProductName.Text.Trim()))
            {
                Warning("Please specify the product name.");
                return false;
            }

            if (string.IsNullOrWhiteSpace(TxtFolder.Text.Trim()))
            {
                Warning("Please specify the output directory.");
                return false;
            }

            if (CmbMainProgram.SelectedItem == null)
            {
                Warning("Please specify the entry point.");
                return false;
            }

            return true;
        }
    }
}
