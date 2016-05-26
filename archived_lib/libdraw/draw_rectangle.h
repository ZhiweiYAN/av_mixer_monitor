/*
 * =====================================================================================
 *
 *       Filename:  drawrectangle.h
 *
 *    Description:   Define some data structures for the screen display elements
 *
 *        Version:  1.0
 *        Created:  12/26/2009 15:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Haitao Zhang  zhanghaitao5177@sina.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef DRAWRECTANGLE_H
#define DRAWRECTANGLE_H

#include <assert.h>
#include "SDL.h"
#include "SDL_draw.h"
#include "read_screen_info.h"
int DrawRectangle(SDL_Surface * screen, T_Rectangle *rectangle_info,T_Screen *screen_info);
#endif
