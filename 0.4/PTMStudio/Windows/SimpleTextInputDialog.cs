using System.Windows.Forms;

namespace PTMStudio.Windows
{
	public partial class SimpleTextInputDialog : Form
	{
		public new string Text => TxtInput.Text.Trim();

		public bool UppercaseOnly
		{
			set => TxtInput.CharacterCasing = CharacterCasing.Upper;
		}

		public SimpleTextInputDialog(string title, string prompt, string defaultText = "")
		{
			InitializeComponent();

			base.Text = title;
			LbPrompt.Text = prompt;
			TxtInput.Text = defaultText;

			KeyPreview = true;
			KeyDown += SimpleTextInputDialog_KeyDown;
		}

		private void SimpleTextInputDialog_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Escape)
				DialogResult = DialogResult.Cancel;
			else if (e.KeyCode == Keys.Enter)
				DialogResult = DialogResult.OK;
		}
	}
}
