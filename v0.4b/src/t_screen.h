#pragma once

class t_tilebuffer;

class t_screen
{
public:
	t_screen();

	void set_tilebuf(t_tilebuffer* buf);

private:
	t_tilebuffer* buf = nullptr;
};
