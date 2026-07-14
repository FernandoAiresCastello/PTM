namespace PTMStudio
{
    partial class ColorSelectWindow
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
            this.PnlPalette = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // PnlPalette
            // 
            this.PnlPalette.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.PnlPalette.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlPalette.Location = new System.Drawing.Point(0, 0);
            this.PnlPalette.Name = "PnlPalette";
            this.PnlPalette.Size = new System.Drawing.Size(227, 233);
            this.PnlPalette.TabIndex = 0;
            // 
            // ColorSelectWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(227, 233);
            this.Controls.Add(this.PnlPalette);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ColorSelectWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel PnlPalette;
    }
}