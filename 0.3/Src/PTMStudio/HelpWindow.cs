using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTMStudio
{
    public partial class HelpWindow : Form
    {
        private readonly List<CommandHelp> Commands;
        private readonly List<CommandHelp> AllCommands;
        private BindingSource BindingSrc;

        public HelpWindow()
        {
            InitializeComponent();
            
            KeyPreview = true;
            KeyDown += HelpWindow_KeyDown;
            Shown += HelpWindow_Shown;
            LstCommands.Sorted = true;
            LstCommands.SelectedIndexChanged += LstCommands_SelectedIndexChanged;
            TxtSearch.TextChanged += TxtSearch_TextChanged;

            Commands = new List<CommandHelp>();
            AllCommands = new List<CommandHelp>();
            BindingSrc = new BindingSource();
            BindingSrc.DataSource = Commands;
            LstCommands.DataSource = BindingSrc;

            LoadCommands();
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

        private void LoadCommands()
        {
            string[] lines = File.ReadAllLines("docs/docgen_src.tsv");

            Commands.Clear();

            for (int i = 1; i < lines.Length; i++)
            {
                string line = lines[i].Trim();
                string[] cols = line.Split('\t');

                CommandHelp cmd = new CommandHelp();
                cmd.Command = cols[0];
                cmd.Params = cols[1];
                cmd.Description = cols[2];
                cmd.Category = cols[3];

                Commands.Add(cmd);
                AllCommands.Add(cmd);
            }

            BindingSrc.ResetBindings(false);
        }

        private void ShowHelpForSelectedCommand()
        {
            CommandHelp cmd = LstCommands.SelectedItem as CommandHelp;
            if (cmd == null)
                return;

            TxtHelp.Text = cmd.ToHelpPanel();
        }

        private void FilterCommandList()
        {
            string search = TxtSearch.Text.Trim().ToUpper();
            
            if (string.IsNullOrEmpty(search))
            {
                Commands.Clear();
                Commands.AddRange(AllCommands);
            }
            else
            {
                Commands.Clear();
                Commands.AddRange(
                    AllCommands.Where(entry => entry.Command.Contains(search)));
            }

            BindingSrc.ResetBindings(false);
            LstCommands.SelectedItem = null;
        }
    }

    public class CommandHelp
    {
        public string Category;
        public string Command;
        public string Params;
        public string Description;

        public override string ToString()
        {
            return Command + Params;
        }

        public string ToHelpPanel()
        {
            return Command + Params +
                Environment.NewLine + Environment.NewLine +
                Description;
        }
    }
}
