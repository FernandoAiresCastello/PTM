#include "PTML_SPRITES.h"
#include "PTML_shared_headers.h"

void PTML::SPR_NEW()
{
	ARGC(1);
	ptm->add_sprite(STR(1), 0, 0, false);
}

void PTML::SPR_GRID()
{
	ARGC(2);
	SPRITE(STR(1));
	sprite->set_grid(BOOL(2));
}

void PTML::SPR_POS()
{
	ARGC(3);
	SPRITE(STR(1));
	sprite->move_to(NUM(2), NUM(3));
}

void PTML::SPR_X()
{
	ARGC(2);
	SPRITE(STR(1));
	sprite->move_to(NUM(2), sprite->get_y());
}

void PTML::SPR_Y()
{
	ARGC(2);
	SPRITE(STR(1));
	sprite->move_to(sprite->get_x(), NUM(2));
}

void PTML::SPR_GETX()
{
	ARGC(2);
	REQUIRE_IDENT(2);
	SPRITE(STR(1));
	ptm->set_var(IDENT(2), sprite->get_x());
}

void PTML::SPR_GETY()
{
	ARGC(2);
	REQUIRE_IDENT(2);
	SPRITE(STR(1));
	ptm->set_var(IDENT(2), sprite->get_y());
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

void PTML::SPR_DEL()
{
	ARGC(1);
	SPRITE(STR(1));
	scr->delete_sprite(sprite);
}

void PTML::SPR_CLR()
{
	ARGC(0);
	ptm->delete_all_sprites();
}

void PTML::SPR_TGET()
{
	ARGC(1);
	SPRITE(STR(1));
	TILEREG = sprite->get_tile();
}

void PTML::SPR_TSET()
{
	ARGC(1);
	SPRITE(STR(1));
	sprite->set_tile(TILEREG);
}

void PTML::SPR_CHK()
{
	ARGC(3);
	REQUIRE_IDENT(3);
	auto&& sprite1 = get_sprite(STR(1)); if (sprite1 == nullptr) return;
	auto&& sprite2 = get_sprite(STR(2)); if (sprite2 == nullptr) return;
	bool&& collision = sprite1->collides_with(sprite2.get());
	ptm->set_var(IDENT(3), collision ? 1 : 0);
}
