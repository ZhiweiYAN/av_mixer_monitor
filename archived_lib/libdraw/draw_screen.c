/*
 * =====================================================================================
 *
 *       Filename:  draw_screen.c
 *
 *    Description:  Set up the display or the whole screen
 *
 *        Version:  1.0
 *        Created:  12/29/2009 11:53:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#include "draw_screen.h"

SDL_Surface * SetupScreenCfg(T_Screen *scr_info)
{

    assert(NULL!=scr_info);
    SDL_Surface *screen = NULL;

    if (0==scr_info->full_scr) {
        screen = SDL_SetVideoMode( scr_info->width,scr_info->height, scr_info->bpp, SDL_SWSURFACE);
    } else {
        screen = SDL_SetVideoMode( scr_info->width,scr_info->height, scr_info->bpp, SDL_FULLSCREEN|SDL_DOUBLEBUF);
    }
    SDL_WM_SetCaption("DrumTm Products", NULL);
    return screen;
}


