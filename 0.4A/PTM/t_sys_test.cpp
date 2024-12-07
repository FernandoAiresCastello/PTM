#include "t_sys_test.h"
#include "t_ptm.h"

void t_sys_test::on_draw()
{
	int x = ptm.mouse.get_x();
	int y = ptm.mouse.get_y();
	bool left = ptm.mouse.btn_left();
	bool middle = ptm.mouse.btn_middle();
	bool right = ptm.mouse.btn_right();

	ptm.scr.set_backcolor(0x000080);
	ptm.scr.print(t_string::fmt("%i, %i | %i, %i, %i", 
		x, y, left, middle, right), 1, 1, 0xffffff);
}

void t_sys_test::on_keydown(t_keycode& key, t_keymod& mod)
{
}
