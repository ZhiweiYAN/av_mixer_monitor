/*
 * =====================================================================================
 *
 *       Filename:  threads_ui_manager.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/6/2010 11:49:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  THREADS_UI_MANAGER_H_INC
#define  THREADS_UI_MANAGER_H_INC
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

#define		ACTIVE_COLOR  0x008000
#define		NONACTIVE_COLOR  0xE0E8C1
#define		COMPLETED_COLOR 0x66FF00

#define		NO_STDIO_REDIRECT 0
#define		WORKER_THREAD_NUM 11
#define		WORKER_THREAD_STATE_NUM 5


typedef struct {
    SDL_Surface *scr;
    char cfg_file[200];
    int thread_num;
    int thread_num_offset;
    T_Worker_Info *ws;
}T_Draw_Thread_State_Param;

int  Initialize_threads_UI(SDL_Surface *screen, T_Monitor_Packet *pkt, T_Worker_Info *ws, pthread_t *ui_tid_table,int ui_tid_table_offset);
void *Update_thread_state(T_Draw_Thread_State_Param *param);
void Draw_Thread_Txt(T_Draw_Thread_State_Param *param);

#endif   /* ----- #ifndef THREADS_MANAGER_H_INC  ----- */
