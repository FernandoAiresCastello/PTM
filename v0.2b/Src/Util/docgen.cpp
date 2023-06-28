#include "docgen.h"
#include "../CppUtils/CppUtils.h"
#include "../Common/common.h"
using namespace CppUtils;

#define DOCGEN_SRC_FILE "docs/docgen_src.tsv"
#define DOCGEN_OUT_FILE "docs/PTM v0.2b Command Reference.html"

struct t_doc_entry {
	string cmd;
	string params;
	string description;
	string category;
};
struct t_doc {
	vector<t_doc_entry> entries;
};
struct t_html {
	vector<string> lines;
	void println(string line) {
		lines.push_back(line);
	}
};

t_doc docgen_parse_file()
{
	t_doc doc;
	auto lines = File::ReadLines(DOCGEN_SRC_FILE, "\n");
	for (auto& line : lines) {
		auto parts = String::Split(line, "\t", true);
		t_doc_entry entry;
		entry.cmd = parts[0];
		entry.params = parts[1];
		entry.description = parts[2];
		entry.category = parts[3];
		doc.entries.push_back(entry);
	}
	return doc;
}
void docgen_begin_html(t_html& html)
{
	html.println("<html>");
	html.println("<head>");
	html.println("<link rel='stylesheet' href='style.css'>");
	html.println("</head>");
	html.println("<body>");

	html.println("<div class='content'>");

	html.println("<div class='title'>");
	html.println("<h1>PTM v0.2b</h1>");
	html.println("</div>");
}
void docgen_end_html(t_html& html)
{
	html.println("</div>");
	html.println("</body>");
	html.println("</html>");
}
void docgen_make_complete_reference(t_html& html, t_doc& doc)
{
	for (auto& entry : doc.entries) {
		html.println("<table class='entry' id='" + entry.cmd + "'>");

		html.println("<tr>");
		html.println("<td class='cmd'>");
		html.println(entry.cmd);
		html.println("</td>");
		html.println("<td class='params'>");
		html.println(entry.params);
		html.println("</td>");
		html.println("</tr>");

		html.println("<tr>");
		html.println("<td class='description' colspan=2>");
		html.println(entry.description);
		html.println("</td>");
		html.println("</tr>");

		html.println("<tr>");
		html.println("<td class='category' colspan=2>");
		html.println("Category: " + entry.category);
		html.println("</td>");
		html.println("</tr>");

		html.println("</table>");
	}
}
void docgen_make_table_of_contents(t_html& html, t_doc& doc)
{
	html.println("<div class='index-container'>");
	html.println("<div class='index-title'>Command Reference</div>");
	html.println("<table class='index'>");

	int col = 0;
	int max_cols = 7;

	for (auto& entry : doc.entries) {
		string cmd = entry.cmd;
		if (col == 0) {
			html.println("<tr>");
		}
		html.println("<td class='index-cmd'>");
		html.println("<a href='#" + cmd + "'>" + cmd + "</a>");
		html.println("</td>");
		col++;
		if (col == max_cols) {
			html.println("</tr>");
			col = 0;
		}
	}

	html.println("</table>");
	html.println("</div>");
}
void docgen_main()
{
	t_html html;
	t_doc doc = docgen_parse_file();
	
	docgen_begin_html(html);
	docgen_make_table_of_contents(html, doc);
	docgen_make_complete_reference(html, doc);
	docgen_end_html(html);

	File::WriteLines(DOCGEN_OUT_FILE, html.lines, "\n");
}
