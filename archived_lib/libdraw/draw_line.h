/*
 * =====================================================================================
 *
 *       Filename: DrawLine.c
 *
 *    Description:  Draw a line on the computer screen according the parameters from .xml
 *
 *        Version:  1.0
 *        Created:  12/24/2009 9:13:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include "SDL.h"
#include "SDL_draw.h"
#include "read_screen_info.h"


int DrawLine(T_Line *line_parm, SDL_Surface *m_screen);
#endif
