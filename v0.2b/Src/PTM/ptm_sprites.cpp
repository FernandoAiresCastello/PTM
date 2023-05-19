#include "ptm_sprites.h"
#include "ptm_color_palette.h"

t_sprite_list sprites;

void t_sprite::set_pos(int x, int y)
{
	this->x = x;
	this->y = y;
}
void t_sprite::move(int dx, int dy)
{
	x += dx;
	y += dy;
}
t_sprite& t_sprite_list::new_sprite(string id)
{
	t_sprite sprite;
	sprites[id] = sprite;
	return sprites[id];
}
t_sprite& t_sprite_list::get_sprite(string id)
{
	return sprites[id];
}
unordered_map<string, t_sprite>& t_sprite_list::get_sprites()
{
	return sprites;
}
void t_sprite_list::remove(string id)
{
	sprites.erase(id);
}
void ptm_draw_visible_sprites()
{
	for (auto& entry : sprites.get_sprites()) {
		t_sprite& spr = entry.second;
		if (!spr.visible) {
			continue;
		}
		if (spr.buf) {
			ptm_clip(spr.buf->get_viewport());
		}
		else {
			ptm_unclip();
		}
		t_tile& frame = spr.tile.frames[0];
		binary& bin = tileset.get(frame.ch);
		rgb fgc = palette.get(frame.fgc);
		rgb bgc = palette.get(frame.bgc);
		ptm_draw_tile_bin(bin, spr.x, spr.y, fgc, bgc, false);
	}
}
