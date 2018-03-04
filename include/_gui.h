#ifndef   _GUI
#define   _GUI

#include <stdbool.h>

#define  IMG_X "../img/x.png"
#define  IMG_O "../img/circle.png"
#define  O_WIN "../img/o_win.png"
#define  X_WIN "../img/x_win.png"
#define  DRAW  "../img/draw.png"

SDL_Window*   window;
SDL_Surface*  surface;
SDL_Surface*  imageSurface;
SDL_Event     event;
SDL_Renderer* renderer;
SDL_Texture*  img_x;
SDL_Texture*  img_o;

bool running;

#endif