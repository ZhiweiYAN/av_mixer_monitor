/*
 * =====================================================================================
 *
 *       Filename:  network_manager.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/6/2010 11:25:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "network_manager.h"

int Inspect_server_state(char *srv_ip_addr, char* srv_port, T_Monitor_Packet *m_pkt)
{
    struct sockaddr_in addr;
    int addr_len = 0;
    int sd = 0;
    char buff[BUFFER_LEN];
    memset(buff, 0, BUFFER_LEN);
    int size = 0;

    //For microsoft windows OS
    char *ip_addr = NULL;
    ip_addr = srv_ip_addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(srv_port));
    addr.sin_addr.s_addr = inet_addr(ip_addr);

    //create socket

    do {
#ifdef WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

        sd = socket(AF_INET, SOCK_DGRAM, 0);
        assert(sd>0);

        addr_len = sizeof(struct sockaddr_in);
        size = sendto(sd, "Monitor", 7, 0, (struct sockaddr *) &addr, addr_len);
        memset(buff, 0, sizeof(BUFFER_LEN));
        size = recvfrom(sd, buff, BUFFER_LEN, 0, (struct sockaddr *) &addr, &addr_len);
        closesocket(sd);
#ifdef WIN32
        WSACleanup();
#endif

        if (-1==size)
            return -1;
    } while (0>=size);

    memcpy(m_pkt, buff, sizeof(T_Monitor_Packet) );

    return 1;
}

int Initialize_system_state_packet_receiver(char *srv_ip_addr, char* srv_port,
        T_Pkt_Queue *q,
        T_Worker_Info *g_ws,
        T_Queue_Info *g_qs)
{

    int err = 0;
    assert( NULL!=srv_ip_addr );
    assert( NULL!=srv_port );
    assert( NULL!=q );

    T_Sampling_Thread_Param *param = NULL;
    param = malloc( sizeof(T_Sampling_Thread_Param) );
    assert( NULL!=param );
    memset(param, 0, sizeof(T_Sampling_Thread_Param) );

    param->ip_addr = srv_ip_addr;
    param->port = srv_port;
    param->q = q;
    pthread_t st_tid;
    err = pthread_create(&st_tid, NULL, (void *)Sampling_system_state, (void *)param);


    T_Updating_Thread_Param *ut_param = NULL;
    ut_param = malloc( sizeof(T_Updating_Thread_Param) );
    assert( NULL!=ut_param );
    memset(ut_param, 0, sizeof(T_Updating_Thread_Param) );

    ut_param->q = q;
    ut_param->g_ws = g_ws;
    ut_param->g_qs = g_qs;
    pthread_t ut_tid;
    err = pthread_create(&ut_tid, NULL, (void *)Updating_system_state_queue, (void *)ut_param);
    return 1;
}
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Sampling_system_state()
 *  Description:
 * =====================================================================================
 */
void *Sampling_system_state(T_Sampling_Thread_Param *param)
{

    int err = 0;

    assert(NULL!=param);

    T_Sampling_Thread_Param *param_bak;
    param_bak = malloc( sizeof(T_Sampling_Thread_Param) );
    assert(NULL!=param_bak);
    memcpy(param_bak, param, sizeof(T_Sampling_Thread_Param) );

    pthread_detach(pthread_self());
    free(param);
    param = NULL;

    struct sockaddr_in addr;
    int addr_len = 0;
    int sd = 0;
    char buff[BUFFER_LEN];
    memset(buff, 0, BUFFER_LEN);
    int size = 0;
    char *pkt = NULL;

    //For microsoft windows OS
#ifdef WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(param_bak->port));
    addr.sin_addr.s_addr = inet_addr(param_bak->ip_addr);

    T_Pkt_Queue *q = NULL;
    q = param_bak->q;

//    free(param_bak);
//    param_bak = NULL;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sd>0);


    while (1) {

        //recv the sampling packet from the network
        //create socket

        addr_len = sizeof(struct sockaddr_in);
        size = sendto(sd, "Monitor", 7, 0, (struct sockaddr *) &addr, addr_len);
        memset(buff, 0, sizeof(BUFFER_LEN));
        size = recvfrom(sd, buff, BUFFER_LEN, 0, (struct sockaddr *) &addr, &addr_len);
        if (size<=0) {
            SDL_Delay(500);
            continue;
        }

		fprintf(stderr, "Recv String:|%s|\n", buff);
		
        //allocate memory for the sampling pkt
        pkt = malloc(size);
        assert(NULL!=pkt);
        memset(pkt, 0, size);
        memcpy(pkt, buff, size);

        //put a pkt into the queue.
        T_Pkt_Node *t = malloc(sizeof(T_Pkt_Node));
        assert(NULL!=t);
        memset(t, 0, sizeof(T_Pkt_Node));
        t->pkt = pkt;

        err = Insert_system_state_packet_queue(q,t);
        SDL_Delay(500);

    }
    closesocket(sd);

#ifdef WIN32
    WSACleanup();
#endif

}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  _worker_t
 *  Description:  the worker thread fetch a task from the task link queue
 * =====================================================================================
 */
void* Updating_system_state_queue(T_Updating_Thread_Param* param)
{

    int err = 0;

    assert(NULL!=param);

    T_Updating_Thread_Param *param_bak;
    param_bak = malloc( sizeof(T_Updating_Thread_Param) );
    assert(NULL!=param_bak);
    memcpy(param_bak, param, sizeof(T_Updating_Thread_Param) );

    pthread_detach(pthread_self());
    free(param);
    param = NULL;


    T_Pkt_Queue *q = NULL;
    q = param_bak->q;
    T_Worker_Info *g_ws = NULL;
    T_Queue_Info *g_qs = NULL;
    g_ws = param_bak->g_ws;
    g_qs = param_bak->g_qs;

    T_Pkt_Node *n = NULL;
    T_Queue_Info *p_qs = NULL;
    T_Worker_Info *p_ws = NULL;

    int srv_problem = 30;

    while (1) {

        n = NULL;
        err = Remove_system_state_packet_queue(q, &n);
        if (NULL==n) {
            SDL_Delay(1000);
            srv_problem --;

            if (0>srv_problem) {
                printf("Server, NO RESPONSE.\n");
            }

            continue;
        }

        srv_problem = 30;

        T_Monitor_Packet *p = NULL;
        p = (T_Monitor_Packet *)(n->pkt);
        int client_num = 0;
        int queue_num = 0;
        int thread_num = 0;
        client_num = p->client_num;
        queue_num = p->queue_num;
        thread_num = p->worker_num;

        void *tmp_p = NULL;
        tmp_p = (void *)p;

        p_qs = (T_Queue_Info *) (tmp_p+ sizeof(T_Monitor_Packet));
        p_ws = (T_Worker_Info *) (tmp_p+ sizeof(T_Monitor_Packet) + queue_num *sizeof(T_Queue_Info));


        memset(g_qs, 0, queue_num*sizeof(T_Queue_Info));

        for (int i = 0;i<queue_num;i++) {
            (g_qs+i)->type = (p_qs+i)->type;
            (g_qs+i)->length = (p_qs+i)->length;
        }


        memset(g_ws, 0, thread_num *sizeof(T_Worker_Info));


        for (int i=0; i<thread_num; i++) {
            (g_ws+i)->type = (p_ws+i)->type;
            (g_ws+i)->state = (p_ws+i)->state;
        }

        //after the task is finished, reset the thread states.
        //wating for the next task incoming.

        free(n->pkt);
        n->pkt = NULL;
        free(n);
        n = NULL;


    }
    while (1);
    return NULL;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Initialize_system_state_packet_queue
 *  Description:
 * =====================================================================================
 */
int Initialize_system_state_packet_queue(T_Pkt_Queue **qs, int n)
{
    assert(NULL!=qs);
    assert(n>=1);

    int err = 0;

    if (NULL!=*qs || n<1) {
        OUTPUT_ERROR;
        return -1;
    }
    *qs = (T_Pkt_Queue* )malloc(sizeof(T_Pkt_Queue));
    assert(NULL!=*qs);
    if (NULL==*qs) {
        OUTPUT_ERROR;
        return -1;
    }
    memset(*qs,0, sizeof(T_Pkt_Queue));

    err = pthread_mutex_init ( &((*qs)->mutex), NULL );

    (*qs)->q_info.id = 0;
    (*qs)->q_info.type = UNKNOWN_QUEUE;

    return 1;

}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Check_system_state_packet_queue
 *  Description:
 * =====================================================================================
 */
int Check_system_state_packet_queue_limit(T_Pkt_Queue *q )
{
    int len = 0;
    int err = 0;
    assert( NULL!= q );

    if (NULL==q) {
        OUTPUT_ERROR;
        return 0;
    }
    err = pthread_mutex_lock(&(q->mutex));
    len = (q->q_info).length;
    err = pthread_mutex_unlock(&(q->mutex));

    if (MAX_PACKET_NUM <= len) {
        DBG("%s:%d\n","The queue of AV packets reaches the length limit",len);
        return -1;
    } else {
        return 1;
    }
}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Insert_system_state_packet_queue
 *  Description:
 * =====================================================================================
 */
int Insert_system_state_packet_queue(T_Pkt_Queue *q, T_Pkt_Node *n)
{
    assert(NULL!=q);
    assert(NULL!=n);

    int err = 0;
    if (NULL==q) {
        OUTPUT_ERROR;
        return 0;
    }

    err = pthread_mutex_lock(&(q->mutex));

    //if the queue is empty, or else ...
    if (NULL == q->header) {

        q->header = n;
        q->tail = n;
        (q->q_info.length) ++;

    } else {

        n->next = NULL;
        q->tail->next = (struct T_Pkt_Node *)n;
        q->tail = n;
        (q->q_info.length) ++;

    }

    DBG("After INSERT, there are %d nodes in T_Monitor_Queue (ID=%d).\n",
        q->q_info.length,q->q_info.id);
    err = pthread_mutex_unlock(&(q->mutex));

    usleep(1);

    return 1;

}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Remove_system_state_packet_queue
 *  Description:
 * =====================================================================================
 */
int Remove_system_state_packet_queue(T_Pkt_Queue *q, T_Pkt_Node **n)
{
    assert(NULL!=q);
    assert(NULL!=n);

    int err = 0;

    if (NULL==q) {
        OUTPUT_ERROR;
        return 0;
    }

    err = pthread_mutex_lock(&(q->mutex));

    //if recv node queue is empty, or else...
    if (NULL == q->header) {
        pthread_mutex_unlock(&(q->mutex));
        //OUTPUT_ERROR;
        return -1;
    } else {

        //fetch a node from the queue
        *n = q->header;

        (q->q_info.length) --;

        if (q->tail  == q->header) {

            q->header = NULL;
            q->tail = NULL;
        } else {
            q->header = (T_Pkt_Node *)(q->header->next);
        }
    }
    DBG("After REMOVE, there are %d nodes in T_Monitor_Queue (ID=%d).\n",
        q->q_info.length,q->q_info.id);
    err = pthread_mutex_unlock(&(q->mutex));
    usleep(1);
    return 1;

}

