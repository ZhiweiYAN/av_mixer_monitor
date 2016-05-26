/*
 * =====================================================================================
 *
 *       Filename:  init_display.h
 *
 *    Description:  Initialize the display and all lines, rectangles and so on.
 *
 *        Version:  1.0
 *        Created:  1/1/2010 1:46:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  INIT_DISPLAY_H_INC
#define  INIT_DISPLAY_H_INC

#include "read_screen_info.h"
#include "draw_screen.h"
#include "draw_line.h"
#include "draw_rectangle.h"
#include "draw_ellipse.h"
#include "draw_text.h"
#include "draw_image.h"

SDL_Surface * InitXmlScr(char *xml_file);
void UnInitXmlSrc(void);
#endif   /* ----- #ifndef INIT_DISPLAY_H_INC  ----- */
