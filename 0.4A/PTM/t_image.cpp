#include <SDL3/SDL.h>
#include "t_image.h"

t_image::t_image()
{
}

t_image::t_image(int w, int h, const t_color& back_color)
{
	width = w;
	height = h;

	for (int i = 0; i < w * h; i++)
		pixels.emplace_back(back_color);
}

t_image::~t_image()
{
	pixels.clear();
}

void t_image::set_pixel(int x, int y, const t_color& color)
{
	if (y >= 0 && x >= 0 && y < height && x < width)
		pixels[y * width + x] = color;
}

const t_color& t_image::get_pixel(int x, int y) const
{
	if (y >= 0 && x >= 0 && y < height && x < width)
		return pixels[y * width + x];

	return t_color::invalid;
}

void t_image::set_transparency_key(const t_color& color)
{
	transparency_key = color;
	transparent = true;
}

const t_color& t_image::get_transparency_key() const
{
	return transparency_key;
}

void t_image::set_transparent(bool transp)
{
	transparent = transp;
}

bool t_image::is_transparent() const
{
	return transparent;
}

int t_image::get_width() const
{
	return width;
}

int t_image::get_height() const
{
	return height;
}

bool t_image::load(const t_string& filename)
{
	pixels.clear();

	SDL_Surface* img = SDL_LoadBMP(filename.c_str());
	if (!img)
		return false;

	width = img->w;
	height = img->h;

    if (SDL_MUSTLOCK(img)) {
        if (!SDL_LockSurface(img))
            return false;
    }

    uint8_t* surface_pixels = static_cast<uint8_t*>(img->pixels);
    const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(img->format);

    for (int y = 0; y < img->h; ++y) {
        for (int x = 0; x < img->w; ++x) {
            uint32_t* pixelAddr = reinterpret_cast<uint32_t*>(
				surface_pixels + y * img->pitch + x * format->bytes_per_pixel);

            uint8_t r, g, b, a;
            SDL_GetRGBA(*pixelAddr, format, nullptr, &r, &g, &b, &a);
			pixels.emplace_back(r, g, b);
        }
    }

    if (SDL_MUSTLOCK(img))
        SDL_UnlockSurface(img);

	SDL_DestroySurface(img);

	return true;
}
