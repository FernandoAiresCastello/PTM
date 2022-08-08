#include "t_main_menu_widget.h"
#include "t_list_widget.h"
#include "t_program_editor.h"

t_main_menu_widget::t_main_menu_widget(t_program_editor* editor) {
	this->editor = editor;
	editor->hide_cursor();
	menu = new t_list_widget(editor->globals, "Main menu", 2, 2, 0, 0, 
		editor->color.fg, editor->color.pnl_bg, editor->color.fg_bold, editor->color.sel_bg);

	menu->add_item("Run program", "prg_run");
	menu->add_item("Save program", "prg_save");
	menu->add_item("Save program as", "prg_save_as");
	menu->add_item("Load program", "prg_load");
	menu->add_item("New program", "prg_new");
	menu->add_item("Subroutine list", "sub_list");
	menu->add_item("Help", "help");
	menu->add_item("Quit", "quit");
}
t_main_menu_widget::~t_main_menu_widget() {
	delete menu;
}
void t_main_menu_widget::show(){
	menu->auto_resize();
	t_list_widget_item* item = menu->run_default_selection_loop();
	if (!item) return;
	editor->buf->ClearLayer(t_layer::panel);

	if (item->data == "prg_run") {
		editor->compile_and_run();
	} else if (item->data == "prg_save") {
		editor->save_program(editor->prg_filename);
	} else if (item->data == "prg_save_as") {
		editor->save_program_as();
	} else if (item->data == "prg_load") {
		editor->load_program();
	} else if (item->data == "prg_new") {
		editor->new_program();
	} else if (item->data == "sub_list") {
		editor->find_label();
	} else if (item->data == "help") {
		editor->show_help();
	} else if (item->data == "quit") {
		editor->quit();
	}
}
