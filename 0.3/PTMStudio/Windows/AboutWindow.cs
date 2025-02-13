using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace PTMStudio.Windows
{
	public partial class AboutWindow : Form
	{
		public AboutWindow(string buildTimestamp)
		{
			InitializeComponent();

			LbAbout.Text = LbAbout.Text.Replace("{build_timestamp}", buildTimestamp);
		}

		private void BtnOk_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void BtnItchIo_Click(object sender, EventArgs e)
		{
			Process.Start("https://fernandoairescastello.itch.io/ptm");
		}

		private void BtnGitHub_Click(object sender, EventArgs e)
		{
			Process.Start("https://github.com/FernandoAiresCastello/PTM");
		}
	}
}
