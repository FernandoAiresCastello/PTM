#include "t_machine.h"

t_machine::t_machine(TBufferedWindow* wnd) {
	this->wnd = wnd;
	wnd->SetBackColor(0);
	tilebuf = wnd->GetBuffer();
	tilebuf->ClearAllLayers();

	original_chr = wnd->GetCharset();
	chr = new TCharset();
	wnd->SetCharset(chr);

	original_pal = wnd->GetPalette();
	pal = new TPalette();
	wnd->SetPalette(pal);

	default_view.x = 0;
	default_view.y = 0;
	default_view.scroll_x = 0;
	default_view.scroll_y = 0;
	default_view.w = tilebuf->Cols;
	default_view.h = tilebuf->Rows;
	cur_view = &default_view;
}
t_machine::~t_machine() {
	wnd->SetCharset(original_chr);
	wnd->SetPalette(original_pal);
	delete chr;
	delete pal;
}
void t_machine::on_loop() {
	wnd->Update();
}
bool t_machine::is_csr_within_view() {
	return cur_view && csr.x >= 0 && csr.y >= 0 && csr.x < cur_view->w && csr.y < cur_view->h;
}
