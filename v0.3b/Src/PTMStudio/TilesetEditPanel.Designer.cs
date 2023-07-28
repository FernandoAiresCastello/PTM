namespace PTMStudio
{
    partial class TilesetEditPanel
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
            this.PnlTileset = new System.Windows.Forms.Panel();
            this.TxtFilename = new System.Windows.Forms.TextBox();
            this.BtnNext = new System.Windows.Forms.ToolStripButton();
            this.BtnPrev = new System.Windows.Forms.ToolStripButton();
            this.LblIndicator = new System.Windows.Forms.ToolStripLabel();
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
            this.tableLayoutPanel1.Controls.Add(this.PnlTileset, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.TxtFilename, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(200, 253);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnPrev,
            this.BtnNext,
            this.LblIndicator});
            this.toolStrip1.Location = new System.Drawing.Point(1, 1);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(198, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // PnlTileset
            // 
            this.PnlTileset.AutoSize = true;
            this.PnlTileset.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlTileset.Location = new System.Drawing.Point(1, 47);
            this.PnlTileset.Margin = new System.Windows.Forms.Padding(0);
            this.PnlTileset.Name = "PnlTileset";
            this.PnlTileset.Size = new System.Drawing.Size(198, 205);
            this.PnlTileset.TabIndex = 1;
            // 
            // TxtFilename
            // 
            this.TxtFilename.BackColor = System.Drawing.SystemColors.Control;
            this.TxtFilename.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.TxtFilename.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TxtFilename.ForeColor = System.Drawing.Color.Gray;
            this.TxtFilename.Location = new System.Drawing.Point(6, 30);
            this.TxtFilename.Margin = new System.Windows.Forms.Padding(5, 3, 3, 3);
            this.TxtFilename.Name = "TxtFilename";
            this.TxtFilename.ReadOnly = true;
            this.TxtFilename.Size = new System.Drawing.Size(190, 13);
            this.TxtFilename.TabIndex = 2;
            this.TxtFilename.Text = "Default PTM tileset";
            // 
            // BtnNext
            // 
            this.BtnNext.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnNext.Image = global::PTMStudio.Properties.Resources.resultset_next;
            this.BtnNext.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.BtnNext.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnNext.Name = "BtnNext";
            this.BtnNext.Size = new System.Drawing.Size(23, 22);
            this.BtnNext.Text = "Scroll down";
            this.BtnNext.Click += new System.EventHandler(this.BtnNext_Click);
            // 
            // BtnPrev
            // 
            this.BtnPrev.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnPrev.Image = global::PTMStudio.Properties.Resources.resultset_previous;
            this.BtnPrev.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.BtnPrev.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnPrev.Name = "BtnPrev";
            this.BtnPrev.Size = new System.Drawing.Size(23, 22);
            this.BtnPrev.Text = "Scroll up";
            this.BtnPrev.Click += new System.EventHandler(this.BtnPrev_Click);
            // 
            // LblIndicator
            // 
            this.LblIndicator.ForeColor = System.Drawing.Color.Gray;
            this.LblIndicator.Name = "LblIndicator";
            this.LblIndicator.Size = new System.Drawing.Size(86, 22);
            this.LblIndicator.Text = "toolStripLabel1";
            // 
            // TilesetEditPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Margin = new System.Windows.Forms.Padding(0);
            this.Name = "TilesetEditPanel";
            this.Size = new System.Drawing.Size(200, 253);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.Panel PnlTileset;
        private System.Windows.Forms.TextBox TxtFilename;
        private System.Windows.Forms.ToolStripButton BtnNext;
        private System.Windows.Forms.ToolStripButton BtnPrev;
        private System.Windows.Forms.ToolStripLabel LblIndicator;
    }
}
