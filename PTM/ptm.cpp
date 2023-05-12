#include "ptm.h"

//=============================================================================
//      PTM
//=============================================================================

struct {
    vector<int> code;
    vector<int> data;

    struct {
        addr pixelbuf_begin = 0;
        addr pixelbuf_end = 0;
        addr bgcol = 0;
        addr fullscreen = 0;
    } mmap;

    struct {
        SDL_Window* wnd = nullptr;
        SDL_Renderer* rend = nullptr;
        SDL_Texture* tx = nullptr;
        const int buf_w = 256;
        const int buf_h = 192;
        const int buf_len = buf_w * buf_h;
        const int wnd_size = 4;
    } scr;

} ptm;

#define ADDR(mmap_id_) ptm.mmap.mmap_id_
#define MEM(mmap_id_) ptm.data[ptm.mmap.mmap_id_]

//=============================================================================
//      PUBLIC API
//=============================================================================
void ptm_init(string program_file)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    ptm_load_program(program_file);
    ptm_init_memory();
    ptm_init_window();
}
void ptm_exit()
{
    ptm_free_window();
	SDL_Quit();
    exit(0);
}
void ptm_halt()
{
    while (true) {
        ptm_update();
    }
}
void ptm_abort(string msg)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PTM Fatal Error", msg.c_str(), ptm.scr.wnd);
    ptm_exit();
}
void ptm_update()
{
    static int pitch;
    static void* pixels;
    int* pixel_buf = &MEM(pixelbuf_begin);

    SDL_LockTexture(ptm.scr.tx, NULL, &pixels, &pitch);
    SDL_memcpy(pixels, pixel_buf, ptm.scr.buf_len * sizeof(rgb));
    SDL_UnlockTexture(ptm.scr.tx);
    SDL_RenderClear(ptm.scr.rend);
    SDL_RenderCopy(ptm.scr.rend, ptm.scr.tx, NULL, NULL);
    SDL_RenderPresent(ptm.scr.rend);

    ptm_proc_events();
}
void ptm_proc_events()
{
    SDL_Event e = { 0 };
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            ptm_exit();
            return;
        }
        else if (e.type == SDL_KEYDOWN) {
            const SDL_Keycode key = e.key.keysym.sym;
            if (key == SDLK_ESCAPE) {
                ptm_exit();
                return;
            }
            else if (key == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
                ptm_toggle_fullscreen();
                return;
            }
        }
    }
}
void ptm_poke(addr address, int value)
{
    ptm.data[address] = value;
}
void ptm_clear_screen()
{
    for (addr i = ADDR(pixelbuf_begin); i <= ADDR(pixelbuf_end); i++) {
        ptm_poke(i, MEM(bgcol));
    }
}
void ptm_wnd_bgcol(rgb color)
{
    MEM(bgcol) = color;
}
void ptm_toggle_fullscreen()
{
    Uint32 flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    Uint32 is_full = SDL_GetWindowFlags(ptm.scr.wnd) & flag;
    SDL_SetWindowFullscreen(ptm.scr.wnd, is_full ? 0 : flag);

    MEM(fullscreen) = is_full;

    ptm_update();
}

//=============================================================================
//      PRIVATE API
//=============================================================================

void ptm_load_program(string path)
{
    ifstream file(path, ios::binary | ios::ate);
    streamsize size = file.tellg();
    string buffer(size, ' ');
    file.seekg(0, ios::beg);
    file.read(&buffer[0], size);

    std::istringstream iss(buffer);
    int value;
    while (iss >> value) {
        ptm.code.push_back(value);
    }
}
void ptm_init_window()
{
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    ptm.scr.wnd = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        ptm.scr.wnd_size * ptm.scr.buf_w, ptm.scr.wnd_size * ptm.scr.buf_h, 0);
    ptm.scr.rend = SDL_CreateRenderer(ptm.scr.wnd, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderSetLogicalSize(ptm.scr.rend, ptm.scr.buf_w, ptm.scr.buf_h);
    ptm.scr.tx = SDL_CreateTexture(ptm.scr.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, ptm.scr.buf_w, ptm.scr.buf_h);
    SDL_SetTextureBlendMode(ptm.scr.tx, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawBlendMode(ptm.scr.rend, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(ptm.scr.rend, 0, 0, 0, 255);
    SDL_RenderClear(ptm.scr.rend);
    SDL_RenderPresent(ptm.scr.rend);
    SDL_SetWindowPosition(ptm.scr.wnd, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RaiseWindow(ptm.scr.wnd);
}
void ptm_free_window()
{
    SDL_DestroyTexture(ptm.scr.tx);      ptm.scr.tx = NULL;
    SDL_DestroyRenderer(ptm.scr.rend);   ptm.scr.rend = NULL;
    SDL_DestroyWindow(ptm.scr.wnd);      ptm.scr.wnd = NULL;
}

#define MMAP(mmap_id_) ADDR(mmap_id_) = ptm.data.size() - 1;

void ptm_init_memory()
{
    ptm.data.clear();

    // VRAM - Pixel Buffer
    ADDR(pixelbuf_begin) = 0;
    for (int i = 0; i < ptm.scr.buf_len; i++) {
        ptm.data.push_back(0x101010);
    }
    MMAP(pixelbuf_end);
    // VRAM - Background Color
    ptm.data.push_back(0);
    MMAP(bgcol);
    // VRAM - Fullscreen Flag
    ptm.data.push_back(0);
    MMAP(fullscreen);
}
