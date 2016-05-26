/*
 * =====================================================================================
 *
 *       Filename:  network_manager.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/5/2010 3:40:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#ifndef  NETWORK_MANAGER_H_INC
#define  NETWORK_MANAGER_H_INC
#ifndef WIN32
#define WIN32 1
#endif

#ifdef WIN32
#include <winsock2.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define closesocket close
#endif


#include	<stdlib.h>
#include	<stdio.h>
#include	<assert.h>
#include	<pthread.h>
#include "SDL.h"
#include "handle_errors.h"

#define  BUFFER_LEN 2048
#define MAX_PACKET_NUM 10

//Worker threads
typedef enum {
    WAITING_STATE = 0,
    TAKENODE_STATE,
    WORKING_STATE,
    PLACENODE_STATE,
    COMPLETED_STATE,
}T_Enum_T_Worker_Active_State;

typedef enum {
    UNKNOWN_WORKER = 0,
    RECEIVER_WORKER,
    DECODEDER_WORKER,
    MIXER_WORKER,
    ENCODER_WORKER,
    SENDER_WORKER,
}T_Enum_Worker_Type;

typedef struct {
    int id;
    T_Enum_Worker_Type type;
    T_Enum_T_Worker_Active_State state;
}T_Worker_Info;

typedef enum {
    UNKNOWN_QUEUE = 0,
    RECEIVE_QUEUE,
    DECODED_QUEUE,
    MIXED_QUEUE,
    ENCODED_QUEUE,
}T_Enum_Queue_Type;

typedef struct {
    T_Enum_Queue_Type type;
    int id;
    int length;
}T_Queue_Info;

typedef struct {
    int client_num;
    int queue_num ;
    int rec_queue_num ;
    int dec_queue_num ;
    int mix_queue_num ;
    int enc_queue_num ;

    int worker_num ;
    int rec_thread_num ;
    int dec_thread_num ;
    int mix_thread_num ;
    int enc_thread_num ;
    int snd_thread_num ;
    void *qs_info;
    void *ws_info;
}T_Monitor_Packet;

typedef struct {
    int id;
    char *pkt;
    struct T_Pkt_Node *next;
}T_Pkt_Node;

typedef struct {
    T_Pkt_Node *header;
    T_Pkt_Node *tail;
    T_Queue_Info q_info;
    pthread_mutex_t mutex;
}T_Pkt_Queue;

typedef struct {
    char *ip_addr;
    char *port;
    T_Pkt_Queue *q;
}T_Sampling_Thread_Param;


typedef struct {
    T_Pkt_Queue *q;
    T_Worker_Info *g_ws;
    T_Queue_Info *g_qs;
}T_Updating_Thread_Param;

int Initialize_system_state_packet_queue(T_Pkt_Queue **qs, int n);
int Check_system_state_packet_queue_limit(T_Pkt_Queue *q );
int Insert_system_state_packet_queue(T_Pkt_Queue *q, T_Pkt_Node *n);
int Remove_system_state_packet_queue(T_Pkt_Queue *q, T_Pkt_Node **n);

int Initialize_system_state_packet_receiver(char *srv_ip_addr, char* srv_port,T_Pkt_Queue *q, T_Worker_Info *g_ws,T_Queue_Info *g_qs);
int Inspect_server_state(char *srv_ip_addr, char* srv_port, T_Monitor_Packet *m_pkt);
void *Sampling_system_state(T_Sampling_Thread_Param *param);
void *Updating_system_state_queue(T_Updating_Thread_Param* param);


#endif   /* ----- #ifndef NETWORK_MANAGER_H_INC  ----- */


