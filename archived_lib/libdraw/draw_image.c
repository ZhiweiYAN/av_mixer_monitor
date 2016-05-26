/*
 * =====================================================================================
 *
 *       Filename:  draw_image.c
 *
 *    Description:  load the images and display them on the screen.
 *
 *        Version:  1.0
 *        Created:  12/31/2009 11:29:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "draw_image.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  DrawImge
 *  Description:  Draw the images and display them on the screen
 * =====================================================================================
 */
int  DrawImage(SDL_Surface * m_screen, T_Image *image_info)
{
//	Check the input parameters
    assert(NULL!=m_screen);
    assert(NULL!=image_info);

//  Open the image file in the specific path
    char *image_path_file_name = NULL;
    int len_image_path_file_name = 0;

    len_image_path_file_name = strlen(image_info->file) + strlen(image_info->path);

    image_path_file_name =(char*)malloc(len_image_path_file_name + 1 );
    assert(NULL!=image_path_file_name);

    memset(image_path_file_name,0, len_image_path_file_name);
    sprintf(image_path_file_name, "%s%s", image_info->path, image_info->file);

//	Display the images
    SDL_Surface *image = NULL;
    image = Load_image( image_path_file_name );

    if ( image != NULL && 1 == image_info->color_enable ) {
        //Map the color key
        SDL_Color m_clrKey;
        m_clrKey.r = (image_info->color_key&0xff0000)>>16;
        m_clrKey.g = (image_info->color_key&0x00ff00)>>8;
        m_clrKey.b = (image_info->color_key&0x0000ff);

        Uint32 colorkey = SDL_MapRGB( image->format,
                                      m_clrKey.r, m_clrKey.g, m_clrKey.b );

        //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey );
    }

    ApplySurface( image_info->start_point.x, image_info->start_point.y, image, m_screen );

    free(image_path_file_name);
    image_path_file_name = NULL;
    return 1;

}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Load_image
 *  Description:  Load images from the specific path and file
 * =====================================================================================
 */
SDL_Surface *Load_image( char * filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = SDL_LoadBMP( filename );

    //If nothing went wrong in loading the image
    if ( loadedImage != NULL ) {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ApplySurface
 *  Description:  Display the .bmp picture on the screen
 * =====================================================================================
 */
void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

