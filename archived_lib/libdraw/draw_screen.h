/*
 * =====================================================================================
 *
 *       Filename:  draw_screen.h
 *
 *    Description:  set up the screen for display
 *
 *        Version:  1.0
 *        Created:  12/30/2009 12:01:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  DRAW_SCREEN_INC
#define  DRAW_SCREEN_INC

#include <assert.h>

#include "SDL.h"
#include "read_screen_info.h"


SDL_Surface * SetupScreenCfg(T_Screen *scr_info);

#endif   /* ----- #ifndef DRAW_SCREEN_INC  ----- */
