#pragma once

struct t_tile_animation
{
	int frame = 0;
	int ctr_next_frame = 0;
	int ctr_next_frame_max = 20;
	int enabled = true;

	void update()
	{
		if (!enabled)
			return;

		ctr_next_frame++;
		if (ctr_next_frame >= ctr_next_frame_max) {
			ctr_next_frame = 0;
			frame++;
		}
	}

	void set_speed(int speed)
	{
		if (speed <= 0) {
			enabled = false;
			return;
		}
		if (speed > 100) {
			speed = 100;
		}
		enabled = true;
		ctr_next_frame = 0;
		ctr_next_frame_max = 100 - speed;
	}
};
