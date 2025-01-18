﻿namespace PTMStudio
{
    partial class TilebufferEditPanel
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
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.TxtFilename = new System.Windows.Forms.TextBox();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.BtnNew = new System.Windows.Forms.ToolStripButton();
			this.BtnSave = new System.Windows.Forms.ToolStripButton();
			this.separator = new System.Windows.Forms.ToolStripSeparator();
			this.BtnSetBgColor = new System.Windows.Forms.ToolStripButton();
			this.BtnFill = new System.Windows.Forms.ToolStripButton();
			this.BtnClear = new System.Windows.Forms.ToolStripButton();
			this.BtnZoomIn = new System.Windows.Forms.ToolStripButton();
			this.BtnZoomOut = new System.Windows.Forms.ToolStripButton();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.LbSize = new System.Windows.Forms.ToolStripStatusLabel();
			this.LbPos = new System.Windows.Forms.ToolStripStatusLabel();
			this.LayoutPanel = new System.Windows.Forms.TableLayoutPanel();
			this.DisplayPanel = new System.Windows.Forms.Panel();
			this.tableLayoutPanel1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.LayoutPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Controls.Add(this.TxtFilename, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
			this.tableLayoutPanel1.Controls.Add(this.statusStrip1, 0, 4);
			this.tableLayoutPanel1.Controls.Add(this.LayoutPanel, 0, 2);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 5;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.Size = new System.Drawing.Size(604, 345);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// TxtFilename
			// 
			this.TxtFilename.BackColor = System.Drawing.SystemColors.Control;
			this.TxtFilename.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.TxtFilename.Dock = System.Windows.Forms.DockStyle.Fill;
			this.TxtFilename.Enabled = false;
			this.TxtFilename.ForeColor = System.Drawing.Color.Gray;
			this.TxtFilename.Location = new System.Drawing.Point(6, 30);
			this.TxtFilename.Margin = new System.Windows.Forms.Padding(5, 3, 3, 3);
			this.TxtFilename.Name = "TxtFilename";
			this.TxtFilename.ReadOnly = true;
			this.TxtFilename.Size = new System.Drawing.Size(594, 13);
			this.TxtFilename.TabIndex = 4;
			this.TxtFilename.Text = "<Unsaved>";
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnNew,
            this.BtnSave,
            this.separator,
            this.BtnSetBgColor,
            this.BtnFill,
            this.BtnClear,
            this.BtnZoomIn,
            this.BtnZoomOut});
			this.toolStrip1.Location = new System.Drawing.Point(1, 1);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(602, 25);
			this.toolStrip1.TabIndex = 5;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// BtnNew
			// 
			this.BtnNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnNew.Image = global::PTMStudio.Properties.Resources.page_white;
			this.BtnNew.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnNew.Name = "BtnNew";
			this.BtnNew.Size = new System.Drawing.Size(23, 22);
			this.BtnNew.Click += new System.EventHandler(this.BtnNew_Click);
			// 
			// BtnSave
			// 
			this.BtnSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSave.Image = global::PTMStudio.Properties.Resources.diskette;
			this.BtnSave.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSave.Name = "BtnSave";
			this.BtnSave.Size = new System.Drawing.Size(23, 22);
			this.BtnSave.Click += new System.EventHandler(this.BtnSave_Click);
			// 
			// separator
			// 
			this.separator.Name = "separator";
			this.separator.Size = new System.Drawing.Size(6, 25);
			// 
			// BtnSetBgColor
			// 
			this.BtnSetBgColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSetBgColor.Image = global::PTMStudio.Properties.Resources.color_wheel;
			this.BtnSetBgColor.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSetBgColor.Name = "BtnSetBgColor";
			this.BtnSetBgColor.Size = new System.Drawing.Size(23, 22);
			this.BtnSetBgColor.Click += new System.EventHandler(this.BtnSetBgColor_Click);
			// 
			// BtnFill
			// 
			this.BtnFill.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnFill.Image = global::PTMStudio.Properties.Resources.fill_color;
			this.BtnFill.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnFill.Name = "BtnFill";
			this.BtnFill.Size = new System.Drawing.Size(23, 22);
			this.BtnFill.Click += new System.EventHandler(this.BtnFill_Click);
			// 
			// BtnClear
			// 
			this.BtnClear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnClear.Image = global::PTMStudio.Properties.Resources.broom;
			this.BtnClear.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnClear.Name = "BtnClear";
			this.BtnClear.Size = new System.Drawing.Size(23, 22);
			this.BtnClear.Click += new System.EventHandler(this.BtnClear_Click);
			// 
			// BtnZoomIn
			// 
			this.BtnZoomIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnZoomIn.Image = global::PTMStudio.Properties.Resources.magnifier_zoom_in;
			this.BtnZoomIn.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnZoomIn.Name = "BtnZoomIn";
			this.BtnZoomIn.Size = new System.Drawing.Size(23, 22);
			this.BtnZoomIn.Click += new System.EventHandler(this.BtnZoomIn_Click);
			// 
			// BtnZoomOut
			// 
			this.BtnZoomOut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnZoomOut.Image = global::PTMStudio.Properties.Resources.magnifier_zoom_out;
			this.BtnZoomOut.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnZoomOut.Name = "BtnZoomOut";
			this.BtnZoomOut.Size = new System.Drawing.Size(23, 22);
			this.BtnZoomOut.Click += new System.EventHandler(this.BtnZoomOut_Click);
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.LbSize,
            this.LbPos});
			this.statusStrip1.Location = new System.Drawing.Point(1, 320);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(602, 24);
			this.statusStrip1.SizingGrip = false;
			this.statusStrip1.TabIndex = 6;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// LbSize
			// 
			this.LbSize.Name = "LbSize";
			this.LbSize.Size = new System.Drawing.Size(27, 19);
			this.LbSize.Text = "Size";
			// 
			// LbPos
			// 
			this.LbPos.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
			this.LbPos.Name = "LbPos";
			this.LbPos.Size = new System.Drawing.Size(30, 19);
			this.LbPos.Text = "Pos";
			// 
			// LayoutPanel
			// 
			this.LayoutPanel.ColumnCount = 1;
			this.LayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.LayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.LayoutPanel.Controls.Add(this.DisplayPanel, 0, 0);
			this.LayoutPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LayoutPanel.Location = new System.Drawing.Point(1, 47);
			this.LayoutPanel.Margin = new System.Windows.Forms.Padding(0);
			this.LayoutPanel.Name = "LayoutPanel";
			this.LayoutPanel.RowCount = 1;
			this.LayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.LayoutPanel.Size = new System.Drawing.Size(602, 271);
			this.LayoutPanel.TabIndex = 7;
			// 
			// DisplayPanel
			// 
			this.DisplayPanel.AutoScroll = true;
			this.DisplayPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.DisplayPanel.Location = new System.Drawing.Point(0, 0);
			this.DisplayPanel.Margin = new System.Windows.Forms.Padding(0);
			this.DisplayPanel.Name = "DisplayPanel";
			this.DisplayPanel.Size = new System.Drawing.Size(602, 271);
			this.DisplayPanel.TabIndex = 8;
			// 
			// TilebufferEditPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.tableLayoutPanel1);
			this.Margin = new System.Windows.Forms.Padding(0);
			this.Name = "TilebufferEditPanel";
			this.Size = new System.Drawing.Size(604, 345);
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.LayoutPanel.ResumeLayout(false);
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox TxtFilename;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.TableLayoutPanel LayoutPanel;
        private System.Windows.Forms.Panel DisplayPanel;
        private System.Windows.Forms.ToolStripButton BtnSave;
        private System.Windows.Forms.ToolStripButton BtnSetBgColor;
        private System.Windows.Forms.ToolStripButton BtnFill;
        private System.Windows.Forms.ToolStripButton BtnClear;
        private System.Windows.Forms.ToolStripStatusLabel LbPos;
        private System.Windows.Forms.ToolStripStatusLabel LbSize;
        private System.Windows.Forms.ToolStripSeparator separator;
        private System.Windows.Forms.ToolStripButton BtnZoomIn;
        private System.Windows.Forms.ToolStripButton BtnZoomOut;
        private System.Windows.Forms.ToolStripButton BtnNew;
    }
}
