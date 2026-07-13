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
			this.LbAbout = new System.Windows.Forms.Label();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.BtnOk = new System.Windows.Forms.Button();
			this.BtnGitHub = new System.Windows.Forms.Button();
			this.BtnItchIo = new System.Windows.Forms.Button();
			this.tableLayoutPanel1.SuspendLayout();
			this.tableLayoutPanel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
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
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 37.1831F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 47.88733F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 14.89362F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(388, 355);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// LbAbout
			// 
			this.LbAbout.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LbAbout.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.LbAbout.Location = new System.Drawing.Point(3, 132);
			this.LbAbout.Name = "LbAbout";
			this.LbAbout.Size = new System.Drawing.Size(382, 170);
			this.LbAbout.TabIndex = 1;
			this.LbAbout.Text = "Version 0.3\r\n\r\n© 2023-2025 Developed by Fernando Aires Castello\r\n\r\nBuild timestam" +
    "p: {build_timestamp}\r\n\r\nhttps://fernandoairescastello.itch.io/ptm\r\nhttps://githu" +
    "b.com/FernandoAiresCastello/PTM";
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
			this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 302);
			this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(0);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 1;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(388, 53);
			this.tableLayoutPanel2.TabIndex = 2;
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
			this.pictureBox1.Size = new System.Drawing.Size(388, 132);
			this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// BtnOk
			// 
			this.BtnOk.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnOk.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnOk.Image = global::PTMStudio.Properties.Resources.thumb_up;
			this.BtnOk.Location = new System.Drawing.Point(261, 3);
			this.BtnOk.Name = "BtnOk";
			this.BtnOk.Size = new System.Drawing.Size(124, 47);
			this.BtnOk.TabIndex = 0;
			this.BtnOk.Text = "  OK";
			this.BtnOk.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnOk.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnOk.UseVisualStyleBackColor = true;
			this.BtnOk.Click += new System.EventHandler(this.BtnOk_Click);
			// 
			// BtnGitHub
			// 
			this.BtnGitHub.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnGitHub.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnGitHub.Image = global::PTMStudio.Properties.Resources.github_2;
			this.BtnGitHub.Location = new System.Drawing.Point(132, 3);
			this.BtnGitHub.Name = "BtnGitHub";
			this.BtnGitHub.Size = new System.Drawing.Size(123, 47);
			this.BtnGitHub.TabIndex = 2;
			this.BtnGitHub.Text = "  Visit GitHub";
			this.BtnGitHub.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnGitHub.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnGitHub.UseVisualStyleBackColor = true;
			this.BtnGitHub.Click += new System.EventHandler(this.BtnGitHub_Click);
			// 
			// BtnItchIo
			// 
			this.BtnItchIo.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnItchIo.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnItchIo.Image = global::PTMStudio.Properties.Resources.itchio_2;
			this.BtnItchIo.Location = new System.Drawing.Point(3, 3);
			this.BtnItchIo.Name = "BtnItchIo";
			this.BtnItchIo.Size = new System.Drawing.Size(123, 47);
			this.BtnItchIo.TabIndex = 1;
			this.BtnItchIo.Text = "  Visit Itch.io";
			this.BtnItchIo.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnItchIo.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnItchIo.UseVisualStyleBackColor = true;
			this.BtnItchIo.Click += new System.EventHandler(this.BtnItchIo_Click);
			// 
			// AboutWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(388, 355);
			this.Controls.Add(this.tableLayoutPanel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AboutWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "About";
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
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