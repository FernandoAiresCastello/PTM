#pragma once
#include "t_sprite.h"
#include "t_list.h"

class t_spritelist
{
public:
	static const int max_sprites = 256;

	t_spritelist();
	~t_spritelist();

	t_sprite& get(int index);
	t_list<t_sprite>& get_all();
	void set(int index, const t_sprite& sprite);
	void reset_all();

private:
	t_list<t_sprite> sprites;
};
