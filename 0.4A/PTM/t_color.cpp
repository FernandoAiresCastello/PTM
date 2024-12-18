#include "t_color.h"
#include "t_util.h"

t_color t_color::invalid = 0x000000;

t_color::t_color() : r(0), g(0), b(0)
{
}

t_color::t_color(int r, int g, int b) : r(r), g(g), b(b)
{
}

t_color::t_color(RGB rgb)
{
    unpack_rgb(rgb, &r, &g, &b);
}

t_color::t_color(const t_color& other)
{
    r = other.r;
    g = other.g;
    b = other.b;
}

bool t_color::operator==(const t_color& other) const
{
    return r == other.r && g == other.g && b == other.b;
}

t_color& t_color::operator=(const t_color& other)
{
    if (this == &other)
        return *this;

    r = other.r;
    g = other.g;
    b = other.b;

    return *this;
}

RGB t_color::to_rgb() const
{
    return pack_rgb(r, g, b);
}

RGB t_color::pack_rgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

void t_color::unpack_rgb(RGB rgb, int* r, int* g, int* b)
{
    *r = (rgb >> 16) & 0xFF;
    *g = (rgb >> 8) & 0xFF;
    *b = rgb & 0xFF;
}

t_color t_color::get_random()
{
    return t_color(t_util::rnd(0, 255), t_util::rnd(0, 255), t_util::rnd(0, 255));
}

void t_color::set(RGB rgb)
{
    unpack_rgb(rgb, &r, &g, &b);
}

void t_color::set(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void t_color::set_r(int r) { this->r = r; }
void t_color::set_g(int g) { this->g = g; }
void t_color::set_b(int b) { this->b = b; }

int t_color::get_r() const { return r; }
int t_color::get_g() const { return g; }
int t_color::get_b() const { return b; }
