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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BtnLoadProfile = new System.Windows.Forms.ToolStripMenuItem();
            this.BtnSaveProfile = new System.Windows.Forms.ToolStripMenuItem();
            this.ChkOpenPublishFolder = new System.Windows.Forms.CheckBox();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // FilesystemPanelContainer
            // 
            this.FilesystemPanelContainer.Location = new System.Drawing.Point(16, 159);
            this.FilesystemPanelContainer.Margin = new System.Windows.Forms.Padding(4);
            this.FilesystemPanelContainer.Name = "FilesystemPanelContainer";
            this.FilesystemPanelContainer.Size = new System.Drawing.Size(267, 345);
            this.FilesystemPanelContainer.TabIndex = 0;
            // 
            // BtnRemove
            // 
            this.BtnRemove.Image = global::PTMStudio.Properties.Resources.arrow_left1;
            this.BtnRemove.Location = new System.Drawing.Point(297, 324);
            this.BtnRemove.Margin = new System.Windows.Forms.Padding(4);
            this.BtnRemove.Name = "BtnRemove";
            this.BtnRemove.Size = new System.Drawing.Size(61, 39);
            this.BtnRemove.TabIndex = 3;
            this.BtnRemove.UseVisualStyleBackColor = true;
            this.BtnRemove.Click += new System.EventHandler(this.BtnRemove_Click);
            // 
            // BtnAdd
            // 
            this.BtnAdd.Image = global::PTMStudio.Properties.Resources.arrow_right1;
            this.BtnAdd.Location = new System.Drawing.Point(297, 277);
            this.BtnAdd.Margin = new System.Windows.Forms.Padding(4);
            this.BtnAdd.Name = "BtnAdd";
            this.BtnAdd.Size = new System.Drawing.Size(61, 39);
            this.BtnAdd.TabIndex = 2;
            this.BtnAdd.UseVisualStyleBackColor = true;
            this.BtnAdd.Click += new System.EventHandler(this.BtnAdd_Click);
            // 
            // PubPanelContainer
            // 
            this.PubPanelContainer.Location = new System.Drawing.Point(372, 159);
            this.PubPanelContainer.Margin = new System.Windows.Forms.Padding(4);
            this.PubPanelContainer.Name = "PubPanelContainer";
            this.PubPanelContainer.Size = new System.Drawing.Size(267, 345);
            this.PubPanelContainer.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(16, 132);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Source files";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(371, 132);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 20);
            this.label2.TabIndex = 5;
            this.label2.Text = "Published files";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(16, 81);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(129, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "Output directory";
            // 
            // TxtFolder
            // 
            this.TxtFolder.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtFolder.Location = new System.Drawing.Point(168, 79);
            this.TxtFolder.Margin = new System.Windows.Forms.Padding(4);
            this.TxtFolder.Name = "TxtFolder";
            this.TxtFolder.Size = new System.Drawing.Size(395, 26);
            this.TxtFolder.TabIndex = 7;
            // 
            // BtnFolder
            // 
            this.BtnFolder.Image = global::PTMStudio.Properties.Resources.folder;
            this.BtnFolder.Location = new System.Drawing.Point(572, 78);
            this.BtnFolder.Margin = new System.Windows.Forms.Padding(4);
            this.BtnFolder.Name = "BtnFolder";
            this.BtnFolder.Size = new System.Drawing.Size(67, 30);
            this.BtnFolder.TabIndex = 8;
            this.BtnFolder.UseVisualStyleBackColor = true;
            this.BtnFolder.Click += new System.EventHandler(this.BtnFolder_Click);
            // 
            // BtnPublish
            // 
            this.BtnPublish.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnPublish.Location = new System.Drawing.Point(281, 603);
            this.BtnPublish.Margin = new System.Windows.Forms.Padding(4);
            this.BtnPublish.Name = "BtnPublish";
            this.BtnPublish.Size = new System.Drawing.Size(175, 41);
            this.BtnPublish.TabIndex = 9;
            this.BtnPublish.Text = "Publish!";
            this.BtnPublish.UseVisualStyleBackColor = true;
            this.BtnPublish.Click += new System.EventHandler(this.BtnPublish_Click);
            // 
            // BtnCancel
            // 
            this.BtnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.BtnCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnCancel.Location = new System.Drawing.Point(464, 603);
            this.BtnCancel.Margin = new System.Windows.Forms.Padding(4);
            this.BtnCancel.Name = "BtnCancel";
            this.BtnCancel.Size = new System.Drawing.Size(175, 41);
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
            this.ChkZip.Location = new System.Drawing.Point(20, 585);
            this.ChkZip.Margin = new System.Windows.Forms.Padding(4);
            this.ChkZip.Name = "ChkZip";
            this.ChkZip.Size = new System.Drawing.Size(152, 24);
            this.ChkZip.TabIndex = 11;
            this.ChkZip.Text = "Generate ZIP file";
            this.ChkZip.UseVisualStyleBackColor = true;
            // 
            // TxtProductName
            // 
            this.TxtProductName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtProductName.Location = new System.Drawing.Point(168, 45);
            this.TxtProductName.Margin = new System.Windows.Forms.Padding(4);
            this.TxtProductName.Name = "TxtProductName";
            this.TxtProductName.Size = new System.Drawing.Size(395, 26);
            this.TxtProductName.TabIndex = 13;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(16, 47);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(128, 20);
            this.label4.TabIndex = 12;
            this.label4.Text = "Published name";
            // 
            // CmbMainProgram
            // 
            this.CmbMainProgram.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CmbMainProgram.FormattingEnabled = true;
            this.CmbMainProgram.Location = new System.Drawing.Point(372, 552);
            this.CmbMainProgram.Margin = new System.Windows.Forms.Padding(4);
            this.CmbMainProgram.Name = "CmbMainProgram";
            this.CmbMainProgram.Size = new System.Drawing.Size(265, 24);
            this.CmbMainProgram.TabIndex = 14;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(371, 522);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(89, 20);
            this.label5.TabIndex = 15;
            this.label5.Text = "Entry point";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(655, 30);
            this.menuStrip1.TabIndex = 16;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.BtnLoadProfile,
            this.BtnSaveProfile});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 26);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // BtnLoadProfile
            // 
            this.BtnLoadProfile.Image = global::PTMStudio.Properties.Resources.folder;
            this.BtnLoadProfile.Name = "BtnLoadProfile";
            this.BtnLoadProfile.Size = new System.Drawing.Size(225, 26);
            this.BtnLoadProfile.Text = "Load publish profile";
            this.BtnLoadProfile.Click += new System.EventHandler(this.BtnLoadProfile_Click);
            // 
            // BtnSaveProfile
            // 
            this.BtnSaveProfile.Image = global::PTMStudio.Properties.Resources.diskette;
            this.BtnSaveProfile.Name = "BtnSaveProfile";
            this.BtnSaveProfile.Size = new System.Drawing.Size(225, 26);
            this.BtnSaveProfile.Text = "Save publish profile";
            this.BtnSaveProfile.Click += new System.EventHandler(this.BtnSaveProfile_Click);
            // 
            // ChkOpenPublishFolder
            // 
            this.ChkOpenPublishFolder.AutoSize = true;
            this.ChkOpenPublishFolder.Checked = true;
            this.ChkOpenPublishFolder.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ChkOpenPublishFolder.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ChkOpenPublishFolder.Location = new System.Drawing.Point(20, 617);
            this.ChkOpenPublishFolder.Margin = new System.Windows.Forms.Padding(4);
            this.ChkOpenPublishFolder.Name = "ChkOpenPublishFolder";
            this.ChkOpenPublishFolder.Size = new System.Drawing.Size(226, 24);
            this.ChkOpenPublishFolder.TabIndex = 17;
            this.ChkOpenPublishFolder.Text = "Open folder after publishing";
            this.ChkOpenPublishFolder.UseVisualStyleBackColor = true;
            // 
            // PublishWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(655, 661);
            this.Controls.Add(this.ChkOpenPublishFolder);
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
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PublishWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Publish";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
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
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BtnLoadProfile;
        private System.Windows.Forms.ToolStripMenuItem BtnSaveProfile;
        private System.Windows.Forms.CheckBox ChkOpenPublishFolder;
    }
}