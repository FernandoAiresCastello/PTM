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
}
t_machine::~t_machine() {
	wnd->SetCharset(original_chr);
	wnd->SetPalette(original_pal);
	delete chr;
	delete pal;
}
void t_machine::on_loop() {
}
