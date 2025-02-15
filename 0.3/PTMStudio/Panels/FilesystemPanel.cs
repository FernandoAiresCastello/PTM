using PTMStudio.Core;
using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio
{
	public partial class FilesystemPanel : UserControl
    {
        private readonly MainWindow MainWindow;

        public TreeView FileTreeComponent => FileTree;

        public FilesystemPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;
            FileTree.DoubleClick += FileTree_DoubleClick;
            UpdateFileList();

            if (mainWnd == null)
                ToolStrip.Visible = false;
        }

        private void FileTree_DoubleClick(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode != null)
                OnDoubleClickEntry(FileTree.SelectedNode.Tag as FilesystemEntry);
		}

		public void ClearFileList()
        {
			FileTree.Nodes.Clear();
		}

		public void UpdateFileList()
        {
			FileTree.Nodes.Clear();
			ListDirectory(FileTree, Filesystem.UserRoot);
			ListDirectory(FileTree, Filesystem.SysRoot);
			FileTree.Nodes[0].Expand();
        }

        private void ListDirectory(TreeView treeView, string path)
        {
            var rootDirectoryInfo = new DirectoryInfo(path);
            treeView.Nodes.Add(CreateDirectoryNode(rootDirectoryInfo));
        }

        private static TreeNode CreateDirectoryNode(DirectoryInfo directoryInfo)
        {
            var directoryNode = new TreeNode(directoryInfo.Name, 0, 0) { Name = directoryInfo.Name };

            FilesystemEntry directoryEntry = new FilesystemEntry
            {
                IsDirectory = true,
                AbsolutePath = Filesystem.NormalizePath(directoryInfo.FullName)
            };
            directoryEntry.RelativePath = Filesystem.RemoveFilesPrefix(Filesystem.RemoveAbsoluteRoot(directoryEntry.AbsolutePath));
            directoryNode.Tag = directoryEntry;

            foreach (var directory in directoryInfo.GetDirectories())
            {
                directoryNode.Nodes.Add(CreateDirectoryNode(directory));
            }
            foreach (var file in directoryInfo.GetFiles())
            {
				int imageIndex = 8;

                if (file.Name == "AUTORUN.PTM" || file.Name == "AUTOSAVE.PTM" || file.Name == "TEMP.PTM")
                {
                    imageIndex = 3;
                }
                else switch (file.Extension.ToUpper())
				{
					case KnownFileExtensions.Program: imageIndex = 2; break;
					case KnownFileExtensions.Charset: imageIndex = 4; break;
					case KnownFileExtensions.Palette: imageIndex = 5; break;
					case KnownFileExtensions.TileBuffer: imageIndex = 6; break;
					case KnownFileExtensions.Project: imageIndex = 7; break;
                    case KnownFileExtensions.Data: imageIndex = 9; break;
                    case KnownFileExtensions.PublishProfile: imageIndex = 10; break;
				}

				var fileNode = new TreeNode(file.Name, imageIndex, imageIndex) { Name = file.Name };

				FilesystemEntry fileEntry = new FilesystemEntry
                {
                    IsDirectory = false,
                    AbsolutePath = Filesystem.NormalizePath(file.FullName)
                };
                fileEntry.RelativePath = Filesystem.RemoveFilesPrefix(Filesystem.RemoveAbsoluteRoot(fileEntry.AbsolutePath));
                fileNode.Tag = fileEntry;
                directoryNode.Nodes.Add(fileNode);
            }

            return directoryNode;
        }

        private void OnDoubleClickEntry(FilesystemEntry entry)
        {
            if (MainWindow == null)
                return;

            if (!entry.IsDirectory)
                MainWindow.LoadFile(entry.AbsolutePath);
        }

        private void BtnExplorer_Click(object sender, EventArgs e)
        {
            Process.Start(Filesystem.CurrentDir);
        }

        private void BtnRefresh_Click(object sender, EventArgs e)
        {
            UpdateFileList();
        }

        private void BtnDelete_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
                return;
			if (FileTree.SelectedNode.Parent == null)
				return;
			if (!(FileTree.SelectedNode.Tag is FilesystemEntry file))
				return;

            if (FileTree.SelectedNode.Parent.Text == Filesystem.SysRootDirName)
            {
                MainWindow.Warning("Cannot delete system files");
                return;
            }

			bool ok = MainWindow.Confirm("Delete this file?\n\n" + file.RelativePath);

            if (ok)
            {
                string path = file.AbsolutePath;
                File.Delete(path);
                UpdateFileList();
            }
        }
	}

	public class FilesystemEntry
    {
        public string AbsolutePath { get; set; }
        public string RelativePath { get; set; }
        public string DisplayPath { get; set; }
        public bool IsDirectory { get; set; }

		public override string ToString() => DisplayPath;
	}
}
