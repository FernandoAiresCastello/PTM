﻿namespace PTMStudio
{
    partial class ProgramEditPanel
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
			this.ScintillaPanel = new System.Windows.Forms.Panel();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.panel1 = new System.Windows.Forms.Panel();
			this.LbFilename = new System.Windows.Forms.Label();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.BtnNew = new System.Windows.Forms.ToolStripButton();
			this.BtnSave = new System.Windows.Forms.ToolStripButton();
			this.BtnRun = new System.Windows.Forms.ToolStripButton();
			this.BtnIncFont = new System.Windows.Forms.ToolStripButton();
			this.BtnDecFont = new System.Windows.Forms.ToolStripButton();
			this.toolStrip1.SuspendLayout();
			this.tableLayoutPanel1.SuspendLayout();
			this.panel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// ScintillaPanel
			// 
			this.ScintillaPanel.BackColor = System.Drawing.SystemColors.AppWorkspace;
			this.ScintillaPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ScintillaPanel.Location = new System.Drawing.Point(1, 47);
			this.ScintillaPanel.Margin = new System.Windows.Forms.Padding(0);
			this.ScintillaPanel.Name = "ScintillaPanel";
			this.ScintillaPanel.Size = new System.Drawing.Size(404, 297);
			this.ScintillaPanel.TabIndex = 5;
			// 
			// toolStrip1
			// 
			this.toolStrip1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnNew,
            this.BtnSave,
            this.toolStripSeparator2,
            this.BtnRun,
            this.toolStripSeparator1,
            this.BtnIncFont,
            this.BtnDecFont});
			this.toolStrip1.Location = new System.Drawing.Point(1, 1);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(404, 25);
			this.toolStrip1.TabIndex = 4;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
			this.tableLayoutPanel1.Controls.Add(this.ScintillaPanel, 0, 2);
			this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 1);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 3;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(406, 345);
			this.tableLayoutPanel1.TabIndex = 6;
			// 
			// panel1
			// 
			this.panel1.AutoSize = true;
			this.panel1.Controls.Add(this.LbFilename);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel1.Location = new System.Drawing.Point(1, 27);
			this.panel1.Margin = new System.Windows.Forms.Padding(0);
			this.panel1.Name = "panel1";
			this.panel1.Padding = new System.Windows.Forms.Padding(3, 2, 2, 2);
			this.panel1.Size = new System.Drawing.Size(404, 19);
			this.panel1.TabIndex = 6;
			// 
			// LbFilename
			// 
			this.LbFilename.Dock = System.Windows.Forms.DockStyle.Top;
			this.LbFilename.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LbFilename.ForeColor = System.Drawing.Color.DimGray;
			this.LbFilename.Location = new System.Drawing.Point(3, 2);
			this.LbFilename.Margin = new System.Windows.Forms.Padding(0);
			this.LbFilename.Name = "LbFilename";
			this.LbFilename.Size = new System.Drawing.Size(399, 15);
			this.LbFilename.TabIndex = 0;
			this.LbFilename.Text = "FILENAME.ABC";
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
			// 
			// BtnNew
			// 
			this.BtnNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnNew.Image = global::PTMStudio.Properties.Resources.page_white;
			this.BtnNew.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnNew.Name = "BtnNew";
			this.BtnNew.Size = new System.Drawing.Size(23, 22);
			this.BtnNew.Text = "Create new program";
			this.BtnNew.Click += new System.EventHandler(this.BtnNew_Click);
			// 
			// BtnSave
			// 
			this.BtnSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSave.Image = global::PTMStudio.Properties.Resources.diskette;
			this.BtnSave.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSave.Name = "BtnSave";
			this.BtnSave.Size = new System.Drawing.Size(23, 22);
			this.BtnSave.Text = "Save program";
			this.BtnSave.Click += new System.EventHandler(this.BtnSave_Click);
			// 
			// BtnRun
			// 
			this.BtnRun.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnRun.Image = global::PTMStudio.Properties.Resources.control_play_blue;
			this.BtnRun.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnRun.Name = "BtnRun";
			this.BtnRun.Size = new System.Drawing.Size(23, 22);
			this.BtnRun.Text = "Run (F5)";
			this.BtnRun.Click += new System.EventHandler(this.BtnRun_Click);
			// 
			// BtnIncFont
			// 
			this.BtnIncFont.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnIncFont.Image = global::PTMStudio.Properties.Resources.font_size_decrease;
			this.BtnIncFont.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnIncFont.Name = "BtnIncFont";
			this.BtnIncFont.Size = new System.Drawing.Size(23, 22);
			this.BtnIncFont.Text = "Increase font size";
			this.BtnIncFont.Click += new System.EventHandler(this.BtnIncFont_Click);
			// 
			// BtnDecFont
			// 
			this.BtnDecFont.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnDecFont.Image = global::PTMStudio.Properties.Resources.font_size_increase;
			this.BtnDecFont.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnDecFont.Name = "BtnDecFont";
			this.BtnDecFont.Size = new System.Drawing.Size(23, 22);
			this.BtnDecFont.Text = "Decrease font size";
			this.BtnDecFont.Click += new System.EventHandler(this.BtnDecFont_Click);
			// 
			// ProgramEditPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.tableLayoutPanel1);
			this.Name = "ProgramEditPanel";
			this.Size = new System.Drawing.Size(406, 345);
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ToolStrip toolStrip1;
        public System.Windows.Forms.Panel ScintillaPanel;
        private System.Windows.Forms.ToolStripButton BtnRun;
        private System.Windows.Forms.ToolStripButton BtnIncFont;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton BtnDecFont;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Label LbFilename;
		private System.Windows.Forms.ToolStripButton BtnNew;
		private System.Windows.Forms.ToolStripButton BtnSave;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
	}
}
