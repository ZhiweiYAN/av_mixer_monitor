/*
 * =====================================================================================
 *
 *       Filename:  queues_ui_manager.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/6/2010 1:05:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  QUEUES_UI_MANAGER_H_INC
#define  QUEUES_UI_MANAGER_H_INC

#include	<stdlib.h>
#include	<stdio.h>
#include	<assert.h>
#include	<pthread.h>

#include	"mxml.h"
#include	"SDL.h"
#include	"SDL_ttf.h"
#include	"SDL_draw.h"

#include	"read_screen_info.h"
#include 	"init_display.h"
#include    "network_manager.h"

typedef struct {
    int queue_num;
    int queue_num_offset;
    T_Queue_Info *qs;
    SDL_Surface *scr;
    SDL_mutex *qs_mutex;
    char cfg_file[STRINGS_LEN];
}T_Draw_Queue_State_Param;


int  Initialize_queues_UI(SDL_Surface *screen, T_Monitor_Packet *pkt, T_Queue_Info *qs,  pthread_t *ui_tid_table,int ui_tid_table_offset);
void *Update_queue_state(T_Draw_Queue_State_Param *param);


#endif   /* ----- #ifndef QUEUES_UI_MANAGER_H_INC  ----- */


