#pragma once
#include "../Common/common.h"
#include "ptm_graphics_base.h"
#include "ptm_tile_system.h"

struct t_sprite {
	t_tileseq tile;
	t_tilebuf* buf = nullptr;
	bool visible = false;
	int x = 0;
	int y = 0;
	int z = 0;
	void set_pos(int x, int y);
	void move(int dx, int dy);
};
struct t_sprite_list {
	t_sprite& new_sprite(string id);
	t_sprite& get_sprite(string id);
	unordered_map<string, t_sprite>& get_sprites();
	void remove(string id);
	void remove_all();
	bool has(string id);
private:
	unordered_map<string, t_sprite> sprites;
};

extern t_sprite_list sprites;

void ptm_draw_visible_sprites();
