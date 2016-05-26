/*
 * =====================================================================================
 *
 *       Filename:  draw_image.h
 *
 *    Description:  load the images and display them on the screen
 *
 *        Version:  1.0
 *        Created:  12/31/2009 11:29:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  DRAW_IMAGE_H_INC
#define  DRAW_IMAGE_H_INC

#include <assert.h>
#include "SDL.h"
#include "read_screen_info.h"

SDL_Surface *Load_image( char * filename );
void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
int  DrawImage(SDL_Surface * m_screen, T_Image *image_info);
#endif   /* ----- #ifndef DRAW_IMAGE_H_INC  ----- */
