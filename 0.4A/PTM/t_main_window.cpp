#include <random>
#include "t_main_window.h"
#include "t_color.h"

const RGB out_of_bounds_color = t_color::invalid.to_rgb();

t_main_window::t_main_window()
{
}

t_main_window::~t_main_window()
{
    close();
}

void t_main_window::open(const t_string& title, int buffer_w, int buffer_h, int stretch_w, int stretch_h)
{
    this->buffer_w = buffer_w;
    this->buffer_h = buffer_h;

    buffer_len = buffer_w * buffer_h * sizeof(int);
    buffer = new int[buffer_len];

    SDL_CreateWindowAndRenderer(title.c_str(), buffer_w * stretch_w, buffer_h * stretch_h, 0, &wnd, &rend);
    SDL_SetWindowPosition(wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, buffer_w, buffer_h);

    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderLogicalPresentation(rend, buffer_w, buffer_h, SDL_LOGICAL_PRESENTATION_STRETCH);
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(rend, tex);
    SDL_RenderClear(rend);
    SDL_RenderPresent(rend);
    
    clear(0x000000);
    update();

    created = true;
}

bool t_main_window::is_open() const
{
    return created;
}

void t_main_window::close()
{
    SDL_DestroyRenderer(rend);
    rend = nullptr;
    SDL_DestroyWindow(wnd);
    wnd = nullptr;
    delete buffer;
    buffer = nullptr;

    created = false;
}

void t_main_window::update()
{
    static void* pixels;
    static int pitch;
    SDL_LockTexture(tex, nullptr, &pixels, &pitch);
    SDL_memcpy(pixels, buffer, buffer_len);
    SDL_UnlockTexture(tex);
    SDL_RenderTexture(rend, tex, nullptr, nullptr);
    SDL_RenderPresent(rend);
}

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> dis(0x000000, 0xffffff);

void t_main_window::draw_test_frame()
{
    for (int i = 0; i < buffer_len; i++)
        set_pixel(i, dis(gen));
}

void t_main_window::clear(const RGB& back_color)
{
    for (int i = 0; i < buffer_len; i++)
        set_pixel(i, back_color);
}

void t_main_window::set_pixel(int i, const RGB& color)
{
    buffer[i] = color;
}

void t_main_window::set_pixel(int x, int y, const RGB& color)
{
    if (y >= 0 && x >= 0 && y < buffer_h && x < buffer_w)
        buffer[y * buffer_w + x] = color;
}

const RGB& t_main_window::get_pixel(int x, int y) const
{
    if (y >= 0 && x >= 0 && y < buffer_h && x < buffer_w)
        return buffer[y * buffer_w + x];

    return out_of_bounds_color;
}

void t_main_window::toggle_fullscreen()
{
    Uint32 flag = SDL_WINDOW_FULLSCREEN;
    Uint32 is_full = SDL_GetWindowFlags(wnd) & flag;
    SDL_SetWindowFullscreen(wnd, is_full ? 0 : flag);
    update();
}
