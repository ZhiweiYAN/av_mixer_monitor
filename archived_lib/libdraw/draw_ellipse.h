/*
 * =====================================================================================
 *
 *       Filename:  draw_ellipse.h
 *
 *    Description:  draw ellipse on the screen
 *
 *        Version:  1.0
 *        Created:  5/14/2010 11:50:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  DRAW_ELLIPSE_INC_INC
#define  DRAW_ELLIPSE_INC_INC
#include "SDL.h"
#include "SDL_draw.h"
#include "read_screen_info.h"

int DrawEllipse(SDL_Surface *screen, T_Ellipse *ellipse_info, T_Screen *screen_info);
#endif   /* ----- #ifndef DRAW_ELLIPSE_INC_INC  ----- */

