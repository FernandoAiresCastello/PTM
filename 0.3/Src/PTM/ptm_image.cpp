#include "ptm_image.h"
#include "ptm_color_palette.h"
#include "../CppUtils/CppUtils.h"

t_image::t_image() : width(0), height(0), size(0)
{
}
t_image::~t_image()
{
}
bool t_image::load(string filename)
{
	SDL_Surface* img = SDL_LoadBMP(filename.c_str());
	const Uint8 bpp = img->format->BytesPerPixel;
	width = img->w;
	height = img->h;
	size = width * height;

	pixels.clear();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Uint8* pPixel = (Uint8*)img->pixels + y * img->pitch + x * bpp;
			Uint32 PixelData = *(Uint32*)pPixel;
			SDL_Color Color = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };
			SDL_GetRGB(PixelData, img->format, &Color.r, &Color.g, &Color.b);
			pixels.push_back(ptm_rgb_from_components(Color.r, Color.g, Color.b));
		}
	}

	return true;
}
int t_image::get_width()
{
	return width;
}
int t_image::get_height()
{
	return height;
}
int t_image::get_size()
{
	return size;
}
rgb& t_image::get_pixel(int i)
{
	return pixels[i];
}

rgb& t_image::get_pixel(int x, int y)
{
	return pixels[y * width + x];
}
vector<rgb>& t_image::get_pixels()
{
	return pixels;
}
