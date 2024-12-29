namespace PTMStudio
{
    partial class ProgramEditPanel
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
            this.ScintillaPanel = new System.Windows.Forms.Panel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.BtnRun = new System.Windows.Forms.ToolStripButton();
            this.BtnIncFont = new System.Windows.Forms.ToolStripButton();
            this.BtnDecFont = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ScintillaPanel
            // 
            this.ScintillaPanel.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ScintillaPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ScintillaPanel.Location = new System.Drawing.Point(0, 25);
            this.ScintillaPanel.Name = "ScintillaPanel";
            this.ScintillaPanel.Size = new System.Drawing.Size(406, 320);
            this.ScintillaPanel.TabIndex = 5;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnRun,
            this.toolStripSeparator1,
            this.BtnIncFont,
            this.BtnDecFont});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(406, 25);
            this.toolStrip1.TabIndex = 4;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // BtnRun
            // 
            this.BtnRun.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnRun.Image = global::PTMStudio.Properties.Resources.control_play_blue;
            this.BtnRun.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnRun.Name = "BtnRun";
            this.BtnRun.Size = new System.Drawing.Size(23, 22);
            this.BtnRun.Click += new System.EventHandler(this.BtnRun_Click);
            // 
            // BtnIncFont
            // 
            this.BtnIncFont.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnIncFont.Image = global::PTMStudio.Properties.Resources.font_size_decrease;
            this.BtnIncFont.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnIncFont.Name = "BtnIncFont";
            this.BtnIncFont.Size = new System.Drawing.Size(23, 22);
            this.BtnIncFont.Click += new System.EventHandler(this.BtnIncFont_Click);
            // 
            // BtnDecFont
            // 
            this.BtnDecFont.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BtnDecFont.Image = global::PTMStudio.Properties.Resources.font_size_increase;
            this.BtnDecFont.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnDecFont.Name = "BtnDecFont";
            this.BtnDecFont.Size = new System.Drawing.Size(23, 22);
            this.BtnDecFont.Click += new System.EventHandler(this.BtnDecFont_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // ProgramEditPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ScintillaPanel);
            this.Controls.Add(this.toolStrip1);
            this.Name = "ProgramEditPanel";
            this.Size = new System.Drawing.Size(406, 345);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ToolStrip toolStrip1;
        public System.Windows.Forms.Panel ScintillaPanel;
        private System.Windows.Forms.ToolStripButton BtnRun;
        private System.Windows.Forms.ToolStripButton BtnIncFont;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton BtnDecFont;
    }
}
