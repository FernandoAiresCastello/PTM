#include "t_sprite.h"

t_sprite::t_sprite() : tile(), pos()
{
}

t_sprite::t_sprite(const t_tile& tile, const t_pos& pos) : tile(tile), pos(pos)
{
}
