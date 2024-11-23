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

void PTML::COLOR_MONO()
{
	ARGC(0);
	scr->set_color_mode(t_color_mode::mode0_monochrome);
}

void PTML::COLOR_MULTI()
{
	ARGC(0);
	scr->set_color_mode(t_color_mode::mode1_multicolor);
}

void PTML::COLOR_SETF()
{
	ARGC(1);
	scr->color_fg(NUM(1));
}

void PTML::COLOR_SETB()
{
	ARGC(1);
	scr->color_bg(NUM(1));
}

void PTML::COLOR_SETBR()
{
	ARGC(1);
	scr->color_bdr(NUM(1));
}

void PTML::COLOR_GETF()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), scr->get_fg_color());
}

void PTML::COLOR_GETB()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), scr->get_bg_color());
}

void PTML::COLOR_GETBR()
{
	ARGC(1);
	REQUIRE_IDENT(1);
	ptm->set_var(IDENT(1), scr->get_bdr_color());
}

void PTML::PRINT()
{
	ARGC(1);
	auto&& value = STR(1);
	if (IMM && !value.empty())
		scr->print_string_crlf(value);
	else
		scr->print_string(value);
}

void PTML::PRINTL()
{
	ARGC_MIN_MAX(0, 1);
	if (COUNT(0))
		scr->newline();
	else {
		auto&& value = STR(1);
		scr->print_string_crlf(value);
	}
}

void PTML::PRINTF()
{
	ARGC(2);
	auto&& fmt = STR(1);
	auto&& value = NUM(2);
	scr->print_string(t_string::fmt(fmt.c_str(), value));
}

void PTML::CLS()
{
	ARGC(0);
	scr->clear();
	scr->locate(0, 0);
	scr->set_insert_mode(false);
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

void PTML::TILE_SETC()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	TILEREG.get_char_wraparound(NUM(1)).ix = NUM(2);
}

void PTML::TILE_GETC()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	ptm->set_var(IDENT(1), TILEREG.get_char_wraparound(NUM(2)).ix);
}

void PTML::TILE_SETF()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	TILEREG.get_char_wraparound(NUM(1)).fgc = NUM(2);
}

void PTML::TILE_GETF()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	ptm->set_var(IDENT(1), TILEREG.get_char_wraparound(NUM(2)).fgc);
}

void PTML::TILE_SETB()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	TILEREG.get_char_wraparound(NUM(1)).bgc = NUM(2);
}

void PTML::TILE_GETB()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	ptm->set_var(IDENT(1), TILEREG.get_char_wraparound(NUM(2)).bgc);
}

void PTML::TILE_SETP()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	TILEREG.data.set(STR(1), STR(2));
}

void PTML::TILE_GETP()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	ptm->set_var(IDENT(1), TILEREG.data.get(STR(2)));
}

void PTML::PUT()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(0);
	auto& tile = TILEREG;
	tile.flags.monochrome = false;

	if (IMM) {
		scr->newline();
		scr->set_tile(tile, 0, scr->csry() - 1);
	}
	else {
		scr->set_tile_at_csr(tile);
	}
}

void PTML::GET()
{
	ARGC(0);
	ptm->tilereg = scr->get_tile_at_csr();
}

void PTML::DEL()
{
	ARGC(0);
	scr->set_blank_tile(scr->csrx(), scr->csry(), t_tileflags());
}

void PTML::RECT()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(4);
	int&& x1 = NUM(1);
	int&& y1 = NUM(2);
	int&& x2 = NUM(3);
	int&& y2 = NUM(4);
	scr->rect_fill(TILEREG, x1, y1, x2, y2);
}

void PTML::FILL()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(0);
	scr->fill(TILEREG);
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
