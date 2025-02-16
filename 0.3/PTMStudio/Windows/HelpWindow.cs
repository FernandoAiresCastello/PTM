using PTMStudio.Core;
using System;
using System.Linq;
using System.Windows.Forms;

namespace PTMStudio
{
	public partial class HelpWindow : Form
    {
        private readonly HelpTopics HelpTopics = new HelpTopics();

        public HelpWindow()
        {
            InitializeComponent();

			Text = $"PTML Reference - {HelpTopics.Commands.Count} commands";
            StartPosition = FormStartPosition.CenterParent;

			LstCommands.Sorted = true;
            LstCommands.SelectedIndexChanged += LstCommands_SelectedIndexChanged;
            LstCommands.DataSource = HelpTopics.Commands;

			KeyPreview = true;
			KeyDown += HelpWindow_KeyDown;
			Shown += HelpWindow_Shown;
			FormClosing += HelpWindow_FormClosing;
			TxtSearch.TextChanged += TxtSearch_TextChanged;
		}

		private void HelpWindow_FormClosing(object sender, FormClosingEventArgs e)
		{
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
                Hide();
            }
		}

		private void TxtSearch_TextChanged(object sender, EventArgs e)
        {
            FilterCommandList();
        }

        private void LstCommands_SelectedIndexChanged(object sender, EventArgs e)
        {
            ShowHelpForSelectedCommand();
        }

        private void HelpWindow_Shown(object sender, EventArgs e)
        {
            TxtSearch.Focus();
        }

        private void HelpWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                Close();
        }

        private void ShowHelpForSelectedCommand()
        {
            if (LstCommands.SelectedItem == null)
                return;

            CommandHelp help = LstCommands.SelectedItem as CommandHelp;
            HelpView.Url = new Uri(help.HtmlFilePath);
		}

        private void FilterCommandList()
        {
            string search = TxtSearch.Text.Trim();
            if (string.IsNullOrWhiteSpace(search))
                return;

			CommandHelp helpTopic = HelpTopics.Commands.FirstOrDefault(
                help => help.Command.StartsWith(search));

            if (helpTopic == null)
                return;

            int index = HelpTopics.Commands.IndexOf(helpTopic);
            if (index >= 0)
                LstCommands.SelectedIndex = index;
		}
    }
}
