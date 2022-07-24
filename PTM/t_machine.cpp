#include "t_machine.h"
#include "t_default_gfx.h"

t_machine::t_machine(TBufferedWindow* wnd) {
	this->wnd = wnd;
	wnd->SetBackColor(0);
	tilebuf = wnd->GetBuffer();
	tilebuf->ClearAllLayers();

	original_chr = wnd->GetCharset();
	chr = new TCharset();
	t_default_gfx::init_charset(chr);
	wnd->SetCharset(chr);

	original_pal = wnd->GetPalette();
	pal = new TPalette();
	t_default_gfx::init_palette(pal);
	wnd->SetPalette(pal);

	wnd->Update();

	set_const("kb.right", 1073741903);
	set_const("kb.left", 1073741904);
	set_const("kb.down", 1073741905);
	set_const("kb.up", 1073741906);
}
t_machine::~t_machine() {
	wnd->SetCharset(original_chr);
	wnd->SetPalette(original_pal);
	snd->StopMainSound();
	snd->StopSubSound();
	delete chr;
	delete pal;
}
void t_machine::on_loop() {
}
void t_machine::set_const(string id, int value) {
	vars[id] = t_variable(value, true);
}
void t_machine::set_const(string id, string value) {
	vars[id] = t_variable(value, true);
}
void t_machine::set_var(string id, int value) {
	vars[id] = t_variable(value);
}
void t_machine::set_var(string id, string value) {
	vars[id] = t_variable(value);
}
