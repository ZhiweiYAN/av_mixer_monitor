#include "display_picture.h"

int DisplayPicture(int picture_x, int picture_y, int width,int height,char *image, SDL_Surface *m_surface, SDL_Surface *m_screen)
{
    if ((NULL == m_screen) ||(NULL== m_surface))
        printf("error @ display_picture.c , the pointer is NULL!\n");
//	LockDisplayArea();
    SDL_LockSurface(m_surface);

    int image_length = 0;
    char *p = NULL;
    p = image;
    image_length = width*height;

    for (int y=0; y<height; y++) {
        for (int x=0; x<width;x++) {
            Uint32 color;

            //convert color
            Uint8 R_color = (Uint8)*(p+2);
            Uint8 G_color = (Uint8)*(p+1);
            Uint8 B_color = (Uint8)*(p+0);
            p += 4;

            color = SDL_MapRGB(m_surface->format,R_color,G_color,B_color);
            char *pData = NULL;

            //grab the frame buffer
            pData = (char*)m_surface->pixels;

            //vetical offset
            pData += (y*m_surface->pitch);

            //horizontal offset
            pData += (x*m_surface->format->BytesPerPixel);

            //copy the pixel color
            memcpy(pData, &color, m_surface->format->BytesPerPixel);

        }
    }
//	UnlockDisplayArea();
    SDL_UnlockSurface(m_surface);

    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = picture_x;
    offset.y = picture_y;

    //Blit the surface
    SDL_BlitSurface( m_surface, NULL, m_screen, &offset );
    SDL_Flip(m_screen);

    return 1;
}


//   create a cursor



