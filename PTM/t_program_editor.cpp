#include "t_program_editor.h"
#include "t_config.h"

t_program_editor::t_program_editor(TBufferedWindow* wnd, t_config* cfg) {
	this->wnd = wnd;
	buf = wnd->GetBuffer();
	running = false;
	prg_view.max_chars = wnd->Cols - 2;
	prg_view.max_lines = wnd->Rows - 2;

	if (!cfg->autoload.empty()) {
		if (File::Exists(cfg->autoload)) {
			prg.load(cfg->autoload);
		}
	}
}
void t_program_editor::run() {
	running = true;
	while (running) {
		buf->ClearAllLayers();
		draw_border();
		draw_program();
		draw_cursor();
		wnd->Update();
		SDL_Event e = { 0 };
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			running = false;
			break;
		} else if (e.type == SDL_KEYDOWN) {
			on_keydown(e.key.keysym.sym, TKey::Ctrl(), TKey::Shift(), TKey::Alt());
		} else {
			SDL_Delay(1);
		}
	}
}
void t_program_editor::on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) {
	if (key == SDLK_ESCAPE) {
		running = false;
	} else if (key == SDLK_RIGHT) {
		move_prg_csr_right();
	} else if (key == SDLK_LEFT) {
		move_prg_csr_left();
	} else if (key == SDLK_DOWN) {
		move_prg_csr_down();
	} else if (key == SDLK_UP) {
		move_prg_csr_up();
	} else if (key == SDLK_END) {
		if (ctrl) move_prg_csr_end();
		else move_prg_csr_end_x();
	} else if (key == SDLK_HOME) {
		if (ctrl) move_prg_csr_home();
		else move_prg_csr_home_x();
	}
}
void t_program_editor::draw_border() {
	TTileSeq tile(0, color.bdr_bg, color.bdr_bg);
	for (int y = 0; y < buf->Rows; y++) {
		buf->SetTile(tile, 0, 0, y, false);
		buf->SetTile(tile, 0, buf->LastCol, y, false);
	}
	for (int x = 0; x < buf->Cols; x++) {
		buf->SetTile(tile, 0, x, 0, false);
		buf->SetTile(tile, 0, x, buf->LastRow, false);
	}
}
void t_program_editor::draw_program() {
	int x = 1;
	int y = 1;
	for (int line_ix = prg_view.first_line_ix; line_ix < prg_view.first_line_ix + prg_view.max_lines && line_ix < prg.src_lines.size(); line_ix++) {
		x = 1;
		auto& line = prg.src_lines[line_ix];
		for (int char_ix = prg_view.first_char_ix; char_ix < prg_view.first_char_ix + prg_view.max_chars && char_ix < line.length(); char_ix++) {
			int ch = line[char_ix];
			if (ch == '\t') ch = ' ';
			TTileSeq tile(ch, color.fg, color.bg);
			buf->SetTile(tile, 0, x, y, false);
			if (++x > buf->LastCol - 1) break;
		}
		y++;
	}
}
void t_program_editor::draw_cursor() {
	TTileSeq tile;
	int ch = get_char_under_cursor();
	tile.Add(ch, color.bg, color.fg);
	tile.Add(ch, color.fg, color.bg);
	buf->SetTile(tile, 1, scr_csr.x, scr_csr.y, false);
}
string* t_program_editor::get_line_under_cursor() {
	if (prg_csr.line_ix >= 0 && prg_csr.line_ix < prg.src_lines.size()) {
		return &prg.src_lines[prg_csr.line_ix];
	}
	return nullptr;
}
int t_program_editor::get_char_under_cursor() {
	string* line = get_line_under_cursor();
	if (line) {
		if (prg_csr.char_ix >= 0 && prg_csr.char_ix < line->length()) {
			return line->at(prg_csr.char_ix);
		}
	}
	return 0;
}
void t_program_editor::move_prg_csr_right() {
	string* line = get_line_under_cursor();
	if (!line) return;
	if (prg_csr.char_ix < line->length()) {
		prg_csr.char_ix++;
		if (scr_csr.x < buf->LastCol - 1) {
			scr_csr.x++;
		} else {
			prg_view.first_char_ix++;
		}
	}
}
void t_program_editor::move_prg_csr_left() {
	string* line = get_line_under_cursor();
	if (!line) return;
	if (prg_csr.char_ix > 0) {
		if (scr_csr.x > 1) {
			prg_csr.char_ix--;
			scr_csr.x--;
		} else if (prg_view.first_char_ix > 0) {
			prg_csr.char_ix--;
			prg_view.first_char_ix--;
		}
	}
}
void t_program_editor::move_prg_csr_down() {
	string* line = get_line_under_cursor();
	if (!line) return;
	if (prg_csr.line_ix < prg.src_lines.size() - 1) {
		prg_csr.line_ix++;
		if (scr_csr.y < buf->LastRow - 1) {
			scr_csr.y++;
		} else {
			prg_view.first_line_ix++;
		}
		string* line = get_line_under_cursor();
		while (prg_csr.char_ix > line->length()) {
			move_prg_csr_left();
		}
	}
}
void t_program_editor::move_prg_csr_up() {
	if (prg_csr.line_ix > 0) {
		prg_csr.line_ix--;
		if (scr_csr.y > 1) {
			scr_csr.y--;
		} else {
			prg_view.first_line_ix--;
		}
		string* line = get_line_under_cursor();
		while (prg_csr.char_ix > line->length()) {
			move_prg_csr_left();
		}
	}
}
void t_program_editor::move_prg_csr_end_x() {
	string* line = get_line_under_cursor();
	if (!line) return;
	while (prg_csr.char_ix < line->length()) {
		move_prg_csr_right();
	}
}
void t_program_editor::move_prg_csr_home_x() {
	string* line = get_line_under_cursor();
	if (!line) return;
	while (prg_csr.char_ix > 0) {
		move_prg_csr_left();
	}
}
void t_program_editor::move_prg_csr_home() {
	move_prg_csr_home_x();
	while (prg_csr.line_ix > 0) {
		move_prg_csr_up();
	}
}
void t_program_editor::move_prg_csr_end() {
	while (prg_csr.line_ix < prg.src_lines.size() - 1) {
		move_prg_csr_down();
	}
	move_prg_csr_end_x();
}
