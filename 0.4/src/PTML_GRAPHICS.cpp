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

void PTML::COLOR_Q()
{
	ARGC(0);
	scr->print_string_crlf(t_string::fmt("%i,%i,%i", 
		scr->get_fg_color(), scr->get_bg_color(), scr->get_bdr_color()));
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

void PTML::PAL_Q()
{
	ARGC(1);
	t_index&& color = NUM(1);
	t_tile tile(0, color, color);
	tile.flags.monochrome = false;
	scr->newline();
	scr->set_tile(tile, 0, scr->csry() - 1);
}

void PTML::CHR_Q()
{
	ARGC(1);
	t_index&& ch = NUM(1);
	t_tile tile(ch, scr->get_fg_color(), scr->get_bg_color());
	scr->newline();
	scr->set_tile(tile, 0, scr->csry() - 1);
}

void PTML::PAL_RESET()
{
	ARGC(0);
	ptm->get_pal().reset();
}

void PTML::CHR_RESET()
{
	ARGC(0);
	ptm->get_chr().reset();
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

void PTML::TILE_Q()
{
	ARGC(0);
	t_list<t_tile> tile_chars;
	t_list<t_string> tile_values;

	for (auto&& ch : TILEREG.get_all_chars()) {
		tile_chars.push_back(ch);
		tile_values.push_back(t_string::fmt(" %i,%i,%i", ch.ix, ch.fgc, ch.bgc));
	}

	if (scr->print_lines_with_icon(tile_chars, tile_values, ptm)) {
		scr->print_string_crlf("Break"); 
	}

	if (TILEREG.data.is_not_empty()) {
		t_list<t_string> props;
		for (auto& prop : TILEREG.data.get_all())
			props.push_back(t_string::fmt("%s: %s", prop.first.c_str(), prop.second.c_str()));

		PRINT_LIST(props);
	}
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
	ptm->set_var(STR(1), TILEREG.data.get(STR(2)));
}

void PTML::TILE_SAVE()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(1);
	ptm->save_tilereg(STR(1));
}

void PTML::TILE_LOAD()
{
	ARGC(1);
	auto&& name = STR(1);
	if (!ptm->has_tilereg(name)) {
		error = err.tile_preset_not_found;
		return;
	}

	ptm->load_tilereg(name);
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

void PTML::LINE_H()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(3);
	int&& y = NUM(1);
	int&& x1 = NUM(2);
	int&& x2 = NUM(3);
	scr->rect_fill(TILEREG, x1, y, x2, y);
}

void PTML::LINE_V()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(3);
	int&& x = NUM(1);
	int&& y1 = NUM(2);
	int&& y2 = NUM(3);
	scr->rect_fill(TILEREG, x, y1, x, y2);
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
			ptm->tilereg = scr->get_tile_at_csr();
		}
	}
	else if (COUNT(2))
		ptm->tilereg = scr->get_tile(t_pos(NUM(1), NUM(2)));
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
