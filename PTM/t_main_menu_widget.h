#pragma once
#include "common.h"

struct t_program_editor;
struct t_list_widget;

struct t_main_menu_widget {
	t_main_menu_widget(t_program_editor* editor);
	~t_main_menu_widget();
	void show();
private:
	t_program_editor* editor;
	t_list_widget* menu;
};
