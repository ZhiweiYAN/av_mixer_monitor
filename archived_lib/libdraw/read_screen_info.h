/*
 * =====================================================================================
 *
 *       Filename:  readscreeninfo.h
 *
 *    Description:   Read the elements on the computer screen from .xml
 *
 *        Version:  1.0
 *        Created:  12/24/2009 9:29:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  READSCREENINFO_H_INC
#define  READSCREENINFO_H_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mxml.h"

#define FILENAME_LEN 100
#define PATHNAME_LEN 200
#define STRINGS_LEN 2000

typedef struct {
    int width;
    int height;
    int bg_color;
    int bpp;
    int full_scr;
}T_Screen;

typedef struct {
    int x;
    int y;
}T_Point;

typedef struct {
    T_Point start_point;
    int  length;
    int  width;
    int  color;
    int line_type; // line_type = 0 means drawing a colunm line
}T_Line;

typedef struct {
    T_Point start_point;
    int width;
    int height;
    int color;
    int fill;
}T_Rectangle;

typedef struct {
    T_Point center_point;
    int x_radius;
    int y_radius;
    int color;
    int fill;
}T_Ellipse;

typedef struct {
    T_Point start_point;
    int pos_mid;
    int size;
    int bg_color;
    int fg_color;
    char font[FILENAME_LEN];
    char path[PATHNAME_LEN];
    char content[STRINGS_LEN];
}T_Text;

typedef struct {
    T_Point start_point;
    int width;
    int height;
    int color_enable;
    int color_key;
    char file[FILENAME_LEN];
    char path[PATHNAME_LEN];
}T_Image;



mxml_node_t * ReadScreenInfo (mxml_node_t *tree, mxml_node_t *cur_node, T_Screen *t );
mxml_node_t * ReadNextLineInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Line *t);
mxml_node_t * ReadNextRectangleInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Rectangle *t);
mxml_node_t * ReadNextTextInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Text *t);
mxml_node_t * ReadNextImageInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Image *t);
mxml_node_t * ReadNextEllipseInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Ellipse *t);
#endif   /* ----- #ifndef READSCREENINFO_H_INC  ----- */
