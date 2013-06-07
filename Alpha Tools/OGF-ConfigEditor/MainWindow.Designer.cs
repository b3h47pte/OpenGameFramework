namespace OGF_ConfigEditor
{
    partial class MainWindow
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
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fileGrid = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.directoryText = new System.Windows.Forms.TextBox();
            this.directorySelect = new System.Windows.Forms.Button();
            this.directoryDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.subdirCheck = new System.Windows.Forms.CheckBox();
            this.sectionTabs = new System.Windows.Forms.TabControl();
            this.saveBtn = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.fileName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dateColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dateCreate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.fileSize = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.FULLFILENAME = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.mainMenu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fileGrid)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(901, 24);
            this.mainMenu.TabIndex = 0;
            this.mainMenu.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
            this.exitToolStripMenuItem.Text = "&Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // fileGrid
            // 
            this.fileGrid.AllowUserToAddRows = false;
            this.fileGrid.AllowUserToDeleteRows = false;
            this.fileGrid.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.fileGrid.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.fileGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.fileGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.fileName,
            this.dateColumn,
            this.dateCreate,
            this.fileSize,
            this.FULLFILENAME});
            this.fileGrid.Location = new System.Drawing.Point(0, 74);
            this.fileGrid.Name = "fileGrid";
            this.fileGrid.Size = new System.Drawing.Size(450, 455);
            this.fileGrid.TabIndex = 1;
            this.fileGrid.CellContentDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.fileGrid_CellContentDoubleClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(183, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "Local Configuration Files";
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(357, 42);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Directory:";
            // 
            // directoryText
            // 
            this.directoryText.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.directoryText.Location = new System.Drawing.Point(412, 38);
            this.directoryText.Name = "directoryText";
            this.directoryText.ReadOnly = true;
            this.directoryText.Size = new System.Drawing.Size(438, 20);
            this.directoryText.TabIndex = 5;
            this.directoryText.TextChanged += new System.EventHandler(this.directoryText_TextChanged);
            // 
            // directorySelect
            // 
            this.directorySelect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.directorySelect.Location = new System.Drawing.Point(857, 36);
            this.directorySelect.Name = "directorySelect";
            this.directorySelect.Size = new System.Drawing.Size(32, 23);
            this.directorySelect.TabIndex = 6;
            this.directorySelect.Text = ",,,";
            this.directorySelect.UseVisualStyleBackColor = true;
            this.directorySelect.Click += new System.EventHandler(this.directorySelect_Click);
            // 
            // directoryDialog
            // 
            this.directoryDialog.RootFolder = System.Environment.SpecialFolder.MyDocuments;
            this.directoryDialog.SelectedPath = "C:\\Users\\Michael\\Documents";
            // 
            // subdirCheck
            // 
            this.subdirCheck.AutoSize = true;
            this.subdirCheck.Checked = true;
            this.subdirCheck.CheckState = System.Windows.Forms.CheckState.Checked;
            this.subdirCheck.Location = new System.Drawing.Point(202, 41);
            this.subdirCheck.Name = "subdirCheck";
            this.subdirCheck.Size = new System.Drawing.Size(114, 17);
            this.subdirCheck.TabIndex = 7;
            this.subdirCheck.Text = "Check subfolders?";
            this.subdirCheck.UseVisualStyleBackColor = true;
            // 
            // sectionTabs
            // 
            this.sectionTabs.Location = new System.Drawing.Point(453, 74);
            this.sectionTabs.Multiline = true;
            this.sectionTabs.Name = "sectionTabs";
            this.sectionTabs.SelectedIndex = 0;
            this.sectionTabs.Size = new System.Drawing.Size(450, 455);
            this.sectionTabs.TabIndex = 8;
            // 
            // saveBtn
            // 
            this.saveBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveBtn.Location = new System.Drawing.Point(820, 532);
            this.saveBtn.Name = "saveBtn";
            this.saveBtn.Size = new System.Drawing.Size(75, 23);
            this.saveBtn.TabIndex = 9;
            this.saveBtn.Text = "Save";
            this.saveBtn.UseVisualStyleBackColor = true;
            this.saveBtn.Click += new System.EventHandler(this.saveBtn_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 558);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(901, 22);
            this.statusStrip1.TabIndex = 10;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(26, 17);
            this.toolStripStatusLabel1.Text = "Idle";
            // 
            // fileName
            // 
            this.fileName.HeaderText = "File Name";
            this.fileName.Name = "fileName";
            this.fileName.ReadOnly = true;
            this.fileName.Width = 79;
            // 
            // dateColumn
            // 
            this.dateColumn.HeaderText = "Date Modified";
            this.dateColumn.Name = "dateColumn";
            this.dateColumn.ReadOnly = true;
            this.dateColumn.Width = 98;
            // 
            // dateCreate
            // 
            this.dateCreate.HeaderText = "Date Created";
            this.dateCreate.Name = "dateCreate";
            this.dateCreate.ReadOnly = true;
            this.dateCreate.Width = 95;
            // 
            // fileSize
            // 
            this.fileSize.HeaderText = "File Size";
            this.fileSize.Name = "fileSize";
            this.fileSize.ReadOnly = true;
            this.fileSize.Width = 71;
            // 
            // FULLFILENAME
            // 
            this.FULLFILENAME.HeaderText = "Full File Name";
            this.FULLFILENAME.Name = "FULLFILENAME";
            this.FULLFILENAME.ReadOnly = true;
            this.FULLFILENAME.Visible = false;
            this.FULLFILENAME.Width = 98;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(901, 580);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.saveBtn);
            this.Controls.Add(this.sectionTabs);
            this.Controls.Add(this.subdirCheck);
            this.Controls.Add(this.directorySelect);
            this.Controls.Add(this.directoryText);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.fileGrid);
            this.Controls.Add(this.mainMenu);
            this.MainMenuStrip = this.mainMenu;
            this.Name = "MainWindow";
            this.Text = "Open Game Framework -- Configuration File Editor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fileGrid)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.DataGridView fileGrid;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox directoryText;
        private System.Windows.Forms.Button directorySelect;
        private System.Windows.Forms.FolderBrowserDialog directoryDialog;
        private System.Windows.Forms.CheckBox subdirCheck;
        private System.Windows.Forms.TabControl sectionTabs;
        private System.Windows.Forms.Button saveBtn;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.DataGridViewTextBoxColumn fileName;
        private System.Windows.Forms.DataGridViewTextBoxColumn dateColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn dateCreate;
        private System.Windows.Forms.DataGridViewTextBoxColumn fileSize;
        private System.Windows.Forms.DataGridViewTextBoxColumn FULLFILENAME;
    }
}

