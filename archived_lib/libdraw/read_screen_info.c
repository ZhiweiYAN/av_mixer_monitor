/*
 * =====================================================================================
 *
 *       Filename:  read_screen_info.c
 *
 *    Description:  Read the elements on the computer screen from .xml
 *
 *        Version:  1.0
 *        Created:  12/24/2009 9:13:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#include "read_screen_info.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ReadScreenInfo
 *  Description:  Read the config information of screen such as screen width or height
 * =====================================================================================
 */

mxml_node_t *ReadScreenInfo (mxml_node_t *tree, mxml_node_t *cur_node, T_Screen *t )
{
    if ( NULL== tree||NULL== cur_node|| NULL== t) {
        return NULL;
    }

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    char *pEnd;

    /* Read the information of the line */
    node = mxmlFindElement(cur_node,tree,"screen", NULL,NULL, MXML_DESCEND);

    if ( NULL == node) {
        return NULL;
    }

    res = mxmlFindElement(node,tree,"width", NULL,NULL, MXML_DESCEND);
    t->width = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"height", NULL,NULL, MXML_DESCEND);
    t->height = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"bgcolor", NULL,NULL, MXML_DESCEND);
    t->bg_color = (int) strtol(res->child->value.opaque, &pEnd,16);

    res = mxmlFindElement(node,tree,"bpp", NULL,NULL, MXML_DESCEND);
    t->bpp = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"fullscr", NULL,NULL, MXML_DESCEND);
    t->full_scr = (int) strtol(res->child->value.opaque, &pEnd,10);


    printf ( "%-10s: %s|%d|, %s|%d|, %s|%d|, %s|0x%X|, %s|%d|\n",
             "Screen",
             "width=",t->width,
             "height=", t->height,
             "bpp=",t->bpp,
             "color=",t->bg_color,
             "fullscr=", t->full_scr);
    return node;
}		/* -----  end of function ReadScreenInfo  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ReadNextLineInfo
 *  Description:  Read next line infomation from xml file
 * =====================================================================================
 */
mxml_node_t * ReadNextLineInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Line *t)
{
    if ( NULL== tree||NULL== cur_node|| NULL== t) {
        return NULL;
    }

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    char *pEnd;

    /* Read the information of the line */
    node = mxmlFindElement(cur_node,tree,"line", NULL,NULL, MXML_DESCEND);

    if ( NULL == node) {
        return NULL;
    }

    res = mxmlFindElement(node,tree,"x", NULL,NULL, MXML_DESCEND);
    t->start_point.x = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"y", NULL,NULL, MXML_DESCEND);
    t->start_point.y = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"length", NULL,NULL, MXML_DESCEND);
    t->length = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"width", NULL,NULL, MXML_DESCEND);
    t->width = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"color", NULL,NULL, MXML_DESCEND);
    t->color = (int) strtol(res->child->value.opaque, &pEnd,16);

    res = mxmlFindElement(node,tree,"line_type", NULL,NULL, MXML_DESCEND);
    t->line_type = (int) strtol(res->child->value.opaque, &pEnd,16);

    printf ( "%-10s: %s|%d|, %s|%d|, %s|%d|, %s|%d|,  %s|%d|, %s|0x%X|\n",
             "Line",
             "x=",t->start_point.x,
             "y=", t->start_point.y,
             "length=",t->length,
             "width=",t->width,
             "line_type=",t->line_type,
             "color=",t->color);
    return node;
}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ReadNextRectangleInfo
 *  Description:  Read a Rectangle infomation from xml file
 * =====================================================================================
 */
mxml_node_t * ReadNextRectangleInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Rectangle *t)
{
    if ( NULL== tree||NULL== cur_node|| NULL== t) {
        return NULL;
    }

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    char *pEnd;

    /* Read the information of the rectangle */
    node = mxmlFindElement(cur_node,tree,"rectangle", NULL,NULL, MXML_DESCEND);

    if ( NULL == node) {
        return NULL;
    }


    res = mxmlFindElement(node,tree,"x", NULL,NULL, MXML_DESCEND);
    t->start_point.x = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"y", NULL,NULL, MXML_DESCEND);
    t->start_point.y = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"height", NULL,NULL, MXML_DESCEND);
    t->height = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"width", NULL,NULL, MXML_DESCEND);
    t->width = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"color", NULL,NULL, MXML_DESCEND);
    t->color = (int) strtol(res->child->value.opaque, &pEnd,16);

    res = mxmlFindElement(node,tree,"fill", NULL,NULL, MXML_DESCEND);
    t->fill = (int) strtol(res->child->value.opaque, &pEnd,16);
    printf ( "%-10s: %s|%d|, %s|%d|, %s|%d|, %s|%d|, %s|0x%X|, %s|%d|\n",
             "Rectangle",
             "x=",t->start_point.x,
             "y=", t->start_point.y,
             "height=",t->height,
             "width=",t->width,
             "color=",t->color,
             "fill=",t->fill);
    return node;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ReadNextEllipseInfo
 *  Description:  read the next ellipse information
 * =====================================================================================
 */
mxml_node_t * ReadNextEllipseInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Ellipse *t)
{
    if ( NULL== tree||NULL== cur_node|| NULL== t) {
        return NULL;
    }

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    char *pEnd;

    /* Read the information of the rectangle */
    node = mxmlFindElement(cur_node,tree,"ellipse", NULL,NULL, MXML_DESCEND);

    if ( NULL == node) {
        return NULL;
    }


    res = mxmlFindElement(node,tree,"x", NULL,NULL, MXML_DESCEND);
    t->center_point.x = (int) strtol(res->child->value.opaque, &pEnd,10);
    res = mxmlFindElement(node,tree,"y", NULL,NULL, MXML_DESCEND);
    t->center_point.y = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"xradius", NULL,NULL, MXML_DESCEND);
    t->x_radius = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"yradius", NULL,NULL, MXML_DESCEND);
    t->y_radius = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"color", NULL,NULL, MXML_DESCEND);
    t->color = (int) strtol(res->child->value.opaque, &pEnd,16);

    res = mxmlFindElement(node,tree,"fill", NULL,NULL, MXML_DESCEND);
    t->fill = (int) strtol(res->child->value.opaque, &pEnd,16);

    printf ( "%-10s: %s|%d|, %s|%d|, %s|%d|, %s|%d|, %s|0x%X|, %s|%d|\n",
             "Rectangle",
             "x=",t->center_point.x,
             "y=", t->center_point.y,
             "height=",t->x_radius,
             "width=",t->y_radius,
             "color=",t->color,
             "fill=",t->fill);
    return node;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ReadNextTextInfo
 *  Description:  Read a text infomation from xml file
 * =====================================================================================
 */
mxml_node_t * ReadNextTextInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Text *t)
{
    if ( NULL== tree||NULL== cur_node|| NULL== t) {
        return NULL;
    }

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    char *pEnd;
    int len;

    /* Read the information of the rectangle */
    node = mxmlFindElement(cur_node,tree,"text", NULL,NULL, MXML_DESCEND);

    if ( NULL == node) {
        return NULL;
    }


    res = mxmlFindElement(node,tree,"x", NULL,NULL, MXML_DESCEND);
    t->start_point.x = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"y", NULL,NULL, MXML_DESCEND);
    t->start_point.y = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"size", NULL,NULL, MXML_DESCEND);
    t->size = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"fgcolor", NULL,NULL, MXML_DESCEND);
    t->fg_color = (int) strtol(res->child->value.opaque, &pEnd,16);

    res = mxmlFindElement(node,tree,"bgcolor", NULL,NULL, MXML_DESCEND);
    t->bg_color = (int) strtol(res->child->value.opaque, &pEnd,16);

    res = mxmlFindElement(node,tree,"font", NULL,NULL, MXML_DESCEND);
    len = strlen(res->child->value.opaque);
    strcpy(t->font,res->child->value.opaque);

    res = mxmlFindElement(node,tree,"path", NULL,NULL, MXML_DESCEND);
    len = strlen(res->child->value.opaque);
    strcpy(t->path,res->child->value.opaque);

    res = mxmlFindElement(node,tree,"content", NULL,NULL, MXML_DESCEND);
    len = strlen(res->child->value.opaque);
    strcpy(t->content,res->child->value.opaque);

    res = mxmlFindElement(node,tree,"pos_mid", NULL,NULL, MXML_DESCEND);
    t->pos_mid = (int) strtol(res->child->value.opaque, &pEnd,10);

    printf ( "%-10s: %s|%d|, %s|%d|, %s|%d|, %s|0x%X|, %s|0x%X|, %s|%s|, %s|%s|, %s|%s|,%s|%d|\n",
             "Text",
             "x=",t->start_point.x,
             "y=", t->start_point.y,
             "size=",t->size,
             "fgcolor=",t->fg_color,
             "bgcolor=",t->bg_color,
             "font=",t->font,
             "path=",t->path,
             "content=",t->content,
             "pos_mid=",t->pos_mid);
    return node;
}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ReadImageInfo
 *  Description:  Read the image information from .xml files
 * =====================================================================================
 */
mxml_node_t * ReadNextImageInfo( mxml_node_t *tree, mxml_node_t *cur_node, T_Image *t)
{
    if ( NULL== tree||NULL== cur_node|| NULL== t) {
        return NULL;
    }

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    char *pEnd;

    /* Read the information of the line */
    node = mxmlFindElement(cur_node,tree,"image", NULL,NULL, MXML_DESCEND);

    if ( NULL == node) {
        return NULL;
    }

    res = mxmlFindElement(node,tree,"x", NULL,NULL, MXML_DESCEND);
    t->start_point.x = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"y", NULL,NULL, MXML_DESCEND);
    t->start_point.y = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"width", NULL,NULL, MXML_DESCEND);
    t->width = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"height", NULL,NULL, MXML_DESCEND);
    t->height = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"file", NULL,NULL, MXML_DESCEND);
    strcpy(t->file,res->child->value.opaque);

    res = mxmlFindElement(node,tree,"path", NULL,NULL, MXML_DESCEND);
    strcpy(t->path,res->child->value.opaque);

    res = mxmlFindElement(node,tree,"color_key", NULL,NULL, MXML_DESCEND);
    t->color_key = (int) strtol(res->child->value.opaque, &pEnd,10);

    res = mxmlFindElement(node,tree,"color_enable", NULL,NULL, MXML_DESCEND);
    t->color_enable = (int) strtol(res->child->value.opaque, &pEnd,10);

    printf ( "%-10s: %s|%d|, %s|%d|, %s|%d|, %s|%d|,%s|%s|, %s|%s|, %s|%d|, %s|0x%X|\n",
             "Image",
             "x=",t->start_point.x,
             "y=", t->start_point.y,
             "width=",t->width,
             "height=",t->height,
             "file=",t->file,
             "path=",t->path,
             "colorenable=",t->color_enable,
             "colorkey=",t->color_key);

    return node;
}
