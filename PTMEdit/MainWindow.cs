namespace PTMEdit;

public partial class MainWindow : Form
{
	public MainWindow()
	{
		InitializeComponent();

		BackColor = Color.FromArgb(0, 0, 80);
		BottomPanel.BackColor = Color.FromArgb(0, 0, 40);
		TopPanel.BackColor = Color.FromArgb(0, 0, 40);
		CenterPanel.BackColor = Color.Transparent;

		TxtProgram.ForeColor = Color.FromArgb(240, 240, 240);
		TxtProgram.BackColor = Color.FromArgb(0, 0, 0);
		TxtProgram.MaxLength = int.MaxValue;
	}
}
