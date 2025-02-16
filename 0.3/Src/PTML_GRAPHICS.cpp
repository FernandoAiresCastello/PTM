#include "PTML_GRAPHICS.h"
#include "PTML_shared_headers.h"

void PTML::COLOR()
{
	ARGC_MIN_MAX(1, 3);

	if (COUNT(3)) {
		scr->color_fg(NUM_WRAP(1, PAL_SIZE));
		scr->color_bg(NUM_WRAP(2, PAL_SIZE));
		scr->color_bdr(NUM_WRAP(3, PAL_SIZE));
		
	}
	else if (COUNT(2)) {
		scr->color_fg(NUM_WRAP(1, PAL_SIZE));
		scr->color_bg(NUM_WRAP(2, PAL_SIZE));
	}
	else if (COUNT(1)) {
		scr->color_fg(NUM_WRAP(1, PAL_SIZE));
	}
}

void PTML::COLOR_MODE()
{
	ARGC(1);

	t_color_mode&& mode = (t_color_mode)NUM(1);

	if (mode == t_color_mode::mode0_monochrome)
		scr->set_color_mode(t_color_mode::mode0_monochrome);
	else if (mode == t_color_mode::mode1_multicolor)
		scr->set_color_mode(t_color_mode::mode1_multicolor);
	else
		error = err.illegal_argument;
}

void PTML::COLOR_SETF()
{
	ARGC(1);
	int&& color = NUM_WRAP(1, PAL_SIZE);
	scr->color_fg(color);
}

void PTML::COLOR_SETB()
{
	ARGC(1);
	int&& color = NUM_WRAP(1, PAL_SIZE);
	scr->color_bg(color);
}

void PTML::COLOR_SETBR()
{
	ARGC(1);
	int&& color = NUM_WRAP(1, PAL_SIZE);
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

	int x = scr->csrx();

	if (COUNT(0))
		scr->newline();
	else {
		auto&& value = STR(1);
		scr->print_string_crlf(value);
	}

	scr->locate_x(x);
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
	ptm->get_pal().set(NUM_WRAP(1, PAL_SIZE), NUM(2));
}

void PTML::CHR()
{
	ARGC_MIN_MAX(2, 3);
	if (COUNT(2)) {
		auto&& binary = STR(2);
		if (binary.has_length(64))
			ptm->get_chr().set(NUM_WRAP(1, CHR_SIZE), binary);
		else
			error = err.binary_str_expected_64_bits;
	}
	else if (COUNT(3)) {
		auto&& binary = STR(3);
		if (binary.has_length(8))
			ptm->get_chr().set_row(NUM_WRAP(1, CHR_SIZE), NUM(2), binary);
		else
			error = err.binary_str_expected_8_bits;
	}
}

void PTML::LOAD_PAL()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	ptm->get_pal().load(t_string(USER_ROOT) + filename);
}

void PTML::SAVE_PAL()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	ptm->get_pal().save(t_string(USER_ROOT) + filename);
}

void PTML::LOAD_CHR()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);

	ptm->get_chr().load(t_string(USER_ROOT) + filename);
}

void PTML::SAVE_CHR()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	ptm->get_chr().save(t_string(USER_ROOT) + filename);
}

void PTML::LOAD_BUF()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);
	REQUIRE_FILE(filename);
	
	ptm->get_screen().load(t_string(USER_ROOT) + filename);

	ptm->suppress_imm_prompt = true;
}

void PTML::SAVE_BUF()
{
	ARGC(1);
	auto&& filename = STR(1);
	VALIDATE_FILENAME(filename);

	ptm->get_screen().save(t_string(USER_ROOT) + filename);
}

void PTML::LOCATE()
{
	ARGC(2);
	int&& x = NUM(1);
	int&& y = NUM(2);
	scr->locate(x, y);
}

void PTML::CSR_SETX()
{
	ARGC(1);
	scr->locate_x(NUM(1));
}

void PTML::CSR_SETY()
{
	ARGC(1);
	scr->locate_y(NUM(1));
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
	bool&& show = BOOL(1);
	scr->show_cursor(show);
}

void PTML::TILE_NEW()
{
	ARGC(0);
	TILEREG.set_empty();
}

void PTML::TILE_ADD()
{
	ARGC_MIN_MAX(0, 3);

	if (COUNT(0))
		TILEREG.set_empty();
	else if (COUNT(3))
		TILEREG.add_char(NUM(1), NUM(2), NUM(3));
	else
		error = err.invalid_argc;
}

void PTML::TILE_SETC()
{
	IF_TILEREG_EMPTY_RET;
	ARGC(2);
	TILEREG.get_char_wraparound(NUM(1)).ix = NUM(2) % ptm->get_chr().size();
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
	TILEREG.get_char_wraparound(NUM(1)).fgc = NUM(2) % ptm->get_pal().size();
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
	TILEREG.get_char_wraparound(NUM(1)).bgc = NUM(2) % ptm->get_pal().size();;
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
	ARGC(4);
	int&& x1 = NUM(1);
	int&& y1 = NUM(2);
	int&& x2 = NUM(3);
	int&& y2 = NUM(4);
	auto&& tile = TILEREG_OR_BLANK_TILE;
	scr->rect_fill(tile, x1, y1, x2, y2);
}

void PTML::FILL()
{
	ARGC(0);
	auto&& tile = TILEREG_OR_BLANK_TILE;
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

void PTML::SET_SPRITE()
{
	ARGC_MIN_MAX(1, 5);

	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	if (COUNT(5)) {
		auto&& x = NUM(2);
		auto&& y = NUM(3);
		bool transparent = BOOL(4);
		bool visible = BOOL(5);
		ptm->get_screen().set_sprite(sprite_number, TILEREG, t_pos(x, y), visible, transparent);
	}
	else if (COUNT(1)) {
		ptm->get_screen().set_sprite_tile_keep_flags(sprite_number, TILEREG);
	}
	else {
		error = err.invalid_argc;
		return;
	}
}

void PTML::MOVE_SPRITE_TO()
{
	ARGC(3);
	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	auto&& x = NUM(2);
	auto&& y = NUM(3);
	ptm->get_screen().get_sprite(sprite_number).move_to(x, y);
}

void PTML::MOVE_SPRITE_DIST()
{
	ARGC(3);
	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	auto&& dx = NUM(2);
	auto&& dy = NUM(3);
	ptm->get_screen().get_sprite(sprite_number).move_dist(dx, dy);
}

void PTML::SHOW_SPRITE()
{
	ARGC(2);
	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	auto&& visible = BOOL(2);
	ptm->get_screen().get_sprite(sprite_number).set_visible(visible);
}

void PTML::GET_SPRITE_TILE()
{
	ARGC(1);
	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	TILEREG = ptm->get_screen().get_sprite(sprite_number).get_tile();
}

void PTML::GET_SPRITE_X()
{
	ARGC(2);
	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	ptm->set_var(ARG(2), ptm->get_screen().get_sprite(sprite_number).get_x(), error);
}

void PTML::GET_SPRITE_Y()
{
	ARGC(2);
	auto&& sprite_number = NUM(1);
	REQUIRE_SPRITE(sprite_number);

	ptm->set_var(ARG(2), ptm->get_screen().get_sprite(sprite_number).get_y(), error);
}

void PTML::ENABLE_SPRITES()
{
	ARGC(1);
	ptm->get_screen().show_sprites(BOOL(1));
}

void PTML::RESET_SPRITES()
{
	ARGC_MIN_MAX(0, 1);
	if (COUNT(0))
		ptm->get_screen().reset_sprites();
	else if (COUNT(1))
		ptm->get_screen().get_sprite(NUM(1)).reset();
}

void PTML::CHECK_SPRITE_COLLISION()
{
	ARGC(3);
	auto&& sprite_1_number = NUM(2);
	auto&& sprite_2_number = NUM(3);
	REQUIRE_SPRITE(sprite_1_number);
	REQUIRE_SPRITE(sprite_2_number);

	auto&& sprite_1 = ptm->get_screen().get_sprite(sprite_1_number);
	auto&& sprite_2 = ptm->get_screen().get_sprite(sprite_2_number);

	bool has_collision = sprite_1.collides_with(&sprite_2);

	ptm->set_var(ARG(1), has_collision ? 1 : 0, error);
}
