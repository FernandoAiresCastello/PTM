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

void PTML::COLOR_MODE()
{
	ARGC(1);
	int&& mode = NUM(1);
	if (mode == 0)
		scr->set_color_mode(t_color_mode::mode0_monochrome);
	else if (mode == 1)
		scr->set_color_mode(t_color_mode::mode1_multicolor);
	else
		error = err.illegal_argument;
}

void PTML::COLOR_SETF()
{
	ARGC(1);
	int&& color = NUM(1);
	scr->color_fg(color);
}

void PTML::COLOR_SETB()
{
	ARGC(1);
	int&& color = NUM(1);
	scr->color_bg(color);
}

void PTML::COLOR_SETBR()
{
	ARGC(1);
	int&& color = NUM(1);
	scr->color_bdr(color);
}

void PTML::PRINT()
{
	ARGC_MIN_MAX(0, 1);
	auto&& value = COUNT(1) ? STR(1) : "";
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
	ARGC_MIN_MAX(2, 3);
	if (COUNT(2)) {
		auto&& binary = STR(2);
		if (binary.has_length(64))
			ptm->get_chr().set(NUM(1), binary);
		else
			error = err.binary_str_expected_64_bits;
	}
	else if (COUNT(3)) {
		auto&& binary = STR(3);
		if (binary.has_length(8))
			ptm->get_chr().set_row(NUM(1), NUM(2), binary);
		else
			error = err.binary_str_expected_8_bits;
	}
}

void PTML::LDPAL()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	ptm->get_pal().load(t_string(USER_ROOT) + filename);
}

void PTML::LDCHR()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	ptm->get_chr().load(t_string(USER_ROOT) + filename);
}

void PTML::LOCATE()
{
	ARGC(2);
	int&& x = NUM(1);
	int&& y = NUM(2);
	scr->locate(x, y);
}

void PTML::CSR_GETX()
{
	ARGC(1);
	ptm->set_var(ARG(1), scr->csrx(), error);
}

void PTML::CSR_GETY()
{
	ARGC(1);
	ptm->set_var(ARG(1), scr->csry(), error);
}

void PTML::FULLSCR()
{
	ARGC_MIN_MAX(0, 1);

	if (COUNT(1))
		ptm->get_wnd().set_fullscreen(BOOL(1));
	else if (COUNT(0))
		ptm->get_wnd().toggle_fullscreen();
}

void PTML::CURSOR()
{
	ARGC(1);
	scr->show_cursor(BOOL(1));
}

void PTML::TILE_NEW()
{
	ARGC(0);
	TILEREG.set_empty();
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
	ptm->set_var(ARG(1), TILEREG.get_char_wraparound(NUM(2)).ix, error);
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
	ptm->set_var(ARG(1), TILEREG.get_char_wraparound(NUM(2)).fgc, error);
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
	ptm->set_var(ARG(1), TILEREG.get_char_wraparound(NUM(2)).bgc, error);
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
	ptm->set_var(ARG(1), TILEREG.data.get(STR(2)), error);
}

void PTML::BUF()
{
	ARGC(1);
	ptm->usr_tilebuf_selected = BOOL(1);
}

void PTML::BSIZE()
{
	ARGC(2);
	ptm->usr_tilebuf.init(NUM(1), NUM(2));
}

void PTML::PUT()
{
	ARGC(0);
	auto&& tile = TILEREG_OR_BLANK_TILE;
	tile.flags.monochrome = false;

	if (IMM) {
		scr->newline();
		scr->set_tile(tile, 0, scr->csry() - 1);
	}
	else {
		if (ptm->usr_tilebuf_selected)
			ptm->usr_tilebuf.set(tile, scr->csrx(), scr->csry());
		else
			scr->set_tile_at_csr(tile);
	}
}

void PTML::GET()
{
	ARGC(0);
	if (ptm->usr_tilebuf_selected)
		ptm->tilereg = ptm->usr_tilebuf.get_copy(scr->csrx(), scr->csry());
	else
		ptm->tilereg = scr->get_tile_at_csr();
}

void PTML::DEL()
{
	ARGC(0);
	if (ptm->usr_tilebuf_selected)
		ptm->usr_tilebuf.set_blank(scr->csrx(), scr->csry());
	else
		scr->set_blank_tile(scr->csrx(), scr->csry(), t_tileflags());
}

void PTML::RECT()
{
	ARGC(4);
	int&& x1 = NUM(1);
	int&& y1 = NUM(2);
	int&& x2 = NUM(3);
	int&& y2 = NUM(4);
	auto&& tile = TILEREG_OR_BLANK_TILE;
	if (ptm->usr_tilebuf_selected)
		ptm->usr_tilebuf.rect_fill(tile, x1, y1, x2, y2);
	else
		scr->rect_fill(tile, x1, y1, x2, y2);
}

void PTML::FILL()
{
	ARGC(0);
	auto&& tile = TILEREG_OR_BLANK_TILE;
	if (ptm->usr_tilebuf_selected)
		ptm->usr_tilebuf.fill(tile);
	else
		scr->fill(tile);
}

void PTML::AUTOREF()
{
	ARGC(1);
	ptm->auto_screen_update = BOOL(1);
}

void PTML::REFRESH()
{
	ARGC(0);
	ptm->refresh_screen();
}

void PTML::DRAW()
{
	ARGC(6);
	int&& x = NUM(1);
	int&& y = NUM(2);
	int&& w = NUM(3);
	int&& h = NUM(4);
	int&& xoff = NUM(5);
	int&& yoff = NUM(6);
	ptm->draw_user_buffer(x, y, w, h, xoff, yoff);
}
