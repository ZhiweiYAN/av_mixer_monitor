/*
 * =====================================================================================
 *
 *       Filename:  ttps_main.c
 *
 *    Description:  It is a mulit-thread queue server prototype.
 *
 *        Version:  1.0
 *        Created:  4/25/2010 9:37:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<assert.h>
#include	<pthread.h>
#include	"mxml.h"
#include	"SDL.h"
#include	"SDL_ttf.h"
#include	"SDL_draw.h"
#include    "handle_errors.h"
#include	"read_screen_info.h"
#include 	"init_display.h"
#include    "network_manager.h"
#include    "threads_ui_manager.h"
#include    "queues_ui_manager.h"

static int exit_flag = 0;
void * _Do_event(void)
{

    SDL_Event g_Event;
    exit_flag = 0;
    do {

        //adjust the sampling rate
        if (SDL_PollEvent(&g_Event) == 0) {
            SDL_Delay(200);
        }

        if (g_Event.type== SDL_QUIT) {
            exit_flag++;
            break;
        }

        if (g_Event.type==SDL_KEYDOWN && SDLK_ESCAPE == g_Event.key.keysym.sym) {
            exit_flag++;
            break;
        }

    } while (1);

}

int main (int argc, char *argv[] )
{
    int err = 0;
    err = 0;

    FILE * ctt = fopen("CON", "w" );
    if (ctt) {
        freopen("CON", "w", stdout);
        freopen("con", "w", stderr);
    } else {
        fclose( ctt );
    }

    //parse the server IP and Port
    char *srv_ip_addr = NULL;
    char *srv_port = NULL;

    if (3==argc) {
        srv_ip_addr = argv[1];
        srv_port = argv[2];
    } else {
        printf("Usage: %s <IP Address> <Port>\n", argv[0]);
        printf("Usage example: %s 192.168.0.1 8765\n", argv[0]);
		getchar();
        return 0;
    }

    //SDL libary
    SDL_Surface *screen = NULL;
    screen = InitXmlScr(".//cfg_files//cfg.xml");

    SDL_WM_SetIcon(SDL_LoadBMP(".//images//icon.bmp"), NULL);
    //receive a task and put it into the queue.
    //if (atexit(UnInitXmlSrc)!=0) {
    //    OUTPUT_ERROR;
    //}

    pthread_t tid;
    //pthread_create(&tid, NULL, (void*)_Do_event, NULL);

    //Inspect the number of clients who servered by the server
    int client_num = 0;
    T_Monitor_Packet m_pkt;
    client_num = Inspect_server_state(srv_ip_addr, srv_port,(T_Monitor_Packet*) &m_pkt);
    if (0>=m_pkt.client_num) {
        printf("Server does not response the monitor\n");
        return 0;
    }

    DBG("Client Number is: %d\n", client_num);

    //Assign the queue of receiving system state packet
    T_Pkt_Queue *sys_state_pkt_queue = NULL;
    if (1==Initialize_system_state_packet_queue(&sys_state_pkt_queue, client_num)) {
        OUTPUT_OK;
    } else {
        OUTPUT_ERROR;
    };
    assert( NULL!=sys_state_pkt_queue );

    //Assign the states of all the threads which run on the server
    T_Worker_Info *g_ws = NULL;
    g_ws = malloc( m_pkt.worker_num* sizeof(T_Worker_Info) );
    assert( NULL!=g_ws );
    memset(g_ws, 0, m_pkt.worker_num*sizeof(T_Worker_Info));

    //Assign the states of all the queues
    T_Queue_Info *g_qs = NULL;
    g_qs = malloc( m_pkt.queue_num * sizeof(T_Queue_Info) );
    assert( NULL!= g_qs );
    memset(g_qs, 0, m_pkt.queue_num * sizeof(T_Queue_Info) );

    //Run the thread which can receive the system state packet.
    err = Initialize_system_state_packet_receiver(srv_ip_addr, srv_port,
            sys_state_pkt_queue,
            g_ws, g_qs);

    pthread_t *ui_thread_table = NULL;
    ui_thread_table = malloc( 9 * sizeof(pthread_t) );

    //Run the program who displays the thread UI
    err = Initialize_threads_UI(screen, &m_pkt, g_ws, ui_thread_table, 0);

    //Run the program who display the queue UI
    err = Initialize_queues_UI(screen, &m_pkt, g_qs, ui_thread_table, 5);



    SDL_Event g_Event;
    do {

        //adjust the sampling rate
        if (SDL_PollEvent(&g_Event) == 0) {
            SDL_Delay(200);
            SDL_Flip(screen);
        }

        if (g_Event.type== SDL_QUIT) {
            break;
        }

        if (g_Event.type==SDL_KEYDOWN && SDLK_ESCAPE == g_Event.key.keysym.sym) {
            break;
        }

    } while (1);


    printf("==Press any key to end!\n");

    for (int i=0; i<9; i++) {
        err = pthread_cancel(ui_thread_table[i] );
    }
    free(g_qs);
    free(g_ws);
    g_qs = NULL;
    g_ws = NULL;
    return 0;
}				/* ----------  end of function main  ---------- */
