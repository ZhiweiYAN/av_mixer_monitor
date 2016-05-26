/*
 * =====================================================================================
 *
 *       Filename:  draw_ellipse.c
 *
 *    Description:  draw ellipse according to xml
 *
 *        Version:  1.0
 *        Created:  5/14/2010 11:49:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "draw_ellipse.h"
int DrawEllipse(SDL_Surface *screen, T_Ellipse *ellipse_info, T_Screen *screen_info)
{
    int x = 0;
    int y = 0;
    int x_radius = 0;
    int y_radius = 0;
    int color = 0;

    //checking input parameters
    assert(NULL!=screen);
    assert(NULL!=ellipse_info);
    assert(NULL != screen_info);

    x = ellipse_info->center_point.x;
    y = ellipse_info->center_point.y;
    x_radius = ellipse_info->x_radius;
    y_radius = ellipse_info->y_radius;

    if ((x+x_radius)>screen_info->width) {
        printf("warnning:the ellipse's stop x-accordate exceeds the screen's width!\n");
        x_radius = screen_info->width - x;
    }
    if ((y+y_radius)>screen_info->height) {
        printf("warnning:the ellipse's stop y-accordate exceeds the screen's height!\n");
        y_radius = screen_info->height - y;
    }
    color = ellipse_info->color;

    //drawing the ellipse on the screen
    if ( 1== ellipse_info->fill) {
        Draw_FillEllipse(screen, x, y, x_radius, y_radius, color);
    } else {
        Draw_Ellipse(screen, x, y, x_radius, y_radius, color);
    }

    return 0;

}
