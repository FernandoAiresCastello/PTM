using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace PTMStudio
{
    public partial class FilesystemPanel : UserControl
    {
        private readonly MainWindow MainWindow;

        private FilesystemPanel()
        {
            InitializeComponent();
        }

        public FilesystemPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;
            FileTree.DoubleClick += FileTree_DoubleClick;
            UpdateFileList();
        }

        private void FileTree_DoubleClick(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode != null)
                OnDoubleClickEntry(FileTree.SelectedNode.Tag as FilesystemEntry);
        }

        public void UpdateFileList()
        {
            ListDirectory(FileTree, Filesystem.Root);
            FileTree.Nodes[0].Expand();
        }

        private void ListDirectory(TreeView treeView, string path)
        {
            treeView.Nodes.Clear();
            var rootDirectoryInfo = new DirectoryInfo(path);
            treeView.Nodes.Add(CreateDirectoryNode(rootDirectoryInfo));
        }

        private static TreeNode CreateDirectoryNode(DirectoryInfo directoryInfo)
        {
            var directoryNode = new TreeNode(directoryInfo.Name, 0, 0);
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
                var fileNode = new TreeNode(file.Name, 1, 1);
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
            if (!entry.IsDirectory)
                MainWindow.LoadFile(entry.AbsolutePath);
        }

        private void BtnExplorer_Click(object sender, EventArgs e)
        {
            Process.Start(Filesystem.Root);
        }

        private void BtnRefresh_Click(object sender, EventArgs e)
        {
            UpdateFileList();
        }

        private void BtnDelete_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
                return;

            FilesystemEntry file = FileTree.SelectedNode.Tag as FilesystemEntry;
            if (file == null)
                return;

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

        public override string ToString()
        {
            return DisplayPath;
        }
    }
}
