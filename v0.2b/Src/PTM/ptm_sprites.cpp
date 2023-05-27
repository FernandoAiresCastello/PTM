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
bool t_sprite::collides_with(t_sprite& other)
{
	return	(x > other.x - PTM_TILE_SIZE) && (x < other.x + PTM_TILE_SIZE) &&
			(y > other.y - PTM_TILE_SIZE) && (y < other.y + PTM_TILE_SIZE);
}
void t_sprite::add_to_buffer(t_tilebuf* tilebuf)
{
	buf = tilebuf;
	tilebuf->add_sprite(this);
}
t_tilebuf* t_sprite::get_buffer()
{
	return buf;
}
void t_sprite::draw()
{
	if (!visible) {
		return;
	}
	if (buf) {
		ptm_clip(buf->get_viewport());
	}
	else {
		ptm_unclip();
	}
	t_tile& frame = tile.frames[tile_animation.frame % tile.length()];
	binary& bin = tileset.get(frame.ch);
	rgb fgc = palette.get(frame.fgc);
	rgb bgc = palette.get(frame.bgc);
	ptm_draw_tile_bin(bin, x, y, fgc, bgc, frame.transparent);
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
void t_sprite_list::remove_all()
{
	sprites.clear();
}
bool t_sprite_list::has(string id)
{
	return sprites.find(id) != sprites.end();
}
void t_sprite_list::draw_all_visible_with_no_buffer()
{
	for (auto& entry : sprites) {
		t_sprite& spr = entry.second;
		if (!spr.get_buffer()) {
			spr.draw();
		}
	}
}
