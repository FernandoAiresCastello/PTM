namespace TileGameMaker.Windows
{
    partial class MainWindow2
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.PnlBtmLeft = new System.Windows.Forms.Panel();
            this.PnlTopLeft = new System.Windows.Forms.Panel();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PnlProgram = new System.Windows.Forms.Panel();
            this.runToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BtnRun = new System.Windows.Forms.ToolStripMenuItem();
            this.BtnLoadProgram = new System.Windows.Forms.ToolStripMenuItem();
            this.BtnSaveProgram = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.runToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 428);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(800, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 227F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 227F));
            this.tableLayoutPanel1.Controls.Add(this.PnlBtmLeft, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.PnlTopLeft, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.PnlProgram, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(800, 404);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // PnlBtmLeft
            // 
            this.PnlBtmLeft.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PnlBtmLeft.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlBtmLeft.Location = new System.Drawing.Point(3, 205);
            this.PnlBtmLeft.Name = "PnlBtmLeft";
            this.PnlBtmLeft.Size = new System.Drawing.Size(221, 196);
            this.PnlBtmLeft.TabIndex = 1;
            // 
            // PnlTopLeft
            // 
            this.PnlTopLeft.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PnlTopLeft.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlTopLeft.Location = new System.Drawing.Point(3, 3);
            this.PnlTopLeft.Name = "PnlTopLeft";
            this.PnlTopLeft.Size = new System.Drawing.Size(221, 196);
            this.PnlTopLeft.TabIndex = 0;
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnLoadProgram,
            this.BtnSaveProgram});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // PnlProgram
            // 
            this.PnlProgram.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PnlProgram.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlProgram.Location = new System.Drawing.Point(230, 3);
            this.PnlProgram.Name = "PnlProgram";
            this.tableLayoutPanel1.SetRowSpan(this.PnlProgram, 2);
            this.PnlProgram.Size = new System.Drawing.Size(340, 398);
            this.PnlProgram.TabIndex = 2;
            // 
            // runToolStripMenuItem
            // 
            this.runToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnRun});
            this.runToolStripMenuItem.Name = "runToolStripMenuItem";
            this.runToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.runToolStripMenuItem.Text = "Program";
            // 
            // BtnRun
            // 
            this.BtnRun.Name = "BtnRun";
            this.BtnRun.ShortcutKeys = System.Windows.Forms.Keys.F5;
            this.BtnRun.Size = new System.Drawing.Size(180, 22);
            this.BtnRun.Text = "Run";
            this.BtnRun.Click += new System.EventHandler(this.BtnRun_Click);
            // 
            // BtnLoadProgram
            // 
            this.BtnLoadProgram.Name = "BtnLoadProgram";
            this.BtnLoadProgram.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.BtnLoadProgram.Size = new System.Drawing.Size(180, 22);
            this.BtnLoadProgram.Text = "Open";
            this.BtnLoadProgram.Click += new System.EventHandler(this.BtnLoadProgram_Click);
            // 
            // BtnSaveProgram
            // 
            this.BtnSaveProgram.Name = "BtnSaveProgram";
            this.BtnSaveProgram.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.BtnSaveProgram.Size = new System.Drawing.Size(180, 22);
            this.BtnSaveProgram.Text = "Save";
            this.BtnSaveProgram.Click += new System.EventHandler(this.BtnSaveProgram_Click);
            // 
            // MainWindow2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainWindow2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PTM Studio";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel PnlBtmLeft;
        private System.Windows.Forms.Panel PnlTopLeft;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.Panel PnlProgram;
        private System.Windows.Forms.ToolStripMenuItem runToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BtnRun;
        private System.Windows.Forms.ToolStripMenuItem BtnLoadProgram;
        private System.Windows.Forms.ToolStripMenuItem BtnSaveProgram;
    }
}