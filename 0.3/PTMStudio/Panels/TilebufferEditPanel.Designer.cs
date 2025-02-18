using PTMStudio.Core;

namespace PTMStudio
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
			this.BtnText = new System.Windows.Forms.ToolStripButton();
			this.BtnFill = new System.Windows.Forms.ToolStripButton();
			this.BtnSetRandomly = new System.Windows.Forms.ToolStripButton();
			this.BtnClear = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.BtnSelect = new System.Windows.Forms.ToolStripButton();
			this.BtnDeselect = new System.Windows.Forms.ToolStripButton();
			this.BtnCopy = new System.Windows.Forms.ToolStripButton();
			this.BtnCut = new System.Windows.Forms.ToolStripButton();
			this.BtnPaste = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.BtnZoomIn = new System.Windows.Forms.ToolStripButton();
			this.BtnZoomOut = new System.Windows.Forms.ToolStripButton();
			this.BtnToggleGrid = new System.Windows.Forms.ToolStripButton();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.LbSize = new System.Windows.Forms.ToolStripStatusLabel();
			this.LbPos = new System.Windows.Forms.ToolStripStatusLabel();
			this.LbObject = new System.Windows.Forms.ToolStripStatusLabel();
			this.LayoutPanel = new System.Windows.Forms.TableLayoutPanel();
			this.DisplayPanel = new System.Windows.Forms.Panel();
			this.LbSelection = new System.Windows.Forms.ToolStripStatusLabel();
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
			this.TxtFilename.Text = GlobalConstants.Unsaved;
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnNew,
            this.BtnSave,
            this.separator,
            this.BtnSetBgColor,
            this.BtnText,
            this.BtnFill,
            this.BtnSetRandomly,
            this.BtnClear,
            this.toolStripSeparator2,
            this.BtnSelect,
            this.BtnDeselect,
            this.BtnCopy,
            this.BtnCut,
            this.BtnPaste,
            this.toolStripSeparator1,
            this.BtnZoomIn,
            this.BtnZoomOut,
            this.BtnToggleGrid});
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
			this.BtnNew.Text = "New tile buffer";
			this.BtnNew.Click += new System.EventHandler(this.BtnNew_Click);
			// 
			// BtnSave
			// 
			this.BtnSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSave.Image = global::PTMStudio.Properties.Resources.diskette;
			this.BtnSave.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSave.Name = "BtnSave";
			this.BtnSave.Size = new System.Drawing.Size(23, 22);
			this.BtnSave.Text = "Save tile buffer";
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
			this.BtnSetBgColor.Text = "Set background color";
			this.BtnSetBgColor.Click += new System.EventHandler(this.BtnSetBgColor_Click);
			// 
			// BtnText
			// 
			this.BtnText.CheckOnClick = true;
			this.BtnText.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnText.Image = global::PTMStudio.Properties.Resources.insert_text;
			this.BtnText.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnText.Name = "BtnText";
			this.BtnText.Size = new System.Drawing.Size(23, 22);
			this.BtnText.Text = "Add text";
			this.BtnText.Click += new System.EventHandler(this.BtnText_Click);
			// 
			// BtnFill
			// 
			this.BtnFill.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnFill.Image = global::PTMStudio.Properties.Resources.fill_color;
			this.BtnFill.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnFill.Name = "BtnFill";
			this.BtnFill.Size = new System.Drawing.Size(23, 22);
			this.BtnFill.Text = "Fill buffer";
			this.BtnFill.Click += new System.EventHandler(this.BtnFill_Click);
			// 
			// BtnSetRandomly
			// 
			this.BtnSetRandomly.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSetRandomly.Image = global::PTMStudio.Properties.Resources.dice;
			this.BtnSetRandomly.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSetRandomly.Name = "BtnSetRandomly";
			this.BtnSetRandomly.Size = new System.Drawing.Size(23, 22);
			this.BtnSetRandomly.Text = "Set objects randomly";
			this.BtnSetRandomly.Click += new System.EventHandler(this.BtnSetRandomly_Click);
			// 
			// BtnClear
			// 
			this.BtnClear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnClear.Image = global::PTMStudio.Properties.Resources.broom;
			this.BtnClear.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnClear.Name = "BtnClear";
			this.BtnClear.Size = new System.Drawing.Size(23, 22);
			this.BtnClear.Text = "Clear buffer";
			this.BtnClear.Click += new System.EventHandler(this.BtnClear_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
			// 
			// BtnSelect
			// 
			this.BtnSelect.CheckOnClick = true;
			this.BtnSelect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnSelect.Image = global::PTMStudio.Properties.Resources.select;
			this.BtnSelect.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnSelect.Name = "BtnSelect";
			this.BtnSelect.Size = new System.Drawing.Size(23, 22);
			this.BtnSelect.Text = "Toggle selection mode";
			this.BtnSelect.Click += new System.EventHandler(this.BtnSelect_Click);
			// 
			// BtnDeselect
			// 
			this.BtnDeselect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnDeselect.Image = global::PTMStudio.Properties.Resources.layer_remove;
			this.BtnDeselect.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnDeselect.Name = "BtnDeselect";
			this.BtnDeselect.Size = new System.Drawing.Size(23, 22);
			this.BtnDeselect.Text = "Deselect all tiles";
			this.BtnDeselect.Click += new System.EventHandler(this.BtnDeselect_Click);
			// 
			// BtnCopy
			// 
			this.BtnCopy.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnCopy.Image = global::PTMStudio.Properties.Resources.page_white_copy;
			this.BtnCopy.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnCopy.Name = "BtnCopy";
			this.BtnCopy.Size = new System.Drawing.Size(23, 22);
			this.BtnCopy.Text = "Copy selected tiles";
			this.BtnCopy.Click += new System.EventHandler(this.BtnCopy_Click);
			// 
			// BtnCut
			// 
			this.BtnCut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnCut.Image = global::PTMStudio.Properties.Resources.cut;
			this.BtnCut.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnCut.Name = "BtnCut";
			this.BtnCut.Size = new System.Drawing.Size(23, 22);
			this.BtnCut.Text = "Cut selected tiles";
			this.BtnCut.Click += new System.EventHandler(this.BtnCut_Click);
			// 
			// BtnPaste
			// 
			this.BtnPaste.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnPaste.Image = global::PTMStudio.Properties.Resources.page_white_paste;
			this.BtnPaste.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnPaste.Name = "BtnPaste";
			this.BtnPaste.Size = new System.Drawing.Size(23, 22);
			this.BtnPaste.Text = "Paste copied tiles";
			this.BtnPaste.Click += new System.EventHandler(this.BtnPaste_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
			// 
			// BtnZoomIn
			// 
			this.BtnZoomIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnZoomIn.Image = global::PTMStudio.Properties.Resources.magnifier_zoom_in;
			this.BtnZoomIn.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnZoomIn.Name = "BtnZoomIn";
			this.BtnZoomIn.Size = new System.Drawing.Size(23, 22);
			this.BtnZoomIn.Text = "Zoom in";
			this.BtnZoomIn.Click += new System.EventHandler(this.BtnZoomIn_Click);
			// 
			// BtnZoomOut
			// 
			this.BtnZoomOut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnZoomOut.Image = global::PTMStudio.Properties.Resources.magnifier_zoom_out;
			this.BtnZoomOut.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnZoomOut.Name = "BtnZoomOut";
			this.BtnZoomOut.Size = new System.Drawing.Size(23, 22);
			this.BtnZoomOut.Text = "Zoom out";
			this.BtnZoomOut.Click += new System.EventHandler(this.BtnZoomOut_Click);
			// 
			// BtnToggleGrid
			// 
			this.BtnToggleGrid.Checked = true;
			this.BtnToggleGrid.CheckOnClick = true;
			this.BtnToggleGrid.CheckState = System.Windows.Forms.CheckState.Checked;
			this.BtnToggleGrid.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.BtnToggleGrid.Image = global::PTMStudio.Properties.Resources.layouts_four_grid;
			this.BtnToggleGrid.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.BtnToggleGrid.Name = "BtnToggleGrid";
			this.BtnToggleGrid.Size = new System.Drawing.Size(23, 22);
			this.BtnToggleGrid.Text = "Toggle grid";
			this.BtnToggleGrid.Click += new System.EventHandler(this.BtnToggleGrid_Click);
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.LbSize,
            this.LbPos,
            this.LbObject,
            this.LbSelection});
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
			// LbObject
			// 
			this.LbObject.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
			this.LbObject.Name = "LbObject";
			this.LbObject.Size = new System.Drawing.Size(46, 19);
			this.LbObject.Text = "Object";
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
			// LbSelection
			// 
			this.LbSelection.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
			this.LbSelection.Name = "LbSelection";
			this.LbSelection.Size = new System.Drawing.Size(59, 19);
			this.LbSelection.Text = "Selection";
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
		private System.Windows.Forms.ToolStripButton BtnText;
		private System.Windows.Forms.ToolStripButton BtnToggleGrid;
		private System.Windows.Forms.ToolStripStatusLabel LbObject;
		private System.Windows.Forms.ToolStripButton BtnSelect;
		private System.Windows.Forms.ToolStripButton BtnDeselect;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripButton BtnSetRandomly;
		private System.Windows.Forms.ToolStripButton BtnCopy;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripButton BtnPaste;
		private System.Windows.Forms.ToolStripButton BtnCut;
		private System.Windows.Forms.ToolStripStatusLabel LbSelection;
	}
}
