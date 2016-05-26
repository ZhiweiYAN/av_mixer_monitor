/*
 * =====================================================================================
 *
 *       Filename: DrawRectangle.c
 *
 *    Description:  Draw a rectangle on the computer screen according the parameters from .xml
 *
 *        Version:  1.0
 *        Created:  12/24/2009 9:13:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Haitao Zhang , zhanghaitao5177@gmail.com
 *         			Zhiwei YAN, jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "draw_rectangle.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DrawRectangle
 *  Description:  Draw a rectangle according the parameters from xml file
 * =====================================================================================
 */

int DrawRectangle(SDL_Surface * screen, T_Rectangle *rectangle_info,T_Screen *screen_info)
{
    int x = 0;
    int y = 0;
    int height = 0;
    int width = 0;
    int color = 0;

    //checking input parameters
    assert(NULL!=screen);
    assert(NULL!=rectangle_info);
    assert(NULL != screen_info);

    x = rectangle_info->start_point.x;
    y = rectangle_info->start_point.y;
    height = rectangle_info->height;
    width = rectangle_info->width;

    if ((x+width)>screen_info->width) {
        printf("warnning:the rectangle's stop x-accordate exceeds the screen's width!\n");
        width = screen_info->width - x;
    }
    if ((y+height)>screen_info->height) {
        printf("warnning:the rectangle's stop y-accordate exceeds the screen's height!\n");
        height = screen_info->height - y;
    }
    color = rectangle_info->color;

    //drawing the rectangle on the screen
    if ( 1== rectangle_info->fill) {
        Draw_FillRect(screen, x, y, width, height, color);
    } else {
        Draw_Rect(screen, x, y, width, height, color);
    }

    return 0;
}


