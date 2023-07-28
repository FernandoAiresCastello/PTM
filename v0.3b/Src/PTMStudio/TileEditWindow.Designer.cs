namespace PTMStudio
{
    partial class TileEditWindow
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.BtnClear = new System.Windows.Forms.ToolStripButton();
            this.BtnUndo = new System.Windows.Forms.ToolStripButton();
            this.BtnFlipH = new System.Windows.Forms.ToolStripButton();
            this.BtnFlipV = new System.Windows.Forms.ToolStripButton();
            this.BtnInvert = new System.Windows.Forms.ToolStripButton();
            this.TilePanel = new System.Windows.Forms.Panel();
            this.BtnRotateR = new System.Windows.Forms.ToolStripButton();
            this.BtnRotateD = new System.Windows.Forms.ToolStripButton();
            this.BtnRotateL = new System.Windows.Forms.ToolStripButton();
            this.BtnRotateU = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.MosaicPanel = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 217F));
            this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.TilePanel, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.MosaicPanel, 1, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(449, 248);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // toolStrip1
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.toolStrip1, 2);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnClear,
            this.BtnFlipH,
            this.BtnFlipV,
            this.BtnRotateR,
            this.BtnRotateD,
            this.BtnRotateL,
            this.BtnRotateU,
            this.BtnInvert,
            this.toolStripSeparator1,
            this.BtnUndo});
            this.toolStrip1.Location = new System.Drawing.Point(2, 2);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(445, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // BtnClear
            // 
            this.BtnClear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnClear.Image = global::PTMStudio.Properties.Resources.page_white;
            this.BtnClear.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnClear.Name = "BtnClear";
            this.BtnClear.Size = new System.Drawing.Size(23, 22);
            this.BtnClear.Click += new System.EventHandler(this.BtnClear_Click);
            // 
            // BtnUndo
            // 
            this.BtnUndo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnUndo.Image = global::PTMStudio.Properties.Resources.arrow_undo;
            this.BtnUndo.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnUndo.Name = "BtnUndo";
            this.BtnUndo.Size = new System.Drawing.Size(23, 22);
            this.BtnUndo.Click += new System.EventHandler(this.BtnUndo_Click);
            // 
            // BtnFlipH
            // 
            this.BtnFlipH.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnFlipH.Image = global::PTMStudio.Properties.Resources.shape_flip_horizontal;
            this.BtnFlipH.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnFlipH.Name = "BtnFlipH";
            this.BtnFlipH.Size = new System.Drawing.Size(23, 22);
            this.BtnFlipH.Click += new System.EventHandler(this.BtnFlipH_Click);
            // 
            // BtnFlipV
            // 
            this.BtnFlipV.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnFlipV.Image = global::PTMStudio.Properties.Resources.shape_flip_vertical;
            this.BtnFlipV.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnFlipV.Name = "BtnFlipV";
            this.BtnFlipV.Size = new System.Drawing.Size(23, 22);
            this.BtnFlipV.Click += new System.EventHandler(this.BtnFlipV_Click);
            // 
            // BtnInvert
            // 
            this.BtnInvert.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnInvert.Image = global::PTMStudio.Properties.Resources.color_picker_switch;
            this.BtnInvert.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnInvert.Name = "BtnInvert";
            this.BtnInvert.Size = new System.Drawing.Size(23, 22);
            this.BtnInvert.Click += new System.EventHandler(this.BtnInvert_Click);
            // 
            // TilePanel
            // 
            this.TilePanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.TilePanel.Location = new System.Drawing.Point(18, 39);
            this.TilePanel.Margin = new System.Windows.Forms.Padding(16, 10, 5, 0);
            this.TilePanel.Name = "TilePanel";
            this.TilePanel.Size = new System.Drawing.Size(196, 196);
            this.TilePanel.TabIndex = 1;
            // 
            // BtnRotateR
            // 
            this.BtnRotateR.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnRotateR.Image = global::PTMStudio.Properties.Resources.arrow_right;
            this.BtnRotateR.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnRotateR.Name = "BtnRotateR";
            this.BtnRotateR.Size = new System.Drawing.Size(23, 22);
            this.BtnRotateR.Click += new System.EventHandler(this.BtnRotateR_Click);
            // 
            // BtnRotateD
            // 
            this.BtnRotateD.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnRotateD.Image = global::PTMStudio.Properties.Resources.arrow_down;
            this.BtnRotateD.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnRotateD.Name = "BtnRotateD";
            this.BtnRotateD.Size = new System.Drawing.Size(23, 22);
            this.BtnRotateD.Click += new System.EventHandler(this.BtnRotateD_Click);
            // 
            // BtnRotateL
            // 
            this.BtnRotateL.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnRotateL.Image = global::PTMStudio.Properties.Resources.arrow_left;
            this.BtnRotateL.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnRotateL.Name = "BtnRotateL";
            this.BtnRotateL.Size = new System.Drawing.Size(23, 22);
            this.BtnRotateL.Click += new System.EventHandler(this.BtnRotateL_Click);
            // 
            // BtnRotateU
            // 
            this.BtnRotateU.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnRotateU.Image = global::PTMStudio.Properties.Resources.arrow_up;
            this.BtnRotateU.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnRotateU.Name = "BtnRotateU";
            this.BtnRotateU.Size = new System.Drawing.Size(23, 22);
            this.BtnRotateU.Click += new System.EventHandler(this.BtnRotateU_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // MosaicPanel
            // 
            this.MosaicPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MosaicPanel.Location = new System.Drawing.Point(230, 29);
            this.MosaicPanel.Margin = new System.Windows.Forms.Padding(0);
            this.MosaicPanel.Name = "MosaicPanel";
            this.MosaicPanel.Size = new System.Drawing.Size(217, 217);
            this.MosaicPanel.TabIndex = 2;
            // 
            // TileEditWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(449, 248);
            this.Controls.Add(this.tableLayoutPanel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TileEditWindow";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton BtnUndo;
        private System.Windows.Forms.Panel TilePanel;
        private System.Windows.Forms.ToolStripButton BtnClear;
        private System.Windows.Forms.ToolStripButton BtnFlipH;
        private System.Windows.Forms.ToolStripButton BtnFlipV;
        private System.Windows.Forms.ToolStripButton BtnInvert;
        private System.Windows.Forms.ToolStripButton BtnRotateR;
        private System.Windows.Forms.ToolStripButton BtnRotateD;
        private System.Windows.Forms.ToolStripButton BtnRotateL;
        private System.Windows.Forms.ToolStripButton BtnRotateU;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.Panel MosaicPanel;
    }
}