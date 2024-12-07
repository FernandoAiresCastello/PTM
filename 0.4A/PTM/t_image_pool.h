#pragma once
#include "t_image.h"
#include "t_list.h"
#include "t_index.h"

class t_image_pool
{
public:
	t_image_pool();
	~t_image_pool();

	t_index new_image(int w, int h, const t_color& color);
	void new_images(int w, int h, const t_color& color, int count);
	t_image* get(t_index index);
	const t_list<t_image>& get_all();
	void delete_all();
	int size() const;

private:
	t_list<t_image> images;
};
