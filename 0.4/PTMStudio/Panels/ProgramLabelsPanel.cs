using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace PTMStudio
{
	public partial class ProgramLabelsPanel : UserControl
    {
        private readonly MainWindow MainWindow;

        private ProgramLabelsPanel()
        {
            InitializeComponent();
        }

        public ProgramLabelsPanel(MainWindow mainWnd)
        {
            InitializeComponent();
            MainWindow = mainWnd;
            LstLabels.MouseDoubleClick += LstLabels_MouseDoubleClick;
        }

        public void UpdateLabels()
        {
            List<string> program = MainWindow.GetProgramSource();
            LstLabels.Items.Clear();

            foreach (string rawLine in program)
            {
                string line = rawLine.Trim();
                if (string.IsNullOrEmpty(line))
                    continue;

                if (line.EndsWith(":"))
                    LstLabels.Items.Add(line.Substring(0, line.Length - 1));
            }
        }

        private void BtnRefresh_Click(object sender, EventArgs e)
        {
            UpdateLabels();
        }

        private void LstLabels_MouseDoubleClick(object sender, MouseEventArgs e)
        {
			if (LstLabels.SelectedItem is string label)
				MainWindow.GoToLabel(label);
		}

		private void BtnSort_Click(object sender, EventArgs e)
		{
            LstLabels.Sorted = BtnSort.Checked;
            UpdateLabels();
		}
	}
}
