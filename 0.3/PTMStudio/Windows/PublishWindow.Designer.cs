namespace PTMStudio.Windows
{
	partial class PublishWindow
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PublishWindow));
			this.FilesystemPanelContainer = new System.Windows.Forms.Panel();
			this.BtnRemove = new System.Windows.Forms.Button();
			this.BtnAdd = new System.Windows.Forms.Button();
			this.PubPanelContainer = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.TxtFolder = new System.Windows.Forms.TextBox();
			this.BtnFolder = new System.Windows.Forms.Button();
			this.BtnPublish = new System.Windows.Forms.Button();
			this.BtnCancel = new System.Windows.Forms.Button();
			this.ChkZip = new System.Windows.Forms.CheckBox();
			this.TxtProductName = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.CmbMainProgram = new System.Windows.Forms.ComboBox();
			this.label5 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// FilesystemPanelContainer
			// 
			this.FilesystemPanelContainer.Location = new System.Drawing.Point(12, 104);
			this.FilesystemPanelContainer.Name = "FilesystemPanelContainer";
			this.FilesystemPanelContainer.Size = new System.Drawing.Size(200, 280);
			this.FilesystemPanelContainer.TabIndex = 0;
			// 
			// BtnRemove
			// 
			this.BtnRemove.Image = global::PTMStudio.Properties.Resources.arrow_left1;
			this.BtnRemove.Location = new System.Drawing.Point(223, 238);
			this.BtnRemove.Name = "BtnRemove";
			this.BtnRemove.Size = new System.Drawing.Size(46, 32);
			this.BtnRemove.TabIndex = 3;
			this.BtnRemove.UseVisualStyleBackColor = true;
			this.BtnRemove.Click += new System.EventHandler(this.BtnRemove_Click);
			// 
			// BtnAdd
			// 
			this.BtnAdd.Image = global::PTMStudio.Properties.Resources.arrow_right1;
			this.BtnAdd.Location = new System.Drawing.Point(223, 200);
			this.BtnAdd.Name = "BtnAdd";
			this.BtnAdd.Size = new System.Drawing.Size(46, 32);
			this.BtnAdd.TabIndex = 2;
			this.BtnAdd.UseVisualStyleBackColor = true;
			this.BtnAdd.Click += new System.EventHandler(this.BtnAdd_Click);
			// 
			// PubPanelContainer
			// 
			this.PubPanelContainer.Location = new System.Drawing.Point(279, 104);
			this.PubPanelContainer.Name = "PubPanelContainer";
			this.PubPanelContainer.Size = new System.Drawing.Size(200, 280);
			this.PubPanelContainer.TabIndex = 1;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(12, 82);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(77, 16);
			this.label1.TabIndex = 4;
			this.label1.Text = "Source files";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(278, 82);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(94, 16);
			this.label2.TabIndex = 5;
			this.label2.Text = "Published files";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label3.Location = new System.Drawing.Point(12, 41);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(100, 16);
			this.label3.TabIndex = 6;
			this.label3.Text = "Output directory";
			// 
			// TxtFolder
			// 
			this.TxtFolder.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.TxtFolder.Location = new System.Drawing.Point(126, 39);
			this.TxtFolder.Name = "TxtFolder";
			this.TxtFolder.Size = new System.Drawing.Size(297, 22);
			this.TxtFolder.TabIndex = 7;
			// 
			// BtnFolder
			// 
			this.BtnFolder.Image = global::PTMStudio.Properties.Resources.folder;
			this.BtnFolder.Location = new System.Drawing.Point(429, 38);
			this.BtnFolder.Name = "BtnFolder";
			this.BtnFolder.Size = new System.Drawing.Size(50, 24);
			this.BtnFolder.TabIndex = 8;
			this.BtnFolder.UseVisualStyleBackColor = true;
			this.BtnFolder.Click += new System.EventHandler(this.BtnFolder_Click);
			// 
			// BtnPublish
			// 
			this.BtnPublish.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnPublish.Location = new System.Drawing.Point(211, 465);
			this.BtnPublish.Name = "BtnPublish";
			this.BtnPublish.Size = new System.Drawing.Size(131, 33);
			this.BtnPublish.TabIndex = 9;
			this.BtnPublish.Text = "Publish!";
			this.BtnPublish.UseVisualStyleBackColor = true;
			this.BtnPublish.Click += new System.EventHandler(this.BtnPublish_Click);
			// 
			// BtnCancel
			// 
			this.BtnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.BtnCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.BtnCancel.Location = new System.Drawing.Point(348, 465);
			this.BtnCancel.Name = "BtnCancel";
			this.BtnCancel.Size = new System.Drawing.Size(131, 33);
			this.BtnCancel.TabIndex = 10;
			this.BtnCancel.Text = "Cancel";
			this.BtnCancel.UseVisualStyleBackColor = true;
			// 
			// ChkZip
			// 
			this.ChkZip.AutoSize = true;
			this.ChkZip.Checked = true;
			this.ChkZip.CheckState = System.Windows.Forms.CheckState.Checked;
			this.ChkZip.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ChkZip.Location = new System.Drawing.Point(15, 472);
			this.ChkZip.Name = "ChkZip";
			this.ChkZip.Size = new System.Drawing.Size(125, 20);
			this.ChkZip.TabIndex = 11;
			this.ChkZip.Text = "Generate ZIP file";
			this.ChkZip.UseVisualStyleBackColor = true;
			// 
			// TxtProductName
			// 
			this.TxtProductName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.TxtProductName.Location = new System.Drawing.Point(126, 11);
			this.TxtProductName.Name = "TxtProductName";
			this.TxtProductName.Size = new System.Drawing.Size(297, 22);
			this.TxtProductName.TabIndex = 13;
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label4.Location = new System.Drawing.Point(12, 13);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(104, 16);
			this.label4.TabIndex = 12;
			this.label4.Text = "Published name";
			// 
			// CmbMainProgram
			// 
			this.CmbMainProgram.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.CmbMainProgram.FormattingEnabled = true;
			this.CmbMainProgram.Location = new System.Drawing.Point(279, 423);
			this.CmbMainProgram.Name = "CmbMainProgram";
			this.CmbMainProgram.Size = new System.Drawing.Size(200, 21);
			this.CmbMainProgram.TabIndex = 14;
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label5.Location = new System.Drawing.Point(278, 399);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(69, 16);
			this.label5.TabIndex = 15;
			this.label5.Text = "Entry point";
			// 
			// PublishWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(491, 510);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.CmbMainProgram);
			this.Controls.Add(this.TxtProductName);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.ChkZip);
			this.Controls.Add(this.BtnCancel);
			this.Controls.Add(this.BtnPublish);
			this.Controls.Add(this.BtnFolder);
			this.Controls.Add(this.TxtFolder);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.PubPanelContainer);
			this.Controls.Add(this.BtnRemove);
			this.Controls.Add(this.BtnAdd);
			this.Controls.Add(this.FilesystemPanelContainer);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "PublishWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Publish";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel FilesystemPanelContainer;
		private System.Windows.Forms.Button BtnAdd;
		private System.Windows.Forms.Button BtnRemove;
		private System.Windows.Forms.Panel PubPanelContainer;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox TxtFolder;
		private System.Windows.Forms.Button BtnFolder;
		private System.Windows.Forms.Button BtnPublish;
		private System.Windows.Forms.Button BtnCancel;
		private System.Windows.Forms.CheckBox ChkZip;
		private System.Windows.Forms.TextBox TxtProductName;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.ComboBox CmbMainProgram;
		private System.Windows.Forms.Label label5;
	}
}