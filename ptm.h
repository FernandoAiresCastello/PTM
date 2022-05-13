#include <SDL2/SDL.h>

void ptm_init();
void ptm_exit();
void ptm_halt();
void ptm_open_window(int wnd_w, int wnd_h, int buf_w, int buf_h);
void ptm_update_window();
void ptm_put_pixel_linear(int i, int rgb);
void ptm_put_pixel(int x, int y, int rgb);
void ptm_clear_window(int rgb);
void ptm_msgbox(const char* msg);
