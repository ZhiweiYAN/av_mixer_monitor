/* =====================================================================================
 *
 *       Filename: draw_text.c
 *
 *    Description:  Draw a srting on the computer screen according the parameters from .xml
 *
 *        Version:  1.0
 *        Created:  12/28/2009 9:36:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Haitao Zhang , zhanghaitao5177@gmail.com
 * 					Zhiwei YAN, jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "draw_text.h"

int  Draw_text(SDL_Surface * m_screen, T_Text *text_info, T_Screen *screen_info)
{

//  Open the font file in the specific path
    char *font_path_file_name = NULL;
    int len_font_path_file_name = 0;

    len_font_path_file_name = strlen(text_info->font) + strlen(text_info->path);

    font_path_file_name =(char*)malloc(len_font_path_file_name +1 );
    assert(NULL!=font_path_file_name);

    memset(font_path_file_name,0, len_font_path_file_name);
    sprintf(font_path_file_name, "%s%s", text_info->path, text_info->font);
    if (!TTF_WasInit() && TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }



//  Prepare the background and foreground color of the font
    SDL_Color m_clrFg;
    m_clrFg.r = (text_info->fg_color&0xff0000)>>16;
    m_clrFg.g = (text_info->fg_color&0x00ff00)>>8;
    m_clrFg.b = (text_info->fg_color&0x0000ff);

    SDL_Color m_clrBg;
    m_clrBg.r = (text_info->bg_color&0xff0000)>>16;
    m_clrBg.g = (text_info->bg_color&0x00ff00)>>8;
    m_clrBg.b = (text_info->bg_color&0x0000ff);

// Print the text strings to a SDL surface
    SDL_Surface *s_text = NULL;

//  Check the encode type of character set.
//  if it is ansi or utf8
    TTF_Font *m_fnt = NULL;
    m_fnt = TTF_OpenFont( font_path_file_name, text_info->size);
    assert(NULL!=m_fnt);
    s_text = TTF_RenderText_Shaded( m_fnt, text_info->content, m_clrFg,m_clrBg);
    TTF_CloseFont(m_fnt);
    m_fnt = NULL;
    free(font_path_file_name);
    font_path_file_name = NULL;

//	char ch = *(text_info->content);
//	if (0 == (ch&0x80)){
//    	s_text = TTF_RenderText_Shaded( m_fnt, text_info->content, m_clrFg,m_clrBg);
//	}
//	else{
//    	s_text = TTF_RenderUTF8_Shaded( m_fnt, text_info->content, m_clrFg,m_clrBg);
//
//	}
    assert(NULL!=s_text);

//	Display the text on the screen
    SDL_Rect rcDest;
    rcDest.w = 0;
    rcDest.h = 0;


    rcDest.x = text_info->start_point.x;
    rcDest.y = text_info->start_point.y;

// printf("text_info->pos_mid=%d\n",text_info->pos_mid);

// Display the text in the middle position
    if (1==text_info->pos_mid) {
        rcDest.x = (screen_info->width - s_text->w)/2;
        printf("rcDest.x =%d  rcDest.y =%d\n",rcDest.x,rcDest.y);
    }

    if ( s_text->w > screen_info->width) {
        printf("warnning:the text length is longer than the screen width, please change the word size!\n");
    }

    SDL_BlitSurface( s_text,NULL, m_screen,&rcDest );
    SDL_FreeSurface( s_text );

    return 1;
}


