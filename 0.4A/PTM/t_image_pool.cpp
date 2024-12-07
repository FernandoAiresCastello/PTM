#include "t_image_pool.h"

t_image_pool::t_image_pool()
{
}

t_image_pool::~t_image_pool()
{
	images.clear();
}

t_index t_image_pool::new_image(int w, int h, const t_color& color)
{
	images.emplace_back(w, h, color);

	return images.size() - 1;
}

void t_image_pool::new_images(int w, int h, const t_color& color, int count)
{
	for (int i = 0; i < count; i++)
		new_image(w, h, color);
}

t_image* t_image_pool::get(t_index index)
{
	if (index >= 0 && index < images.size())
		return &images[index];

	return nullptr;
}

const t_list<t_image>& t_image_pool::get_all()
{
	return images;
}

void t_image_pool::delete_all()
{
	images.clear();
}

int t_image_pool::size() const
{
	return images.size();
}
