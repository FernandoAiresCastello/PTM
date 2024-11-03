#include "PTML_SOUND.h"
#include "PTML_shared_headers.h"

void PTML::BEEP()
{
	ARGC_MIN_MAX(0, 2);
	if (COUNT(0))
		SOUND.alert();
	else if (COUNT(2))
		SOUND.beep(NUM(1), NUM(2));
	else
		error = err.invalid_argc;
}

void PTML::PLAY()
{
	ARGC(1);
	SOUND.play_mml(STR(1));
}

void PTML::LPLAY()
{
	ARGC(1);
	SOUND.play_mml_loop(STR(1));
}
