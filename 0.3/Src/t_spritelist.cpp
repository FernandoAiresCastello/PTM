#include "t_spritelist.h"

t_spritelist::t_spritelist()
{
	reset_all();
}

t_spritelist::~t_spritelist()
{
	sprites.clear();
}

t_sprite& t_spritelist::get(int index)
{
	return sprites[index];
}

t_list<t_sprite>& t_spritelist::get_all()
{
	return sprites;
}

void t_spritelist::set(int index, const t_sprite& sprite)
{
	sprites[index] = t_sprite(sprite);
	sprites[index].enabled = true;
}

void t_spritelist::reset_all()
{
	sprites.clear();

	for (int i = 0; i < max_sprites; i++) {
		t_sprite sprite(false);
		sprite.enabled = false;
		sprites.push_back(sprite);
	}
}
