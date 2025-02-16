namespace PTMStudio.Windows
{
	partial class AboutWindow
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AboutWindow));
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.LbAbout = new System.Windows.Forms.Label();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.BtnItchIo = new System.Windows.Forms.Button();
			this.BtnGitHub = new System.Windows.Forms.Button();
			this.BtnOk = new System.Windows.Forms.Button();
			this.tableLayoutPanel1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.tableLayoutPanel2.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.BackColor = System.Drawing.Color.White;
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.Controls.Add(this.pictureBox1, 0, 0);
			this.tableLayoutPanel1.Controls.Add(this.LbAbout, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 3;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 35.16484F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 53.84615F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10.64935F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(383, 364);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// pictureBox1
			// 
			this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pictureBox1.Image = global::PTMStudio.Properties.Resources.logo_fw;
			this.pictureBox1.InitialImage = null;
			this.pictureBox1.Location = new System.Drawing.Point(0, 0);
			this.pictureBox1.Margin = new System.Windows.Forms.Padding(0);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(383, 128);
			this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// LbAbout
			// 
			this.LbAbout.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LbAbout.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LbAbout.Location = new System.Drawing.Point(3, 128);
			this.LbAbout.Name = "LbAbout";
			this.LbAbout.Size = new System.Drawing.Size(377, 196);
			this.LbAbout.TabIndex = 1;
			this.LbAbout.Text = resources.GetString("LbAbout.Text");
			this.LbAbout.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// tableLayoutPanel2
			// 
			this.tableLayoutPanel2.ColumnCount = 3;
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel2.Controls.Add(this.BtnOk, 2, 0);
			this.tableLayoutPanel2.Controls.Add(this.BtnGitHub, 1, 0);
			this.tableLayoutPanel2.Controls.Add(this.BtnItchIo, 0, 0);
			this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 327);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 1;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(377, 34);
			this.tableLayoutPanel2.TabIndex = 2;
			// 
			// BtnItchIo
			// 
			this.BtnItchIo.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnItchIo.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnItchIo.Location = new System.Drawing.Point(3, 3);
			this.BtnItchIo.Name = "BtnItchIo";
			this.BtnItchIo.Size = new System.Drawing.Size(119, 28);
			this.BtnItchIo.TabIndex = 1;
			this.BtnItchIo.Text = "Visit Itch.io page";
			this.BtnItchIo.UseVisualStyleBackColor = true;
			this.BtnItchIo.Click += new System.EventHandler(this.BtnItchIo_Click);
			// 
			// BtnGitHub
			// 
			this.BtnGitHub.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnGitHub.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnGitHub.Location = new System.Drawing.Point(128, 3);
			this.BtnGitHub.Name = "BtnGitHub";
			this.BtnGitHub.Size = new System.Drawing.Size(119, 28);
			this.BtnGitHub.TabIndex = 2;
			this.BtnGitHub.Text = "Visit GitHub page";
			this.BtnGitHub.UseVisualStyleBackColor = true;
			this.BtnGitHub.Click += new System.EventHandler(this.BtnGitHub_Click);
			// 
			// BtnOk
			// 
			this.BtnOk.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnOk.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnOk.Location = new System.Drawing.Point(253, 3);
			this.BtnOk.Name = "BtnOk";
			this.BtnOk.Size = new System.Drawing.Size(121, 28);
			this.BtnOk.TabIndex = 0;
			this.BtnOk.Text = "OK";
			this.BtnOk.UseVisualStyleBackColor = true;
			this.BtnOk.Click += new System.EventHandler(this.BtnOk_Click);
			// 
			// AboutWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(383, 364);
			this.Controls.Add(this.tableLayoutPanel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AboutWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "About";
			this.tableLayoutPanel1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.tableLayoutPanel2.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Label LbAbout;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
		private System.Windows.Forms.Button BtnOk;
		private System.Windows.Forms.Button BtnGitHub;
		private System.Windows.Forms.Button BtnItchIo;
	}
}