using PTMStudio.Core;
using System;
using System.Windows.Forms;

namespace PTMStudio
{
	public partial class HelpWindow : Form
    {
        private readonly HelpTopics HelpTopics = new HelpTopics();
        private readonly BindingSource BindingSrc;

        public HelpWindow()
        {
            InitializeComponent();

			Text = $"PTML Reference - {HelpTopics.Commands.Count} commands";
			KeyPreview = true;
            KeyDown += HelpWindow_KeyDown;
            Shown += HelpWindow_Shown;
            LstCommands.Sorted = true;
            LstCommands.SelectedIndexChanged += LstCommands_SelectedIndexChanged;
            TxtSearch.TextChanged += TxtSearch_TextChanged;

            BindingSrc = new BindingSource
            {
                DataSource = HelpTopics.Commands
            };
            LstCommands.DataSource = BindingSrc;
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
            BindingSrc.Filter = $"Command LIKE {TxtSearch.Text.Trim().ToUpper()}%";
            
		}
    }
}
