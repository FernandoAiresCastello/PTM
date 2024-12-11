#include <SDL.h>
#include "t_image.h"

t_image::t_image(int width, int height, t_rgb color) : width(width), height(height)
{
	for (int i = 0; i < width * height; i++)
		pixels.emplace_back(color);
}

t_image::t_image(const t_string& file_path)
{
	load(file_path);
}

t_image::~t_image()
{
	pixels.clear();
}

void t_image::load(const t_string& file_path)
{
	SDL_Surface* img = SDL_LoadBMP(file_path.c_str());
	if (!img)
		return;

	pixels.clear();

	const Uint8 bpp = img->format->BytesPerPixel;
	width = img->w;
	height = img->h;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Uint8* pixel = (Uint8*)img->pixels + y * img->pitch + x * bpp;
			Uint32 pixel_data = *(Uint32*)pixel;
			SDL_Color color = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };
			SDL_GetRGB(pixel_data, img->format, &color.r, &color.g, &color.b);
			pixels.emplace_back(t_color(color.r, color.g, color.b).to_rgb());
		}
	}

	SDL_FreeSurface(img);
}

void t_image::set_pixel(int x, int y, t_rgb color)
{
	pixels[y * width + x] = color;
}

t_rgb t_image::get_pixel(int x, int y)
{
	return t_rgb();
}

void t_image::set_transparent(t_rgb color)
{
	transparency_key = color;
	transparent = true;
}

void t_image::set_opaque()
{
	transparent = false;
}

bool t_image::is_transparent() const
{
	return transparent;
}

t_rgb t_image::get_transparency_key() const
{
	return transparency_key;
}

t_list<t_rgb>& t_image::get_pixels()
{
	return pixels;
}
