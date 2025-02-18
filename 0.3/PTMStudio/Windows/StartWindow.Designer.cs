﻿namespace PTMStudio.Windows
{
	partial class StartWindow
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StartWindow));
			this.RootPanel = new System.Windows.Forms.TableLayoutPanel();
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.BtnExit = new System.Windows.Forms.Button();
			this.BtnScratchpad = new System.Windows.Forms.Button();
			this.BtnLoad = new System.Windows.Forms.Button();
			this.BtnNew = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.RootPanel.SuspendLayout();
			this.tableLayoutPanel1.SuspendLayout();
			this.tableLayoutPanel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.SuspendLayout();
			// 
			// RootPanel
			// 
			this.RootPanel.BackColor = System.Drawing.Color.White;
			this.RootPanel.ColumnCount = 1;
			this.RootPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.RootPanel.Controls.Add(this.pictureBox1, 0, 0);
			this.RootPanel.Controls.Add(this.tableLayoutPanel1, 0, 1);
			this.RootPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.RootPanel.Location = new System.Drawing.Point(0, 0);
			this.RootPanel.Name = "RootPanel";
			this.RootPanel.RowCount = 2;
			this.RootPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 41.05263F));
			this.RootPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 58.94737F));
			this.RootPanel.Size = new System.Drawing.Size(388, 329);
			this.RootPanel.TabIndex = 1;
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 138);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 2;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 47.34043F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 52.65957F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(382, 188);
			this.tableLayoutPanel1.TabIndex = 1;
			// 
			// tableLayoutPanel2
			// 
			this.tableLayoutPanel2.ColumnCount = 2;
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel2.Controls.Add(this.BtnExit, 1, 1);
			this.tableLayoutPanel2.Controls.Add(this.BtnScratchpad, 0, 1);
			this.tableLayoutPanel2.Controls.Add(this.BtnLoad, 1, 0);
			this.tableLayoutPanel2.Controls.Add(this.BtnNew, 0, 0);
			this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 89);
			this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(0);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 2;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(382, 99);
			this.tableLayoutPanel2.TabIndex = 0;
			// 
			// pictureBox1
			// 
			this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pictureBox1.Image = global::PTMStudio.Properties.Resources.logo_fw;
			this.pictureBox1.InitialImage = null;
			this.pictureBox1.Location = new System.Drawing.Point(0, 0);
			this.pictureBox1.Margin = new System.Windows.Forms.Padding(0);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(388, 135);
			this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// BtnExit
			// 
			this.BtnExit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
			this.BtnExit.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnExit.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
			this.BtnExit.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.BtnExit.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnExit.Image = global::PTMStudio.Properties.Resources.door_out;
			this.BtnExit.Location = new System.Drawing.Point(194, 52);
			this.BtnExit.Name = "BtnExit";
			this.BtnExit.Size = new System.Drawing.Size(185, 44);
			this.BtnExit.TabIndex = 3;
			this.BtnExit.Text = "  Exit";
			this.BtnExit.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnExit.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnExit.UseVisualStyleBackColor = false;
			this.BtnExit.Click += new System.EventHandler(this.BtnExit_Click);
			// 
			// BtnScratchpad
			// 
			this.BtnScratchpad.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
			this.BtnScratchpad.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnScratchpad.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
			this.BtnScratchpad.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.BtnScratchpad.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnScratchpad.Image = global::PTMStudio.Properties.Resources.lightbulb;
			this.BtnScratchpad.Location = new System.Drawing.Point(3, 52);
			this.BtnScratchpad.Name = "BtnScratchpad";
			this.BtnScratchpad.Size = new System.Drawing.Size(185, 44);
			this.BtnScratchpad.TabIndex = 2;
			this.BtnScratchpad.Text = "  Scratchpad";
			this.BtnScratchpad.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnScratchpad.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnScratchpad.UseVisualStyleBackColor = false;
			this.BtnScratchpad.Click += new System.EventHandler(this.BtnScratchpad_Click);
			// 
			// BtnLoad
			// 
			this.BtnLoad.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
			this.BtnLoad.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnLoad.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
			this.BtnLoad.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.BtnLoad.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnLoad.Image = global::PTMStudio.Properties.Resources.folder_vertical_open;
			this.BtnLoad.Location = new System.Drawing.Point(194, 3);
			this.BtnLoad.Name = "BtnLoad";
			this.BtnLoad.Size = new System.Drawing.Size(185, 43);
			this.BtnLoad.TabIndex = 1;
			this.BtnLoad.Text = "  Load Project";
			this.BtnLoad.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnLoad.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnLoad.UseVisualStyleBackColor = false;
			this.BtnLoad.Click += new System.EventHandler(this.BtnLoad_Click);
			// 
			// BtnNew
			// 
			this.BtnNew.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
			this.BtnNew.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BtnNew.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
			this.BtnNew.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.BtnNew.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnNew.Image = global::PTMStudio.Properties.Resources.flag_new;
			this.BtnNew.Location = new System.Drawing.Point(3, 3);
			this.BtnNew.Name = "BtnNew";
			this.BtnNew.Size = new System.Drawing.Size(185, 43);
			this.BtnNew.TabIndex = 0;
			this.BtnNew.Text = "  New Project";
			this.BtnNew.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.BtnNew.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.BtnNew.UseVisualStyleBackColor = false;
			this.BtnNew.Click += new System.EventHandler(this.BtnNew_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.label1.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(0, 10);
			this.label1.Margin = new System.Windows.Forms.Padding(0, 10, 0, 10);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(382, 69);
			this.label1.TabIndex = 1;
			this.label1.Text = "Version 0.3\r\n\r\n© 2023-2025 Developed by Fernando Aires Castello";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// StartWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(388, 329);
			this.Controls.Add(this.RootPanel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "StartWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Welcome!";
			this.RootPanel.ResumeLayout(false);
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.tableLayoutPanel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel RootPanel;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
		private System.Windows.Forms.Button BtnNew;
		private System.Windows.Forms.Button BtnLoad;
		private System.Windows.Forms.Button BtnScratchpad;
		private System.Windows.Forms.Button BtnExit;
		private System.Windows.Forms.Label label1;
	}
}