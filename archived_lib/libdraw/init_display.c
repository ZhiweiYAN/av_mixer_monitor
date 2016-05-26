/*
 * =====================================================================================
 *
 *       Filename:  init_display.c
 *
 *    Description:  Initialize the display and all lines, rectangles and so on.
 *
 *        Version:  1.0
 *        Created:  1/1/2010 1:45:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "init_display.h"
void UnInitXmlSrc(void)
{
    TTF_Quit();
    SDL_Quit();
    abort();

}
SDL_Surface * InitXmlScr(char *xml_file)
{
    assert(NULL != xml_file);

    FILE *fp_cfg = NULL;
    fp_cfg = fopen(xml_file,"r");
    assert(NULL != fp_cfg);

    mxml_node_t *tree = NULL;
    mxml_node_t * node = NULL;
    tree = mxmlLoadFile(NULL,fp_cfg, MXML_OPAQUE_CALLBACK);

    fclose(fp_cfg);
    fp_cfg = NULL;

//	Set up Computer display
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    T_Screen scr_info;
    memset(&scr_info, 0, sizeof(T_Screen));

    node = mxmlWalkNext(tree, tree, MXML_DESCEND);
    {
        mxml_node_t * res = NULL;
        res = ReadScreenInfo(tree,node, &scr_info);
        assert(NULL!=res);
        screen = SetupScreenCfg(&scr_info);
        assert(NULL != screen);
    }

//  Add the background color
    SDL_FillRect(screen,NULL,scr_info.bg_color);
    SDL_Flip(screen);
    printf("scr_info.bg_color=%d\n\n\n\n",scr_info.bg_color);

//	Draw  all rectangles defined in .xml file
    T_Rectangle rectangle_info;
    memset(&rectangle_info, 0, sizeof(T_Rectangle));
    node = mxmlWalkNext(tree, tree, MXML_DESCEND);
    do {
        mxml_node_t * res = ReadNextRectangleInfo( tree,node, &rectangle_info);
        if ( NULL==res) {
            break;
        } else {
            DrawRectangle( screen, &rectangle_info,&scr_info);
            SDL_Flip(screen);
        }

//		One step to advance the node.
        node = mxmlWalkNext(res, tree, MXML_NO_DESCEND);
    } while (NULL!=node);


//	Draw  all ellipses defined in .xml file
    T_Ellipse ellipse_info;
    memset(&ellipse_info, 0, sizeof(T_Ellipse));
    node = mxmlWalkNext(tree, tree, MXML_DESCEND);
    do {
        mxml_node_t * res = ReadNextEllipseInfo( tree,node, &ellipse_info);
        if ( NULL==res) {
            break;
        } else {
            DrawEllipse( screen, &ellipse_info, &scr_info);
            SDL_Flip(screen);
        }

//		One step to advance the node.
        node = mxmlWalkNext(res, tree, MXML_NO_DESCEND);
    } while (NULL!=node);

//  Draw all strings defined in .xml file
    T_Text text_info;
    memset(&text_info, 0, sizeof(T_Text));
    node = mxmlWalkNext(tree, tree, MXML_DESCEND);
    do {
        mxml_node_t * res = ReadNextTextInfo( tree, node, &text_info);
        if ( NULL==res) {
            break;
        } else {
            Draw_text(screen, &text_info,&scr_info);
            SDL_Flip(screen);
        }
        node = mxmlWalkNext(res, tree, MXML_NO_DESCEND);
    } while (NULL!=node);

//	Draw all .bmp pictures defined in .xml file
    T_Image image_info;
    memset(&image_info, 0, sizeof(T_Image));
    node =  mxmlWalkNext(tree, tree, MXML_DESCEND);
    do {
        mxml_node_t * res = ReadNextImageInfo( tree, node, &image_info);
        if ( NULL==res) {
            break;
        } else {
            DrawImage(screen, &image_info);
            SDL_Flip(screen);
        }
        node = mxmlWalkNext(res, tree, MXML_NO_DESCEND);
    } while (NULL!=node);


    //	Draw all lines defined in .xml file
    T_Line line_info;
    memset(&line_info,0,sizeof(T_Line));

    node = mxmlWalkNext(tree, tree, MXML_DESCEND);
    do {
        mxml_node_t * res = ReadNextLineInfo( tree,node, &line_info);
        if ( NULL==res) {
            break;
        } else {
            DrawLine(&line_info, screen);
            SDL_Flip(screen);
        }

//		One step to advance the node.
        node = mxmlWalkNext(res, tree, MXML_NO_DESCEND);
    } while (NULL!=node);

    return screen;
}

