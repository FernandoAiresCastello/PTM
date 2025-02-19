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
			this.BtnNew = new System.Windows.Forms.ToolStripButton();
			this.BtnSwitchColor = new System.Windows.Forms.ToolStripButton();
			this.panel1 = new System.Windows.Forms.Panel();
			this.panel3 = new System.Windows.Forms.Panel();
			this.label2 = new System.Windows.Forms.Label();
			this.LblFrameCount = new System.Windows.Forms.Label();
			this.PropertyGrid = new System.Windows.Forms.DataGridView();
			this.Property = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.Value = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.panel2 = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.LbTileRegFrame = new System.Windows.Forms.Label();
			this.TileFramePanel = new System.Windows.Forms.Panel();
			this.tableLayoutPanel1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.panel1.SuspendLayout();
			this.panel3.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.PropertyGrid)).BeginInit();
			this.panel2.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
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
			this.tableLayoutPanel1.Size = new System.Drawing.Size(185, 268);
			this.tableLayoutPanel1.TabIndex = 2;
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnNew,
            this.BtnSwitchColor});
			this.toolStrip1.Location = new System.Drawing.Point(1, 1);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(183, 25);
			this.toolStrip1.TabIndex = 0;
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
			// BtnSwitchColor
			// 
			this.BtnSwitchColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSwitchColor.Image = global::PTMStudio.Properties.Resources.color_picker_switch;
			this.BtnSwitchColor.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSwitchColor.Name = "BtnSwitchColor";
			this.BtnSwitchColor.Size = new System.Drawing.Size(23, 22);
			this.BtnSwitchColor.Click += new System.EventHandler(this.BtnSwitchColor_Click);
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.panel3);
			this.panel1.Controls.Add(this.PropertyGrid);
			this.panel1.Controls.Add(this.panel2);
			this.panel1.Controls.Add(this.TileFramePanel);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel1.Location = new System.Drawing.Point(1, 27);
			this.panel1.Margin = new System.Windows.Forms.Padding(0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(183, 240);
			this.panel1.TabIndex = 1;
			// 
			// panel3
			// 
			this.panel3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.panel3.Controls.Add(this.label2);
			this.panel3.Controls.Add(this.LblFrameCount);
			this.panel3.Location = new System.Drawing.Point(134, 8);
			this.panel3.Margin = new System.Windows.Forms.Padding(0);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(40, 36);
			this.panel3.TabIndex = 5;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(1, 1);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(41, 13);
			this.label2.TabIndex = 2;
			this.label2.Text = "Frames";
			// 
			// LblFrameCount
			// 
			this.LblFrameCount.AutoSize = true;
			this.LblFrameCount.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LblFrameCount.Location = new System.Drawing.Point(2, 18);
			this.LblFrameCount.Name = "LblFrameCount";
			this.LblFrameCount.Size = new System.Drawing.Size(13, 13);
			this.LblFrameCount.TabIndex = 3;
			this.LblFrameCount.Text = "0";
			// 
			// PropertyGrid
			// 
			this.PropertyGrid.AllowUserToResizeRows = false;
			this.PropertyGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.PropertyGrid.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this.PropertyGrid.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.PropertyGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.PropertyGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Property,
            this.Value});
			this.PropertyGrid.EnableHeadersVisualStyles = false;
			this.PropertyGrid.Location = new System.Drawing.Point(8, 51);
			this.PropertyGrid.MultiSelect = false;
			this.PropertyGrid.Name = "PropertyGrid";
			this.PropertyGrid.RowHeadersVisible = false;
			this.PropertyGrid.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders;
			this.PropertyGrid.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
			this.PropertyGrid.ShowCellErrors = false;
			this.PropertyGrid.ShowCellToolTips = false;
			this.PropertyGrid.ShowEditingIcon = false;
			this.PropertyGrid.ShowRowErrors = false;
			this.PropertyGrid.Size = new System.Drawing.Size(167, 181);
			this.PropertyGrid.TabIndex = 5;
			this.PropertyGrid.TabStop = false;
			// 
			// Property
			// 
			this.Property.HeaderText = "Property";
			this.Property.Name = "Property";
			// 
			// Value
			// 
			this.Value.HeaderText = "Value";
			this.Value.Name = "Value";
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.label1);
			this.panel2.Controls.Add(this.LbTileRegFrame);
			this.panel2.Location = new System.Drawing.Point(48, 8);
			this.panel2.Margin = new System.Windows.Forms.Padding(0);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(84, 36);
			this.panel2.TabIndex = 4;
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
			this.LbTileRegFrame.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LbTileRegFrame.Location = new System.Drawing.Point(0, 18);
			this.LbTileRegFrame.Name = "LbTileRegFrame";
			this.LbTileRegFrame.Size = new System.Drawing.Size(49, 13);
			this.LbTileRegFrame.TabIndex = 3;
			this.LbTileRegFrame.Text = "0, 0, 0";
			// 
			// TileFramePanel
			// 
			this.TileFramePanel.Location = new System.Drawing.Point(8, 8);
			this.TileFramePanel.Margin = new System.Windows.Forms.Padding(0);
			this.TileFramePanel.Name = "TileFramePanel";
			this.TileFramePanel.Size = new System.Drawing.Size(38, 36);
			this.TileFramePanel.TabIndex = 1;
			// 
			// TileRegisterPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.tableLayoutPanel1);
			this.Name = "TileRegisterPanel";
			this.Size = new System.Drawing.Size(185, 268);
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.panel3.ResumeLayout(false);
			this.panel3.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.PropertyGrid)).EndInit();
			this.panel2.ResumeLayout(false);
			this.panel2.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel TileFramePanel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label LbTileRegFrame;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ToolStripButton BtnSwitchColor;
        private System.Windows.Forms.ToolStripButton BtnNew;
        private System.Windows.Forms.DataGridView PropertyGrid;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label LblFrameCount;
		private System.Windows.Forms.DataGridViewTextBoxColumn Property;
		private System.Windows.Forms.DataGridViewTextBoxColumn Value;
	}
}
