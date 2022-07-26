#include "t_input_widget.h"
#include "t_globals.h"

t_input_widget::t_input_widget(t_globals* g) {
	buf = g->wnd->GetBuffer();
}
string t_input_widget::show() {
	return string();
}
