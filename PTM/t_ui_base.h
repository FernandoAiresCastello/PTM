#pragma once
#include "common.h"

struct t_config;
struct t_globals;

struct t_ui_base {
	t_ui_base(t_globals* g);
	virtual ~t_ui_base();
	void run();

protected:
	t_globals* globals;
	t_config* cfg;
	TBufferedWindow* wnd;
	TTileBuffer* buf;
	TSound* snd;
	bool running;
	struct {
		int csr_fg;
		int fg;
		int bg;
		int bdr_fg;
		int bdr_bg;
		int label_fg;
		int cmd_fg;
		int comment_fg;
		int sel_bg;
		int fg_bold;
	} color;
	
	virtual void on_run_loop() = 0;
	virtual bool on_exit() = 0;
	virtual void on_keydown(SDL_Keycode key, bool ctrl, bool shift, bool alt) = 0;
	virtual void on_mouse_wheel(int dist_y) = 0;
	
	void poll_events();
	void draw_screen_base();
	void draw_border();
	void print_border(string str, int top_or_bottom, int x);
	void print_border_top(string str, int x);
	void print_border_bottom(string str, int x);
};
