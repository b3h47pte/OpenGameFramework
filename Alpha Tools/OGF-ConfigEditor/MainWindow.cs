using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OGF_ConfigEditor
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
            mConfigSelected = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void directorySelect_Click(object sender, EventArgs e)
        {
            /*
             * Show folder selection dialog and update the directory textbox.
             */
            if (directoryDialog.ShowDialog() == DialogResult.OK)
            {
                directoryText.Text = directoryDialog.SelectedPath;
            }
        }

        private void directoryText_TextChanged(object sender, EventArgs e)
        {
            /*
             * Take the directory and search for all the *.ogfconfig files within it and within its sub-folders as well if the option is checked.
             */
            string[] allFiles  = Directory.GetFiles(directoryText.Text, "*.ogfconfig", 
                subdirCheck.Checked ? SearchOption.AllDirectories : SearchOption.TopDirectoryOnly);

            foreach (string s in allFiles)
            {
                FileInfo fi = new FileInfo(s);
                string[] newrow = new string[] { fi.Name, fi.LastWriteTime.ToString(), fi.CreationTime.ToString(),
                    fi.Length.ToString() + " bytes", s };
                fileGrid.Rows.Add(newrow);
            }
        }

        private void AddNewSectionTab(String s)
        {
            TabPage page = new TabPage(s);
            page.AutoScroll = true;
            sectionTabs.TabPages.Add(page);
        }

        private Dictionary<String, Dictionary<String, String>> ConfigData;
        private bool mConfigSelected;
        private String mSelectedFile;

        private void fileGrid_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;
            ConfigData = new Dictionary<string,Dictionary<string,string>>();
            mConfigSelected = true;
            /*
             * Read in the config data and display it. 
             */
            toolStripStatusLabel1.Text = "Modifying..." + fileGrid.Rows[e.RowIndex].Cells[0].Value.ToString();

            /*
             * Open file and parse each line.
             * Lines that begin with ; are comments
             * Lines that begin with [ denotes a section
             * Other lines are key/value pairs
             */
            String currentSection = "DEFAULT";
            bool bFoundDefault = false;

            int rowCnt = 5;
            mSelectedFile = fileGrid.Rows[e.RowIndex].Cells[4].Value.ToString();
            foreach (string line in File.ReadLines(mSelectedFile))
            {
                string trimLine = line.Trim();

                if (trimLine.Length == 0)
                    continue;

                if (trimLine[0] == ';')
                    continue;
                if (trimLine[0] == '[')
                {
                    currentSection = trimLine.Substring(1, trimLine.Length - 2);
                    AddNewSectionTab(currentSection);
                    if (currentSection == "DEFAULT")
                        bFoundDefault = true;
                    rowCnt = 5;
                }
                else
                {
                    int eq = trimLine.IndexOf('=');
                    if (eq == -1)
                        continue;

                    if (currentSection == "DEFAULT" && !bFoundDefault)
                    {
                        bFoundDefault = true;
                        AddNewSectionTab("DEFAULT");
                    }

                    String key = trimLine.Substring(0, eq);
                    String data = trimLine.Substring(eq + 1);

                    Label lbl = new Label();
                    lbl.Top = rowCnt;
                    lbl.Left = 2;
                    lbl.Text = key;

                    TextBox bx = new TextBox();
                    bx.Top = rowCnt - 3;
                    bx.Left = 2 + lbl.Width;
                    bx.Text = data;
                    bx.Tag = key;
                    bx.TextChanged += bx_TextChanged;

                    if (!ConfigData.ContainsKey(currentSection))
                    {
                        ConfigData.Add(currentSection, new Dictionary<string, string>());
                        ConfigData[currentSection].Add(key, data);
                    }
                    else if (!ConfigData[currentSection].ContainsKey(key))
                    {
                        ConfigData[currentSection].Add(key, data);
                    }
                    else
                    {
                        ConfigData[currentSection][key] = data;
                    } 

                    sectionTabs.TabPages[sectionTabs.TabPages.Count - 1].Controls.Add(lbl);
                    sectionTabs.TabPages[sectionTabs.TabPages.Count - 1].Controls.Add(bx);

                    rowCnt += lbl.Height;
                }
            }
        }

        void bx_TextChanged(object sender, EventArgs e)
        {
            // When the textbox for a config data entry is changed
            // Determine what the current active tab is to get the proper section
            // Then determine the proper key from the box's tag
            TextBox bx = (TextBox)sender;
            ConfigData[sectionTabs.SelectedTab.Text][bx.Tag.ToString()] = bx.Text;
        }

        private void saveBtn_Click(object sender, EventArgs e)
        {
            // Save config data back out to the file using the dictionary
            // TODO: Find some way to preserve comments?
            if (!mConfigSelected)
                return;

            using (StreamWriter sw = File.CreateText(mSelectedFile))
            {
                foreach (var section in ConfigData)
                {
                    sw.WriteLine("[" + section.Key + "]");
                    foreach (var kvp in section.Value)
                    {
                        sw.WriteLine(kvp.Key + "=" + kvp.Value);
                    }
                    sw.WriteLine();
                }
            }
        }


    }
}
