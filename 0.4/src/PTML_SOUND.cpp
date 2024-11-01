#include "PTML_SOUND.h"
#include "PTML_shared_headers.h"

void PTML::BEEP()
{
	ARGC(2);
	ptm->get_sound_gen().beep(NUM(1), NUM(2));
}

void PTML::PLAY()
{
	ARGC(1);
	ptm->get_sound_gen().play_mml(STR(1));
}

void PTML::LPLAY()
{
	ARGC(1);
	ptm->get_sound_gen().play_mml_loop(STR(1));
}
