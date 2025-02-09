namespace PTMStudio
{
    partial class HelpWindow
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HelpWindow));
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.TxtHelp = new System.Windows.Forms.TextBox();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.LstCommands = new System.Windows.Forms.ListBox();
			this.TxtSearch = new System.Windows.Forms.TextBox();
			this.tableLayoutPanel1.SuspendLayout();
			this.tableLayoutPanel2.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.ColumnCount = 2;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 400F));
			this.tableLayoutPanel1.Controls.Add(this.TxtHelp, 1, 0);
			this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 0);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 1;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(520, 320);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// TxtHelp
			// 
			this.TxtHelp.BackColor = System.Drawing.SystemColors.Window;
			this.TxtHelp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.TxtHelp.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.TxtHelp.Location = new System.Drawing.Point(123, 3);
			this.TxtHelp.Multiline = true;
			this.TxtHelp.Name = "TxtHelp";
			this.TxtHelp.ReadOnly = true;
			this.TxtHelp.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.TxtHelp.Size = new System.Drawing.Size(394, 314);
			this.TxtHelp.TabIndex = 1;
			this.TxtHelp.TabStop = false;
			// 
			// tableLayoutPanel2
			// 
			this.tableLayoutPanel2.BackColor = System.Drawing.SystemColors.Window;
			this.tableLayoutPanel2.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
			this.tableLayoutPanel2.ColumnCount = 1;
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.Controls.Add(this.LstCommands, 0, 1);
			this.tableLayoutPanel2.Controls.Add(this.TxtSearch, 0, 0);
			this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 3);
			this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(3, 3, 0, 3);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 2;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(117, 314);
			this.tableLayoutPanel2.TabIndex = 2;
			// 
			// LstCommands
			// 
			this.LstCommands.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.LstCommands.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LstCommands.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LstCommands.FormattingEnabled = true;
			this.LstCommands.ItemHeight = 14;
			this.LstCommands.Location = new System.Drawing.Point(1, 27);
			this.LstCommands.Margin = new System.Windows.Forms.Padding(0);
			this.LstCommands.Name = "LstCommands";
			this.LstCommands.Size = new System.Drawing.Size(115, 286);
			this.LstCommands.TabIndex = 2;
			// 
			// TxtSearch
			// 
			this.TxtSearch.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.TxtSearch.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.TxtSearch.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.TxtSearch.Location = new System.Drawing.Point(4, 6);
			this.TxtSearch.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
			this.TxtSearch.Name = "TxtSearch";
			this.TxtSearch.Size = new System.Drawing.Size(109, 15);
			this.TxtSearch.TabIndex = 3;
			// 
			// HelpWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(520, 320);
			this.Controls.Add(this.tableLayoutPanel1);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "HelpWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "PTML Command Reference";
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.tableLayoutPanel2.ResumeLayout(false);
			this.tableLayoutPanel2.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox TxtHelp;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.ListBox LstCommands;
        private System.Windows.Forms.TextBox TxtSearch;
    }
}