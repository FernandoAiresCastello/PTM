#include "PTML_GRAPHICS.h"
#include "PTML_shared_headers.h"

void PTML::COLOR()
{
	ARGC_MIN_MAX(1, 3);

	if (COUNT(3)) {
		scr->color_fg(NUM(1));
		scr->color_bg(NUM(2));
		scr->color_bdr(NUM(3));
	}
	else if (COUNT(2)) {
		scr->color_fg(NUM(1));
		scr->color_bg(NUM(2));
	}
	else if (COUNT(1)) {
		scr->color_fg(NUM(1));
	}
}

void PTML::COLOR_F()
{
	ARGC(1);
	scr->color_fg(NUM(1));
}

void PTML::COLOR_B()
{
	ARGC(1);
	scr->color_bg(NUM(1));
}

void PTML::COLOR_BD()
{
	ARGC(1);
	scr->color_bdr(NUM(1));
}

void PTML::COLOR_GET()
{
	ARGC(0);
	scr->println(t_string::fmt("%i,%i,%i", 
		scr->get_fg_color(), scr->get_bg_color(), scr->get_bdr_color()));
}

void PTML::PRINT()
{
	ARGC(1);
	auto&& value = STR(1);

	if (IMM && !value.empty())
		scr->println(value);
	else
		scr->print(value);
}

void PTML::PRINTL()
{
	ARGC(1);
	auto&& value = STR(1);
	scr->println(value);
}

void PTML::PRINTF()
{
	ARGC(2);
	auto&& fmt = STR(1);
	auto&& value = NUM(2);
	scr->print(t_string::fmt(fmt.c_str(), value));
}

void PTML::CLS()
{
	ARGC(0);
	scr->clear();
	scr->locate(0, 0);
}

void PTML::PAL()
{
	ARGC(2);
	ptm->get_pal().set(NUM(1), NUM(2));
}

void PTML::CHR()
{
	ARGC(3);
	ptm->get_chr().set_row(NUM(1), NUM(2), STR(3));
}

void PTML::LOCATE()
{
	ARGC(2);
	scr->locate(NUM(1), NUM(2));
}

void PTML::SCR_FULL()
{
	ARGC_MIN_MAX(0, 1);

	if (COUNT(1))
		ptm->get_wnd().set_fullscreen(BOOL(1));
	else if (COUNT(0))
		ptm->get_wnd().toggle_fullscreen();
}

void PTML::CSR_ON()
{
	ARGC(0);
	scr->show_cursor(true);
}

void PTML::CSR_OFF()
{
	ARGC(0);
	scr->show_cursor(false);
}

void PTML::TILE_NEW()
{
	ARGC_MIN_MAX(0, 3);

	TILEREG.set_empty();

	if (COUNT(0))
		return;
	else if (COUNT(3))
		TILEREG.add_char(NUM(1), NUM(2), NUM(3));
	else
		error = err.invalid_argc;
}

void PTML::TILE_ADD()
{
	ARGC(3);
	TILEREG.add_char(NUM(1), NUM(2), NUM(3));
}

void PTML::TILE_LIST()
{
	ARGC(0);
	for (auto&& ch : TILEREG.get_all_chars()) {
		scr->println(t_string::fmt("%i,%i,%i", ch.ix, ch.fgc, ch.bgc));
	}
}

void PTML::PUT()
{
	IF_TILEREG_EMPTY_RET;
	ARGC_MIN_MAX(0, 2);
	auto& tile = TILEREG;
	tile.flags.monochrome = false;

	if (COUNT(0)) {
		if (IMM) {
			scr->newline();
			scr->set_tile(tile, 0, scr->csry() - 1);
		}
		else {
			scr->set_tile_at_csr(tile);
		}
	}
	else if (COUNT(2))
		scr->set_tile(tile, NUM(1), NUM(2));
	else
		error = err.invalid_argc;
}

void PTML::PUTC()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(0);
	auto& tile = TILEREG;
	tile.flags.monochrome = false;
	scr->set_tile_at_csr(tile);
	scr->move_cursor_wrap_x(1);
}

void PTML::RECT()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(5);
	int&& x1 = NUM(1);
	int&& y1 = NUM(2);
	int&& x2 = NUM(3);
	int&& y2 = NUM(4);
	bool&& fill = BOOL(5);
	if (fill)
		scr->rect_fill(TILEREG, x1, y1, x2, y2);
	else
		scr->rect_border(TILEREG, x1, y1, x2, y2);
}

void PTML::RECT_DEL()
{
	ARGC(4);
	int&& x1 = NUM(1);
	int&& y1 = NUM(2);
	int&& x2 = NUM(3);
	int&& y2 = NUM(4);
	scr->rect_clear(x1, y1, x2, y2);
}

void PTML::FILL()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(0);
	scr->fill(TILEREG);
}

void PTML::GET()
{
	ARGC_MIN_MAX(0, 2);

	if (COUNT(0)) {
		if (NOT_IMM) {
			ptm->set_tilereg(scr->get_tile_at_csr());
		}
	}
	else if (COUNT(2))
		ptm->set_tilereg(scr->get_tile(t_pos(NUM(1), NUM(2))));
	else
		error = err.invalid_argc;
}

void PTML::DEL()
{
	ARGC_MIN_MAX(0, 2);

	if (COUNT(0)) {
		if (NOT_IMM) {
			scr->set_blank_tile(scr->csrx(), scr->csry(), t_tileflags());
		}
	}
	else if (COUNT(2))
		scr->set_blank_tile(NUM(1), NUM(2));
	else
		error = err.invalid_argc;
}

void PTML::SCR_ON()
{
	ARGC(0);
	ptm->auto_screen_update = true;
}

void PTML::SCR_OFF()
{
	ARGC(0);
	ptm->auto_screen_update = false;
}

void PTML::REFRESH()
{
	ARGC(0);
	ptm->refresh_screen();
}
