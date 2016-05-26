/* =====================================================================================
 *
 *       Filename: draw_text.h
 *
 *    Description:  Draw a srting on the computer screen according the parameters from .xml
 *
 *        Version:  1.0
 *        Created:  12/28/2009 9:36:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Haitao Zhang , zhanghaitao5177@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef DRAW_TEXT_H
#define DRAW_TEXT_H

#include <assert.h>
#include "SDL.h"
#include "SDL_draw.h"
#include "SDL_ttf.h"
#include "read_screen_info.h"

int  Draw_text(SDL_Surface * m_screen, T_Text *text_info, T_Screen *screen_info);
#endif
