#ifndef DISPLAY_PICTURE_H
#define DISPLAY_PICTURE_H
#include <stdio.h>
#include "SDL.h"
#include "read_screen_info.h"
int  DisplayPicture(int x, int  y, int width, int height, char* image, SDL_Surface *m_surface, SDL_Surface *m_screen);

#endif
