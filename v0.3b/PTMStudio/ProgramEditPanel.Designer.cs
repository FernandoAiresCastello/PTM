﻿namespace PTMStudio
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
            this.SuspendLayout();
            // 
            // ScintillaPanel
            // 
            this.ScintillaPanel.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ScintillaPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ScintillaPanel.Location = new System.Drawing.Point(0, 25);
            this.ScintillaPanel.Name = "ScintillaPanel";
            this.ScintillaPanel.Size = new System.Drawing.Size(295, 320);
            this.ScintillaPanel.TabIndex = 5;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(295, 25);
            this.toolStrip1.TabIndex = 4;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // ProgramEditPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ScintillaPanel);
            this.Controls.Add(this.toolStrip1);
            this.Name = "ProgramEditPanel";
            this.Size = new System.Drawing.Size(295, 345);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ToolStrip toolStrip1;
        public System.Windows.Forms.Panel ScintillaPanel;
    }
}
