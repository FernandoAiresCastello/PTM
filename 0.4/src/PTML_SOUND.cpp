#include "PTML_SOUND.h"
#include "PTML_shared_headers.h"

void PTML::BEEP()
{
	ARGC(2);
	int&& freq = NUM(1);
	int&& length = NUM(2);
	ptm->get_sound_gen().beep(freq, length);
}

void PTML::PLAY()
{
}
