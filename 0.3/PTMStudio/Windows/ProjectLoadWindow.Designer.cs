namespace PTMStudio.Windows
{
	partial class ProjectLoadWindow
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ProjectLoadWindow));
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.panel1 = new System.Windows.Forms.Panel();
			this.LstProjectFolders = new System.Windows.Forms.ListBox();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.BtnOpenProjectsFolder = new System.Windows.Forms.ToolStripButton();
			this.tableLayoutPanel1.SuspendLayout();
			this.panel1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 2;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(249, 299);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.LstProjectFolders);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel1.Location = new System.Drawing.Point(0, 25);
			this.panel1.Margin = new System.Windows.Forms.Padding(0);
			this.panel1.Name = "panel1";
			this.panel1.Padding = new System.Windows.Forms.Padding(10, 5, 10, 10);
			this.panel1.Size = new System.Drawing.Size(249, 274);
			this.panel1.TabIndex = 1;
			// 
			// LstProjectFolders
			// 
			this.LstProjectFolders.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LstProjectFolders.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LstProjectFolders.FormattingEnabled = true;
			this.LstProjectFolders.ItemHeight = 21;
			this.LstProjectFolders.Location = new System.Drawing.Point(10, 5);
			this.LstProjectFolders.Margin = new System.Windows.Forms.Padding(0);
			this.LstProjectFolders.Name = "LstProjectFolders";
			this.LstProjectFolders.ScrollAlwaysVisible = true;
			this.LstProjectFolders.Size = new System.Drawing.Size(229, 259);
			this.LstProjectFolders.TabIndex = 0;
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnOpenProjectsFolder});
			this.toolStrip1.Location = new System.Drawing.Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Padding = new System.Windows.Forms.Padding(0);
			this.toolStrip1.Size = new System.Drawing.Size(249, 25);
			this.toolStrip1.TabIndex = 2;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// BtnOpenProjectsFolder
			// 
			this.BtnOpenProjectsFolder.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnOpenProjectsFolder.Image = global::PTMStudio.Properties.Resources.folder;
			this.BtnOpenProjectsFolder.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnOpenProjectsFolder.Name = "BtnOpenProjectsFolder";
			this.BtnOpenProjectsFolder.Size = new System.Drawing.Size(23, 22);
			this.BtnOpenProjectsFolder.Text = "Open projects folder";
			this.BtnOpenProjectsFolder.Click += new System.EventHandler(this.BtnOpenProjectsFolder_Click);
			// 
			// ProjectLoadWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(249, 299);
			this.Controls.Add(this.tableLayoutPanel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ProjectLoadWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Load Project";
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.ListBox LstProjectFolders;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton BtnOpenProjectsFolder;
	}
}