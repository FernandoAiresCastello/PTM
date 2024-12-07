#pragma once
#include "global.h"
#include "t_rgb.h"

class t_main_window
{
public:
	t_main_window();
	~t_main_window();

	void open(const t_string& title, int buffer_w, int buffer_h, int stretch_w, int stretch_h, const RGB& back_color);
	bool is_open() const;
	void close();
	void update();
	void draw_test_frame();
	void clear(const RGB& back_color);
	void set_pixel(int i, const RGB& color);
	void set_pixel(int x, int y, const RGB& color);
	const RGB& get_pixel(int x, int y) const;
	void toggle_fullscreen();

private:
	bool created = false;
	SDL_Window* wnd = nullptr;
	SDL_Renderer* rend = nullptr;
	SDL_Texture* tex = nullptr;
	int* buffer = nullptr;
	int buffer_len = 0;
	int buffer_h = 0;
	int buffer_w = 0;
};
