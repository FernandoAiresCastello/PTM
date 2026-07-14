namespace PTMStudio
{
    partial class ColorEditWindow
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
			this.TxtColor = new System.Windows.Forms.TextBox();
			this.TxtOriginal = new System.Windows.Forms.TextBox();
			this.PnlColor = new System.Windows.Forms.Panel();
			this.PnlOriginal = new System.Windows.Forms.Panel();
			this.SuspendLayout();
			// 
			// TxtColor
			// 
			this.TxtColor.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.TxtColor.Font = new System.Drawing.Font("Consolas", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.TxtColor.Location = new System.Drawing.Point(9, 8);
			this.TxtColor.MaxLength = 6;
			this.TxtColor.Name = "TxtColor";
			this.TxtColor.Size = new System.Drawing.Size(100, 25);
			this.TxtColor.TabIndex = 0;
			this.TxtColor.Text = "000000";
			this.TxtColor.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// TxtOriginal
			// 
			this.TxtOriginal.Enabled = false;
			this.TxtOriginal.Font = new System.Drawing.Font("Consolas", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.TxtOriginal.ForeColor = System.Drawing.SystemColors.WindowText;
			this.TxtOriginal.Location = new System.Drawing.Point(9, 32);
			this.TxtOriginal.Name = "TxtOriginal";
			this.TxtOriginal.ReadOnly = true;
			this.TxtOriginal.Size = new System.Drawing.Size(100, 25);
			this.TxtOriginal.TabIndex = 1;
			this.TxtOriginal.Text = "000000";
			this.TxtOriginal.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// PnlColor
			// 
			this.PnlColor.Location = new System.Drawing.Point(116, 8);
			this.PnlColor.Name = "PnlColor";
			this.PnlColor.Size = new System.Drawing.Size(66, 25);
			this.PnlColor.TabIndex = 2;
			// 
			// PnlOriginal
			// 
			this.PnlOriginal.Location = new System.Drawing.Point(116, 32);
			this.PnlOriginal.Name = "PnlOriginal";
			this.PnlOriginal.Size = new System.Drawing.Size(66, 25);
			this.PnlOriginal.TabIndex = 3;
			// 
			// ColorEditWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(190, 65);
			this.Controls.Add(this.PnlOriginal);
			this.Controls.Add(this.PnlColor);
			this.Controls.Add(this.TxtOriginal);
			this.Controls.Add(this.TxtColor);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "ColorEditWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TxtColor;
        private System.Windows.Forms.TextBox TxtOriginal;
        private System.Windows.Forms.Panel PnlColor;
        private System.Windows.Forms.Panel PnlOriginal;
    }
}