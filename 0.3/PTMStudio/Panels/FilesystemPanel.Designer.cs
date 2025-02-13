namespace PTMStudio
{
    partial class FilesystemPanel
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FilesystemPanel));
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.BtnExplorer = new System.Windows.Forms.ToolStripButton();
			this.BtnRefresh = new System.Windows.Forms.ToolStripButton();
			this.BtnDelete = new System.Windows.Forms.ToolStripButton();
			this.FileTree = new System.Windows.Forms.TreeView();
			this.FileTreeIcons = new System.Windows.Forms.ImageList(this.components);
			this.tableLayoutPanel1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
			this.tableLayoutPanel1.Controls.Add(this.FileTree, 0, 1);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 2;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(201, 272);
			this.tableLayoutPanel1.TabIndex = 1;
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnExplorer,
            this.BtnRefresh,
            this.BtnDelete});
			this.toolStrip1.Location = new System.Drawing.Point(1, 1);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(199, 25);
			this.toolStrip1.TabIndex = 0;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// BtnExplorer
			// 
			this.BtnExplorer.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnExplorer.Image = global::PTMStudio.Properties.Resources.folder;
			this.BtnExplorer.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnExplorer.Name = "BtnExplorer";
			this.BtnExplorer.Size = new System.Drawing.Size(23, 22);
			this.BtnExplorer.Text = "Explore PTM folder";
			this.BtnExplorer.Click += new System.EventHandler(this.BtnExplorer_Click);
			// 
			// BtnRefresh
			// 
			this.BtnRefresh.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnRefresh.Image = global::PTMStudio.Properties.Resources.update;
			this.BtnRefresh.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnRefresh.Name = "BtnRefresh";
			this.BtnRefresh.Size = new System.Drawing.Size(23, 22);
			this.BtnRefresh.Text = "Refresh file list";
			this.BtnRefresh.Click += new System.EventHandler(this.BtnRefresh_Click);
			// 
			// BtnDelete
			// 
			this.BtnDelete.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnDelete.Image = global::PTMStudio.Properties.Resources.delete;
			this.BtnDelete.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnDelete.Name = "BtnDelete";
			this.BtnDelete.Size = new System.Drawing.Size(23, 22);
			this.BtnDelete.Text = "Delete selected file";
			this.BtnDelete.Click += new System.EventHandler(this.BtnDelete_Click);
			// 
			// FileTree
			// 
			this.FileTree.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.FileTree.Dock = System.Windows.Forms.DockStyle.Fill;
			this.FileTree.ImageIndex = 0;
			this.FileTree.ImageList = this.FileTreeIcons;
			this.FileTree.Location = new System.Drawing.Point(1, 27);
			this.FileTree.Margin = new System.Windows.Forms.Padding(0);
			this.FileTree.Name = "FileTree";
			this.FileTree.SelectedImageIndex = 0;
			this.FileTree.Size = new System.Drawing.Size(199, 244);
			this.FileTree.TabIndex = 1;
			// 
			// FileTreeIcons
			// 
			this.FileTreeIcons.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("FileTreeIcons.ImageStream")));
			this.FileTreeIcons.TransparentColor = System.Drawing.Color.Transparent;
			this.FileTreeIcons.Images.SetKeyName(0, "folder.png");
			this.FileTreeIcons.Images.SetKeyName(1, "page_white.png");
			this.FileTreeIcons.Images.SetKeyName(2, "page.png");
			this.FileTreeIcons.Images.SetKeyName(3, "document_black.png");
			this.FileTreeIcons.Images.SetKeyName(4, "text_smallcaps.png");
			this.FileTreeIcons.Images.SetKeyName(5, "color_wheel.png");
			this.FileTreeIcons.Images.SetKeyName(6, "map.png");
			this.FileTreeIcons.Images.SetKeyName(7, "bookshelf.png");
			this.FileTreeIcons.Images.SetKeyName(8, "emotion_question.png");
			this.FileTreeIcons.Images.SetKeyName(9, "table_layout_grand_totals.png");
			// 
			// FilesystemPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.tableLayoutPanel1);
			this.Name = "FilesystemPanel";
			this.Size = new System.Drawing.Size(201, 272);
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton BtnExplorer;
        private System.Windows.Forms.ToolStripButton BtnRefresh;
        private System.Windows.Forms.ToolStripButton BtnDelete;
        private System.Windows.Forms.TreeView FileTree;
        private System.Windows.Forms.ImageList FileTreeIcons;
	}
}
