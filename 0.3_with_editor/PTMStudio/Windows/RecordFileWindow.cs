using System.Data;
using System.Windows.Forms;

namespace PTMStudio.Windows
{
	public partial class RecordFileWindow : Form
	{
		private const int MaxColumns = 10;

		public RecordFileWindow(string filename, string[] items)
		{
			InitializeComponent();

			DoubleBuffered = true;
			Text = "Record File - " + filename;
			LbSize.Text = "";
			SetData(items);
		}

		private void SetData(string[] items)
		{
			DataTable table = new DataTable();

			for (int i = 0; i < MaxColumns && i < items.Length; i++)
				table.Columns.Add($"Col {i + 1}", typeof(string));

			DataRow row = null;
			for (int i = 0; i < items.Length; i++)
			{
				if (i % MaxColumns == 0)
				{
					row = table.NewRow();
					table.Rows.Add(row);
				}
				row[i % MaxColumns] = items[i];
			}

			DataGrid.DataSource = table;
			LbSize.Text = "Data items: " + items.Length;
		}
	}
}
