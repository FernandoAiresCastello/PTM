#pragma once

using t_keycode = int32_t;

class t_keyboard
{
public:
	t_keycode key = 0;

	bool alt();
	bool enter();
};
