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
 *					Haitao Zhang, zhanghaitao5177@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "draw_line.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DrawLine
 *  Description:  Draw a line on the computer screen according the parameters from .xml
 * =====================================================================================
 */

int DrawLine(T_Line *line_parm, SDL_Surface *m_screen)
{
    int m_start_x, m_start_y;
    int m_stop_x, m_stop_y;
    int m_color;
    int flag;

    if (NULL==m_screen) {
        return -1;
    }


    m_start_x = line_parm->start_point.x;
    m_start_y = line_parm->start_point.y;

    flag = line_parm->line_type;

    if (1==flag) {
        m_stop_x = m_start_x + line_parm->length;
        m_stop_y = m_start_y;
    } else {
        m_stop_y = m_start_y+ line_parm->length;
        m_stop_x = m_start_x;
    }

    m_color = line_parm->color;


    if (m_stop_x>m_screen->w) {
        printf("draw_line.c: The vaule of the coordinate x exceeds the width of screen\n");
        m_stop_x = m_screen->w;
    }
    if (m_stop_y>m_screen->h) {
        printf("draw_line.c: The value of the coordinate y exceeds the height of screen\n");
        m_stop_y = m_screen->h;
    }


    Draw_Line(m_screen, m_stop_x, m_stop_y, m_start_x, m_start_y, m_color);
    SDL_Flip(m_screen);

    return 0;
}
