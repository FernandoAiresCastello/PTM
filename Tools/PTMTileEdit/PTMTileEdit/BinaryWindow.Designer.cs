namespace TGLTilePaint
{
    partial class BinaryWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BinaryWindow));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.BtnMode = new System.Windows.Forms.Button();
            this.BtnPaste = new System.Windows.Forms.Button();
            this.BtnCopy = new System.Windows.Forms.Button();
            this.BtnClear = new System.Windows.Forms.Button();
            this.PnlTileEditContainer = new System.Windows.Forms.Panel();
            this.TxtBinary = new System.Windows.Forms.TextBox();
            this.PnlMosaicContainer = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 230F));
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.PnlTileEditContainer, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.TxtBinary, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.PnlMosaicContainer, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 92.56966F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 7.430341F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 39F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(602, 416);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // panel1
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.panel1, 2);
            this.panel1.Controls.Add(this.tableLayoutPanel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 379);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(596, 34);
            this.panel1.TabIndex = 1;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 4;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25.00015F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25.00016F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25.00016F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 24.99953F));
            this.tableLayoutPanel2.Controls.Add(this.BtnMode, 3, 0);
            this.tableLayoutPanel2.Controls.Add(this.BtnPaste, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.BtnCopy, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.BtnClear, 2, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(596, 34);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // BtnMode
            // 
            this.BtnMode.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BtnMode.Location = new System.Drawing.Point(447, 0);
            this.BtnMode.Margin = new System.Windows.Forms.Padding(0);
            this.BtnMode.Name = "BtnMode";
            this.BtnMode.Size = new System.Drawing.Size(149, 34);
            this.BtnMode.TabIndex = 12;
            this.BtnMode.Text = "Mode (F1)";
            this.BtnMode.UseVisualStyleBackColor = true;
            this.BtnMode.Click += new System.EventHandler(this.BtnMode_Click);
            // 
            // BtnPaste
            // 
            this.BtnPaste.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BtnPaste.Location = new System.Drawing.Point(149, 0);
            this.BtnPaste.Margin = new System.Windows.Forms.Padding(0);
            this.BtnPaste.Name = "BtnPaste";
            this.BtnPaste.Size = new System.Drawing.Size(149, 34);
            this.BtnPaste.TabIndex = 11;
            this.BtnPaste.Text = "Paste (Ctrl+V)";
            this.BtnPaste.UseVisualStyleBackColor = true;
            this.BtnPaste.Click += new System.EventHandler(this.BtnPaste_Click);
            // 
            // BtnCopy
            // 
            this.BtnCopy.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BtnCopy.Location = new System.Drawing.Point(0, 0);
            this.BtnCopy.Margin = new System.Windows.Forms.Padding(0);
            this.BtnCopy.Name = "BtnCopy";
            this.BtnCopy.Size = new System.Drawing.Size(149, 34);
            this.BtnCopy.TabIndex = 5;
            this.BtnCopy.Text = "Copy (Ctrl+C)";
            this.BtnCopy.UseVisualStyleBackColor = true;
            this.BtnCopy.Click += new System.EventHandler(this.BtnCopy_Click);
            // 
            // BtnClear
            // 
            this.BtnClear.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BtnClear.Location = new System.Drawing.Point(298, 0);
            this.BtnClear.Margin = new System.Windows.Forms.Padding(0);
            this.BtnClear.Name = "BtnClear";
            this.BtnClear.Size = new System.Drawing.Size(149, 34);
            this.BtnClear.TabIndex = 0;
            this.BtnClear.Text = "Clear (Delete)";
            this.BtnClear.UseVisualStyleBackColor = true;
            this.BtnClear.Click += new System.EventHandler(this.BtnClear_Click);
            // 
            // PnlTileEditContainer
            // 
            this.PnlTileEditContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.PnlTileEditContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlTileEditContainer.Location = new System.Drawing.Point(3, 3);
            this.PnlTileEditContainer.Name = "PnlTileEditContainer";
            this.PnlTileEditContainer.Size = new System.Drawing.Size(366, 342);
            this.PnlTileEditContainer.TabIndex = 0;
            // 
            // TxtBinary
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.TxtBinary, 2);
            this.TxtBinary.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.TxtBinary.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TxtBinary.Location = new System.Drawing.Point(3, 351);
            this.TxtBinary.Margin = new System.Windows.Forms.Padding(3, 0, 3, 3);
            this.TxtBinary.Name = "TxtBinary";
            this.TxtBinary.ReadOnly = true;
            this.TxtBinary.Size = new System.Drawing.Size(596, 22);
            this.TxtBinary.TabIndex = 2;
            this.TxtBinary.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // PnlMosaicContainer
            // 
            this.PnlMosaicContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PnlMosaicContainer.Location = new System.Drawing.Point(375, 3);
            this.PnlMosaicContainer.Name = "PnlMosaicContainer";
            this.PnlMosaicContainer.Padding = new System.Windows.Forms.Padding(32);
            this.PnlMosaicContainer.Size = new System.Drawing.Size(224, 342);
            this.PnlMosaicContainer.TabIndex = 3;
            // 
            // BinaryWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(602, 416);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "BinaryWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PTM Tile Edit";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.BinaryWindow_KeyDown);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel PnlTileEditContainer;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button BtnClear;
        private System.Windows.Forms.Button BtnCopy;
        private System.Windows.Forms.Button BtnPaste;
        private System.Windows.Forms.TextBox TxtBinary;
        private System.Windows.Forms.Panel PnlMosaicContainer;
        private System.Windows.Forms.Button BtnMode;
    }
}