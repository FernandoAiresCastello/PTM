namespace PTMEdit
{
    partial class MainWindow
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
		///  Required method for Designer support - do not modify
		///  the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			tableLayoutPanel1 = new TableLayoutPanel();
			BottomPanel = new Panel();
			TopPanel = new Panel();
			CenterPanel = new Panel();
			TxtProgram = new TextBox();
			tableLayoutPanel1.SuspendLayout();
			CenterPanel.SuspendLayout();
			SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			tableLayoutPanel1.ColumnCount = 1;
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
			tableLayoutPanel1.Controls.Add(BottomPanel, 0, 2);
			tableLayoutPanel1.Controls.Add(TopPanel, 0, 0);
			tableLayoutPanel1.Controls.Add(CenterPanel, 0, 1);
			tableLayoutPanel1.Dock = DockStyle.Fill;
			tableLayoutPanel1.Location = new Point(0, 0);
			tableLayoutPanel1.Name = "tableLayoutPanel1";
			tableLayoutPanel1.RowCount = 3;
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 10F));
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 80F));
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 10F));
			tableLayoutPanel1.Size = new Size(413, 308);
			tableLayoutPanel1.TabIndex = 0;
			// 
			// BottomPanel
			// 
			BottomPanel.Dock = DockStyle.Fill;
			BottomPanel.Location = new Point(0, 276);
			BottomPanel.Margin = new Padding(0);
			BottomPanel.Name = "BottomPanel";
			BottomPanel.Size = new Size(413, 32);
			BottomPanel.TabIndex = 1;
			// 
			// TopPanel
			// 
			TopPanel.Dock = DockStyle.Fill;
			TopPanel.Location = new Point(0, 0);
			TopPanel.Margin = new Padding(0);
			TopPanel.Name = "TopPanel";
			TopPanel.Size = new Size(413, 30);
			TopPanel.TabIndex = 0;
			// 
			// CenterPanel
			// 
			CenterPanel.Controls.Add(TxtProgram);
			CenterPanel.Dock = DockStyle.Fill;
			CenterPanel.Location = new Point(20, 50);
			CenterPanel.Margin = new Padding(20);
			CenterPanel.Name = "CenterPanel";
			CenterPanel.Size = new Size(373, 206);
			CenterPanel.TabIndex = 2;
			// 
			// TxtProgram
			// 
			TxtProgram.AcceptsReturn = true;
			TxtProgram.AcceptsTab = true;
			TxtProgram.BorderStyle = BorderStyle.None;
			TxtProgram.Dock = DockStyle.Fill;
			TxtProgram.Font = new Font("Consolas", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 0);
			TxtProgram.Location = new Point(0, 0);
			TxtProgram.Margin = new Padding(0);
			TxtProgram.Multiline = true;
			TxtProgram.Name = "TxtProgram";
			TxtProgram.ScrollBars = ScrollBars.Vertical;
			TxtProgram.Size = new Size(373, 206);
			TxtProgram.TabIndex = 0;
			TxtProgram.WordWrap = false;
			// 
			// MainWindow
			// 
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(413, 308);
			ControlBox = false;
			Controls.Add(tableLayoutPanel1);
			Name = "MainWindow";
			StartPosition = FormStartPosition.CenterScreen;
			Text = "PTM";
			tableLayoutPanel1.ResumeLayout(false);
			CenterPanel.ResumeLayout(false);
			CenterPanel.PerformLayout();
			ResumeLayout(false);
		}

		#endregion

		private TableLayoutPanel tableLayoutPanel1;
		private Panel TopPanel;
		private Panel BottomPanel;
		private Panel CenterPanel;
		private TextBox TxtProgram;
	}
}
