#include <filesystem>
#include "t_image_pool.h"

namespace fs = std::filesystem;

t_image_pool::t_image_pool()
{
}

t_image_pool::~t_image_pool()
{
	images.clear();
}

t_image* t_image_pool::new_image(int w, int h, const t_color& color)
{
	return &images.emplace_back(w, h, color);
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
