#include "PTML_SPRITES.h"
#include "PTML_shared_headers.h"

void PTML::SPR_NEW()
{
	ARGC(1);
	ptm->add_sprite(STR(1), 0, 0, false);
}

void PTML::SPR_POS()
{
	ARGC(3);
	SPRITE(STR(1));
	sprite->move_to(NUM(2), NUM(3));
}

void PTML::SPR_SHOW()
{
	ARGC(2);
	SPRITE(STR(1));
	sprite->set_visible(BOOL(2));
}

void PTML::SPR_MOVE()
{
	ARGC(3);
	SPRITE(STR(1));
	sprite->move_dist(NUM(2), NUM(3));
}

void PTML::SPR_CLR()
{
	ARGC(0);
	ptm->delete_all_sprites();
}
