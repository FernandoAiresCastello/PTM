namespace PTMStudio
{
    partial class TileRegisterPanel
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
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.panel1 = new System.Windows.Forms.Panel();
            this.TileSeqPanel = new System.Windows.Forms.Panel();
            this.TileFramePanel = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.LbTileRegFrame = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.BtnSwitchColor = new System.Windows.Forms.ToolStripButton();
            this.BtnNew = new System.Windows.Forms.ToolStripButton();
            this.PropertyGrid = new System.Windows.Forms.DataGridView();
            this.Property = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Value = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.LblFrameCount = new System.Windows.Forms.Label();
            this.ChkTransparent = new System.Windows.Forms.CheckBox();
            this.tableLayoutPanel1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PropertyGrid)).BeginInit();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(193, 268);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnNew,
            this.BtnSwitchColor});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(193, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Controls.Add(this.ChkTransparent);
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.PropertyGrid);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.TileFramePanel);
            this.panel1.Controls.Add(this.TileSeqPanel);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(193, 243);
            this.panel1.TabIndex = 1;
            // 
            // TileSeqPanel
            // 
            this.TileSeqPanel.Location = new System.Drawing.Point(8, 47);
            this.TileSeqPanel.Margin = new System.Windows.Forms.Padding(0);
            this.TileSeqPanel.Name = "TileSeqPanel";
            this.TileSeqPanel.Size = new System.Drawing.Size(174, 29);
            this.TileSeqPanel.TabIndex = 0;
            // 
            // TileFramePanel
            // 
            this.TileFramePanel.Location = new System.Drawing.Point(8, 8);
            this.TileFramePanel.Margin = new System.Windows.Forms.Padding(0);
            this.TileFramePanel.Name = "TileFramePanel";
            this.TileFramePanel.Size = new System.Drawing.Size(38, 36);
            this.TileFramePanel.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(-1, 1);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Tile Register";
            // 
            // LbTileRegFrame
            // 
            this.LbTileRegFrame.AutoSize = true;
            this.LbTileRegFrame.Location = new System.Drawing.Point(1, 18);
            this.LbTileRegFrame.Name = "LbTileRegFrame";
            this.LbTileRegFrame.Size = new System.Drawing.Size(37, 13);
            this.LbTileRegFrame.TabIndex = 3;
            this.LbTileRegFrame.Text = "?, ?, ?";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.LbTileRegFrame);
            this.panel2.Location = new System.Drawing.Point(48, 8);
            this.panel2.Margin = new System.Windows.Forms.Padding(0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(72, 36);
            this.panel2.TabIndex = 4;
            // 
            // BtnSwitchColor
            // 
            this.BtnSwitchColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnSwitchColor.Image = global::PTMStudio.Properties.Resources.color_picker_switch;
            this.BtnSwitchColor.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnSwitchColor.Name = "BtnSwitchColor";
            this.BtnSwitchColor.Size = new System.Drawing.Size(23, 22);
            this.BtnSwitchColor.Click += new System.EventHandler(this.BtnSwitchColor_Click);
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
            // PropertyGrid
            // 
            this.PropertyGrid.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.PropertyGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.PropertyGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Property,
            this.Value});
            this.PropertyGrid.Location = new System.Drawing.Point(8, 101);
            this.PropertyGrid.Name = "PropertyGrid";
            this.PropertyGrid.RowHeadersVisible = false;
            this.PropertyGrid.Size = new System.Drawing.Size(174, 130);
            this.PropertyGrid.TabIndex = 5;
            // 
            // Property
            // 
            this.Property.HeaderText = "Property";
            this.Property.Name = "Property";
            this.Property.Width = 70;
            // 
            // Value
            // 
            this.Value.HeaderText = "Value";
            this.Value.Name = "Value";
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.label2);
            this.panel3.Controls.Add(this.LblFrameCount);
            this.panel3.Location = new System.Drawing.Point(120, 8);
            this.panel3.Margin = new System.Windows.Forms.Padding(0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(62, 36);
            this.panel3.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 1);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Frames";
            // 
            // LblFrameCount
            // 
            this.LblFrameCount.AutoSize = true;
            this.LblFrameCount.Location = new System.Drawing.Point(47, 18);
            this.LblFrameCount.Name = "LblFrameCount";
            this.LblFrameCount.Size = new System.Drawing.Size(13, 13);
            this.LblFrameCount.TabIndex = 3;
            this.LblFrameCount.Text = "?";
            // 
            // ChkTransparent
            // 
            this.ChkTransparent.AutoSize = true;
            this.ChkTransparent.Location = new System.Drawing.Point(8, 78);
            this.ChkTransparent.Name = "ChkTransparent";
            this.ChkTransparent.Size = new System.Drawing.Size(83, 17);
            this.ChkTransparent.TabIndex = 6;
            this.ChkTransparent.Text = "Transparent";
            this.ChkTransparent.UseVisualStyleBackColor = true;
            // 
            // TileRegisterPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "TileRegisterPanel";
            this.Size = new System.Drawing.Size(193, 268);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PropertyGrid)).EndInit();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel TileSeqPanel;
        private System.Windows.Forms.Panel TileFramePanel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label LbTileRegFrame;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ToolStripButton BtnSwitchColor;
        private System.Windows.Forms.ToolStripButton BtnNew;
        private System.Windows.Forms.DataGridView PropertyGrid;
        private System.Windows.Forms.DataGridViewTextBoxColumn Property;
        private System.Windows.Forms.DataGridViewTextBoxColumn Value;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label LblFrameCount;
        private System.Windows.Forms.CheckBox ChkTransparent;
    }
}
