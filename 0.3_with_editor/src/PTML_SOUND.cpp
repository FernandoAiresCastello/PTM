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
	ARGC_MIN_MAX(1, 2);

	if (COUNT(1))
		SOUND.play_mml(STR(1));
	else {
		if (BOOL(2))
			SOUND.play_mml_loop(STR(1));
		else
			SOUND.play_mml(STR(1));
	}
}
