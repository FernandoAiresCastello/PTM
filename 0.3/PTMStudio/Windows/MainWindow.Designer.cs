namespace PTMStudio
{
    partial class MainWindow
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.runToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.LbChanges = new System.Windows.Forms.ToolStripStatusLabel();
			this.RootPanel = new System.Windows.Forms.TableLayoutPanel();
			this.CenterPanel = new System.Windows.Forms.TableLayoutPanel();
			this.CenterBottomPanel = new System.Windows.Forms.Panel();
			this.LeftPanel = new System.Windows.Forms.TableLayoutPanel();
			this.TopRightPanel = new System.Windows.Forms.Panel();
			this.BtmRightPanel = new System.Windows.Forms.Panel();
			this.RightPanel = new System.Windows.Forms.TableLayoutPanel();
			this.BtmLeftPanel = new System.Windows.Forms.Panel();
			this.TopLeftPanel = new System.Windows.Forms.Panel();
			this.BtnSaveProgram = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnSaveEverything = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnSaveProject = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnPublish = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnRelaunchIde = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnQuit = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnRun = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnRunEmpty = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnViewPrgEdit = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnViewTilebufEdit = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnAlternateEditor = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnHelp = new System.Windows.Forms.ToolStripMenuItem();
			this.BtnAbout = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.RootPanel.SuspendLayout();
			this.CenterPanel.SuspendLayout();
			this.LeftPanel.SuspendLayout();
			this.RightPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.runToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(884, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnSaveProgram,
            this.BtnSaveEverything,
            this.BtnSaveProject,
            this.BtnPublish,
            this.toolStripSeparator1,
            this.BtnRelaunchIde,
            this.BtnQuit});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(219, 6);
			// 
			// runToolStripMenuItem
			// 
			this.runToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnRun,
            this.BtnRunEmpty});
			this.runToolStripMenuItem.Name = "runToolStripMenuItem";
			this.runToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
			this.runToolStripMenuItem.Text = "Run";
			// 
			// viewToolStripMenuItem
			// 
			this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnViewPrgEdit,
            this.BtnViewTilebufEdit,
            this.toolStripSeparator2,
            this.BtnAlternateEditor});
			this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
			this.viewToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
			this.viewToolStripMenuItem.Text = "View";
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(212, 6);
			// 
			// helpToolStripMenuItem
			// 
			this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnHelp,
            this.BtnAbout});
			this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
			this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
			this.helpToolStripMenuItem.Text = "Help";
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.LbChanges});
			this.statusStrip1.Location = new System.Drawing.Point(0, 489);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(884, 22);
			this.statusStrip1.TabIndex = 1;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// LbChanges
			// 
			this.LbChanges.Name = "LbChanges";
			this.LbChanges.Size = new System.Drawing.Size(99, 17);
			this.LbChanges.Text = "Unsaved changes";
			// 
			// RootPanel
			// 
			this.RootPanel.BackColor = System.Drawing.SystemColors.Control;
			this.RootPanel.ColumnCount = 3;
			this.RootPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 26.31579F));
			this.RootPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 73.68421F));
			this.RootPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 272F));
			this.RootPanel.Controls.Add(this.CenterPanel, 1, 0);
			this.RootPanel.Controls.Add(this.LeftPanel, 0, 0);
			this.RootPanel.Controls.Add(this.RightPanel, 2, 0);
			this.RootPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.RootPanel.Location = new System.Drawing.Point(0, 24);
			this.RootPanel.Margin = new System.Windows.Forms.Padding(0);
			this.RootPanel.Name = "RootPanel";
			this.RootPanel.Padding = new System.Windows.Forms.Padding(10, 10, 10, 15);
			this.RootPanel.RowCount = 1;
			this.RootPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.RootPanel.Size = new System.Drawing.Size(884, 465);
			this.RootPanel.TabIndex = 2;
			// 
			// CenterPanel
			// 
			this.CenterPanel.ColumnCount = 1;
			this.CenterPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.CenterPanel.Controls.Add(this.CenterBottomPanel, 0, 1);
			this.CenterPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.CenterPanel.Location = new System.Drawing.Point(168, 10);
			this.CenterPanel.Margin = new System.Windows.Forms.Padding(3, 0, 3, 0);
			this.CenterPanel.Name = "CenterPanel";
			this.CenterPanel.RowCount = 2;
			this.CenterPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.CenterPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.CenterPanel.Size = new System.Drawing.Size(430, 440);
			this.CenterPanel.TabIndex = 3;
			// 
			// CenterBottomPanel
			// 
			this.CenterBottomPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.CenterBottomPanel.Location = new System.Drawing.Point(0, 3);
			this.CenterBottomPanel.Margin = new System.Windows.Forms.Padding(0, 3, 0, 0);
			this.CenterBottomPanel.Name = "CenterBottomPanel";
			this.CenterBottomPanel.Size = new System.Drawing.Size(430, 440);
			this.CenterBottomPanel.TabIndex = 0;
			// 
			// LeftPanel
			// 
			this.LeftPanel.ColumnCount = 1;
			this.LeftPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.LeftPanel.Controls.Add(this.TopRightPanel, 0, 0);
			this.LeftPanel.Controls.Add(this.BtmRightPanel, 0, 1);
			this.LeftPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LeftPanel.Location = new System.Drawing.Point(10, 10);
			this.LeftPanel.Margin = new System.Windows.Forms.Padding(0);
			this.LeftPanel.Name = "LeftPanel";
			this.LeftPanel.RowCount = 2;
			this.LeftPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.LeftPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.LeftPanel.Size = new System.Drawing.Size(155, 440);
			this.LeftPanel.TabIndex = 1;
			// 
			// TopRightPanel
			// 
			this.TopRightPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.TopRightPanel.Location = new System.Drawing.Point(3, 3);
			this.TopRightPanel.Name = "TopRightPanel";
			this.TopRightPanel.Size = new System.Drawing.Size(149, 214);
			this.TopRightPanel.TabIndex = 1;
			// 
			// BtmRightPanel
			// 
			this.BtmRightPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtmRightPanel.Location = new System.Drawing.Point(3, 226);
			this.BtmRightPanel.Margin = new System.Windows.Forms.Padding(3, 6, 3, 3);
			this.BtmRightPanel.Name = "BtmRightPanel";
			this.BtmRightPanel.Size = new System.Drawing.Size(149, 211);
			this.BtmRightPanel.TabIndex = 2;
			// 
			// RightPanel
			// 
			this.RightPanel.ColumnCount = 1;
			this.RightPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.RightPanel.Controls.Add(this.BtmLeftPanel, 0, 1);
			this.RightPanel.Controls.Add(this.TopLeftPanel, 0, 0);
			this.RightPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.RightPanel.Location = new System.Drawing.Point(601, 10);
			this.RightPanel.Margin = new System.Windows.Forms.Padding(0);
			this.RightPanel.Name = "RightPanel";
			this.RightPanel.RowCount = 2;
			this.RightPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.RightPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.RightPanel.Size = new System.Drawing.Size(273, 440);
			this.RightPanel.TabIndex = 2;
			// 
			// BtmLeftPanel
			// 
			this.BtmLeftPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtmLeftPanel.Location = new System.Drawing.Point(3, 226);
			this.BtmLeftPanel.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
			this.BtmLeftPanel.Name = "BtmLeftPanel";
			this.BtmLeftPanel.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.BtmLeftPanel.Size = new System.Drawing.Size(267, 214);
			this.BtmLeftPanel.TabIndex = 4;
			// 
			// TopLeftPanel
			// 
			this.TopLeftPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.TopLeftPanel.Location = new System.Drawing.Point(3, 3);
			this.TopLeftPanel.Name = "TopLeftPanel";
			this.TopLeftPanel.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.TopLeftPanel.Size = new System.Drawing.Size(267, 214);
			this.TopLeftPanel.TabIndex = 3;
			// 
			// BtnSaveProgram
			// 
			this.BtnSaveProgram.Image = global::PTMStudio.Properties.Resources.diskette;
			this.BtnSaveProgram.Name = "BtnSaveProgram";
			this.BtnSaveProgram.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
			this.BtnSaveProgram.Size = new System.Drawing.Size(222, 22);
			this.BtnSaveProgram.Text = "Save program";
			this.BtnSaveProgram.Click += new System.EventHandler(this.BtnSaveProgram_Click);
			// 
			// BtnSaveEverything
			// 
			this.BtnSaveEverything.Image = global::PTMStudio.Properties.Resources.disk_multiple;
			this.BtnSaveEverything.Name = "BtnSaveEverything";
			this.BtnSaveEverything.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
			this.BtnSaveEverything.Size = new System.Drawing.Size(222, 22);
			this.BtnSaveEverything.Text = "Save all panels";
			this.BtnSaveEverything.Click += new System.EventHandler(this.BtnSaveEverything_Click);
			// 
			// BtnSaveProject
			// 
			this.BtnSaveProject.Image = global::PTMStudio.Properties.Resources.bookshelf;
			this.BtnSaveProject.Name = "BtnSaveProject";
			this.BtnSaveProject.Size = new System.Drawing.Size(222, 22);
			this.BtnSaveProject.Text = "Save as project";
			this.BtnSaveProject.Click += new System.EventHandler(this.BtnSaveProject_Click);
			// 
			// BtnPublish
			// 
			this.BtnPublish.Image = global::PTMStudio.Properties.Resources.package_go;
			this.BtnPublish.Name = "BtnPublish";
			this.BtnPublish.Size = new System.Drawing.Size(222, 22);
			this.BtnPublish.Text = "Publish";
			this.BtnPublish.Click += new System.EventHandler(this.BtnPublish_Click);
			// 
			// BtnRelaunchIde
			// 
			this.BtnRelaunchIde.Image = global::PTMStudio.Properties.Resources.restart_services;
			this.BtnRelaunchIde.Name = "BtnRelaunchIde";
			this.BtnRelaunchIde.Size = new System.Drawing.Size(222, 22);
			this.BtnRelaunchIde.Text = "Relaunch IDE";
			this.BtnRelaunchIde.Click += new System.EventHandler(this.BtnRelaunchIde_Click);
			// 
			// BtnQuit
			// 
			this.BtnQuit.Image = global::PTMStudio.Properties.Resources.cancel;
			this.BtnQuit.Name = "BtnQuit";
			this.BtnQuit.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.Q)));
			this.BtnQuit.Size = new System.Drawing.Size(222, 22);
			this.BtnQuit.Text = "Quit";
			this.BtnQuit.Click += new System.EventHandler(this.BtnQuit_Click);
			// 
			// BtnRun
			// 
			this.BtnRun.Image = global::PTMStudio.Properties.Resources.control_play_blue;
			this.BtnRun.Name = "BtnRun";
			this.BtnRun.ShortcutKeys = System.Windows.Forms.Keys.F5;
			this.BtnRun.Size = new System.Drawing.Size(233, 22);
			this.BtnRun.Text = "Run current program";
			this.BtnRun.Click += new System.EventHandler(this.BtnRun_Click);
			// 
			// BtnRunEmpty
			// 
			this.BtnRunEmpty.Image = global::PTMStudio.Properties.Resources.control_play;
			this.BtnRunEmpty.Name = "BtnRunEmpty";
			this.BtnRunEmpty.Size = new System.Drawing.Size(233, 22);
			this.BtnRunEmpty.Text = "Launch PTM without program";
			this.BtnRunEmpty.Click += new System.EventHandler(this.BtnRunEmpty_Click);
			// 
			// BtnViewPrgEdit
			// 
			this.BtnViewPrgEdit.Image = global::PTMStudio.Properties.Resources.script_code;
			this.BtnViewPrgEdit.Name = "BtnViewPrgEdit";
			this.BtnViewPrgEdit.Size = new System.Drawing.Size(215, 22);
			this.BtnViewPrgEdit.Text = "Program editor";
			this.BtnViewPrgEdit.Click += new System.EventHandler(this.BtnViewPrgEdit_Click);
			// 
			// BtnViewTilebufEdit
			// 
			this.BtnViewTilebufEdit.Image = global::PTMStudio.Properties.Resources.table_edit;
			this.BtnViewTilebufEdit.Name = "BtnViewTilebufEdit";
			this.BtnViewTilebufEdit.Size = new System.Drawing.Size(215, 22);
			this.BtnViewTilebufEdit.Text = "Tilebuffer editor";
			this.BtnViewTilebufEdit.Click += new System.EventHandler(this.BtnViewTilebufEdit_Click);
			// 
			// BtnAlternateEditor
			// 
			this.BtnAlternateEditor.Image = global::PTMStudio.Properties.Resources.arrow_refresh;
			this.BtnAlternateEditor.Name = "BtnAlternateEditor";
			this.BtnAlternateEditor.ShortcutKeys = System.Windows.Forms.Keys.F2;
			this.BtnAlternateEditor.Size = new System.Drawing.Size(215, 22);
			this.BtnAlternateEditor.Text = "Switch between editors";
			this.BtnAlternateEditor.Click += new System.EventHandler(this.BtnAlternateEditor_Click);
			// 
			// BtnHelp
			// 
			this.BtnHelp.Image = global::PTMStudio.Properties.Resources.help;
			this.BtnHelp.Name = "BtnHelp";
			this.BtnHelp.ShortcutKeys = System.Windows.Forms.Keys.F1;
			this.BtnHelp.Size = new System.Drawing.Size(233, 22);
			this.BtnHelp.Text = "PTML command reference";
			this.BtnHelp.Click += new System.EventHandler(this.BtnHelp_Click);
			// 
			// BtnAbout
			// 
			this.BtnAbout.Image = global::PTMStudio.Properties.Resources.information;
			this.BtnAbout.Name = "BtnAbout";
			this.BtnAbout.Size = new System.Drawing.Size(233, 22);
			this.BtnAbout.Text = "About";
			this.BtnAbout.Click += new System.EventHandler(this.BtnAbout_Click);
			// 
			// MainWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(884, 511);
			this.Controls.Add(this.RootPanel);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.menuStrip1);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "MainWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "PTM";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.RootPanel.ResumeLayout(false);
			this.CenterPanel.ResumeLayout(false);
			this.LeftPanel.ResumeLayout(false);
			this.RightPanel.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BtnRun;
        private System.Windows.Forms.TableLayoutPanel RootPanel;
        private System.Windows.Forms.TableLayoutPanel LeftPanel;
        private System.Windows.Forms.TableLayoutPanel RightPanel;
        private System.Windows.Forms.Panel TopRightPanel;
        private System.Windows.Forms.Panel BtmRightPanel;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BtnViewPrgEdit;
        private System.Windows.Forms.ToolStripMenuItem BtnViewTilebufEdit;
        private System.Windows.Forms.ToolStripMenuItem BtnAlternateEditor;
        private System.Windows.Forms.ToolStripMenuItem BtnQuit;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BtnHelp;
        private System.Windows.Forms.ToolStripMenuItem BtnAbout;
        private System.Windows.Forms.ToolStripMenuItem BtnSaveEverything;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripStatusLabel LbChanges;
        private System.Windows.Forms.ToolStripMenuItem BtnSaveProject;
		private System.Windows.Forms.ToolStripMenuItem BtnRunEmpty;
		private System.Windows.Forms.TableLayoutPanel CenterPanel;
		private System.Windows.Forms.Panel CenterBottomPanel;
		private System.Windows.Forms.Panel BtmLeftPanel;
		private System.Windows.Forms.Panel TopLeftPanel;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem BtnRelaunchIde;
		private System.Windows.Forms.ToolStripMenuItem BtnSaveProgram;
		private System.Windows.Forms.ToolStripMenuItem BtnPublish;
	}
}

