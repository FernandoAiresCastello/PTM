namespace PTMStudio
{
    partial class PaletteEditPanel
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
            this.PnlPalette = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.BtnNew = new System.Windows.Forms.ToolStripButton();
            this.BtnSave = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.BtnPrev = new System.Windows.Forms.ToolStripButton();
            this.BtnNext = new System.Windows.Forms.ToolStripButton();
            this.LblIndicator = new System.Windows.Forms.ToolStripLabel();
            this.TxtFilename = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // PnlPalette
            // 
            this.PnlPalette.AutoSize = true;
            this.PnlPalette.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlPalette.Location = new System.Drawing.Point(1, 47);
            this.PnlPalette.Margin = new System.Windows.Forms.Padding(0);
            this.PnlPalette.Name = "PnlPalette";
            this.PnlPalette.Size = new System.Drawing.Size(217, 205);
            this.PnlPalette.TabIndex = 1;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.TxtFilename, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.PnlPalette, 0, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(219, 253);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnNew,
            this.BtnSave,
            this.toolStripSeparator1,
            this.BtnPrev,
            this.BtnNext,
            this.LblIndicator});
            this.toolStrip1.Location = new System.Drawing.Point(1, 1);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(217, 25);
            this.toolStrip1.TabIndex = 4;
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
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // BtnPrev
            // 
            this.BtnPrev.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnPrev.Image = global::PTMStudio.Properties.Resources.resultset_previous;
            this.BtnPrev.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.BtnPrev.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnPrev.Name = "BtnPrev";
            this.BtnPrev.Size = new System.Drawing.Size(23, 22);
            this.BtnPrev.Visible = false;
            this.BtnPrev.Click += new System.EventHandler(this.BtnPrev_Click);
            // 
            // BtnNext
            // 
            this.BtnNext.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnNext.Image = global::PTMStudio.Properties.Resources.resultset_next;
            this.BtnNext.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.BtnNext.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnNext.Name = "BtnNext";
            this.BtnNext.Size = new System.Drawing.Size(23, 22);
            this.BtnNext.Visible = false;
            this.BtnNext.Click += new System.EventHandler(this.BtnNext_Click);
            // 
            // LblIndicator
            // 
            this.LblIndicator.ForeColor = System.Drawing.Color.Gray;
            this.LblIndicator.Name = "LblIndicator";
            this.LblIndicator.Size = new System.Drawing.Size(86, 22);
            this.LblIndicator.Text = "toolStripLabel1";
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
            this.TxtFilename.Size = new System.Drawing.Size(209, 13);
            this.TxtFilename.TabIndex = 3;
            this.TxtFilename.Text = "<Unsaved>";
            // 
            // PaletteEditPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Margin = new System.Windows.Forms.Padding(0);
            this.Name = "PaletteEditPanel";
            this.Size = new System.Drawing.Size(219, 253);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel PnlPalette;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox TxtFilename;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton BtnSave;
        private System.Windows.Forms.ToolStripButton BtnPrev;
        private System.Windows.Forms.ToolStripButton BtnNext;
        private System.Windows.Forms.ToolStripLabel LblIndicator;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton BtnNew;
    }
}
