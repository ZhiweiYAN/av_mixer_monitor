/*
 * =====================================================================================
 *
 *       Filename:  threads_ui_manager.c
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  11/6/2010 11:48:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "threads_ui_manager.h"


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Update_thread_state
 *  Description:  update the screen
 * =====================================================================================
 */
void Draw_Thread_Txt(T_Draw_Thread_State_Param *param)
{
    assert(NULL!=param);

    char g_ws_strings[WORKER_THREAD_STATE_NUM][3]={"W0","T1","W2","P3","E4"};

    T_Draw_Thread_State_Param *p = NULL;
    p = (T_Draw_Thread_State_Param*)param;

    SDL_Surface *screen = NULL;
    screen = (SDL_Surface *)(p->scr);

    T_Worker_Info *g_ws = NULL;
    g_ws = p->ws;


    //reading the worker thread UI configuration from tsg.xml
    FILE *fp_cfg = NULL;
    //fp_cfg = fopen(".//cfg_files/tsg.xml","r");
    fp_cfg = fopen(p->cfg_file, "r");
    assert(NULL!=fp_cfg);

    int thread_num = 0;
    thread_num = p->thread_num;

    //saving the all ui circles information on the screen
    T_Rectangle *wtsg = NULL;
    wtsg = malloc( thread_num * WORKER_THREAD_STATE_NUM *sizeof(T_Rectangle));
    assert(NULL!=wtsg);

    mxml_node_t *tree = NULL;
    tree = mxmlLoadFile(NULL, fp_cfg, MXML_OPAQUE_CALLBACK);
    fclose(fp_cfg);
    fp_cfg = NULL;

    //reading the left upper node and right bottom node

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;

    T_Rectangle lu_node;
    T_Rectangle rb_node;
    memset(&lu_node, 0, sizeof(T_Rectangle) );
    memset(&rb_node, 0, sizeof(T_Rectangle) );
    node = mxmlWalkNext(tree,tree,MXML_DESCEND);
    res = ReadNextRectangleInfo(tree,node,&lu_node);
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadNextRectangleInfo(tree,node,&rb_node);

    T_Screen scr_info;
    memset(&scr_info, 0, sizeof(T_Screen) );
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadScreenInfo(tree,node,&scr_info);

    T_Text wstg_text_info;
    memset(&wstg_text_info, 0, sizeof(T_Text) );
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadNextTextInfo(tree,node,&wstg_text_info);

    int vertical_span = 0;
    int horizon_span = 0;

    if (1<thread_num) {
        vertical_span = (rb_node.start_point.y - lu_node.start_point.y)
                        / (thread_num -1);
    } else {
        vertical_span = 0;
    }
    horizon_span = (rb_node.start_point.x - lu_node.start_point.x)
                   / (WORKER_THREAD_STATE_NUM -1);

    //print the thread index number on the left of retangle matrix
    for (int i=0;i<thread_num;i++) {
        memset(wstg_text_info.content, 0, STRINGS_LEN);
        sprintf(wstg_text_info.content, "%d", i);
        wstg_text_info.start_point.x = lu_node.start_point.x - 30;
        wstg_text_info.start_point.y = lu_node.start_point.y + i * vertical_span - 5;

        Draw_text(screen, &wstg_text_info,&scr_info);
    }

    //print the state abbreviation on the top of retangle matrix
    for (int i=0;i<WORKER_THREAD_STATE_NUM;i++) {
        memset(wstg_text_info.content, 0, 10);
        sprintf(wstg_text_info.content, "%s", g_ws_strings[i]);
        wstg_text_info.start_point.x = lu_node.start_point.x  + i * horizon_span;
        wstg_text_info.start_point.y = lu_node.start_point.y - 20;

        Draw_text(screen, &wstg_text_info,&scr_info);
    }

    //filling the configuration into the wtsg
    for (int i=0; i<thread_num; i++)
        for (int j=0; j<WORKER_THREAD_STATE_NUM; j++) {
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x = lu_node.start_point.x + j * horizon_span;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y = lu_node.start_point.y + i * vertical_span;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width = lu_node.width;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height = lu_node.height;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color = lu_node.color;

            //drawing the grid
            Draw_FillRect(screen,(wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x-1, (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y-1,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width+2, (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height+2, 0x000000);

            Draw_FillRect(screen,(wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x, (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width, (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height, (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color);

        }
    return ;
}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Update_thread_state
 *  Description:  update the screen
 * =====================================================================================
 */
void * Update_thread_state(T_Draw_Thread_State_Param *param)
{
    assert(NULL!=param);

    T_Draw_Thread_State_Param p;
    memcpy(&p, param, sizeof(T_Draw_Thread_State_Param) );

    pthread_detach(pthread_self());

    free(param);
    param = NULL;

    SDL_Surface *screen = NULL;
    screen = (SDL_Surface *)(p.scr);

    T_Worker_Info *g_ws = NULL;
    g_ws = p.ws;


    //reading the worker thread UI configuration from tsg.xml
    FILE *fp_cfg = NULL;
    fp_cfg = fopen(p.cfg_file, "r");
    if (NULL==fp_cfg) {
        fprintf(stderr, "filename:%s\n", p.cfg_file);
        fflush(NULL);
    }
    assert(NULL!=fp_cfg);

    int thread_num = 0;
    thread_num = p.thread_num;

    //saving the all ui circles information on the screen
    T_Rectangle *wtsg = NULL;
    wtsg = malloc( thread_num * WORKER_THREAD_STATE_NUM *sizeof(T_Rectangle));
    assert(NULL!=wtsg);

    int thread_num_offset = p.thread_num_offset;


    mxml_node_t *tree = NULL;
    tree = mxmlLoadFile(NULL, fp_cfg, MXML_OPAQUE_CALLBACK);
    fclose(fp_cfg);
    fp_cfg = NULL;

    //reading the left upper node and right bottom node

    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;

    T_Rectangle lu_node;
    T_Rectangle rb_node;
    memset(&lu_node, 0, sizeof(T_Rectangle) );
    memset(&rb_node, 0, sizeof(T_Rectangle) );
    node = mxmlWalkNext(tree,tree,MXML_DESCEND);
    res = ReadNextRectangleInfo(tree,node,&lu_node);
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadNextRectangleInfo(tree,node,&rb_node);

    T_Screen scr_info;
    memset(&scr_info, 0, sizeof(T_Screen) );
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadScreenInfo(tree,node,&scr_info);

    T_Text wstg_text_info;
    memset(&wstg_text_info, 0, sizeof(T_Text) );
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadNextTextInfo(tree,node,&wstg_text_info);

    int vertical_span = 0;
    int horizon_span = 0;

    if (1<thread_num) {
        vertical_span = (rb_node.start_point.y - lu_node.start_point.y)
                        / (thread_num -1);
    } else {
        vertical_span = 0;
    }
    horizon_span = (rb_node.start_point.x - lu_node.start_point.x)
                   / (WORKER_THREAD_STATE_NUM -1);

    //filling the configuration into the wtsg
    for (int i=0; i<thread_num; i++)
        for (int j=0; j<WORKER_THREAD_STATE_NUM; j++) {
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x = lu_node.start_point.x + j * horizon_span;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y = lu_node.start_point.y + i * vertical_span;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width = lu_node.width;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height = lu_node.height;
            (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color = lu_node.color;

            //drawing the grid
            Draw_FillRect(screen,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x-1,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y-1,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width+2,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height+2,
                          0x000000);

            Draw_FillRect(screen,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height,
                          (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color);

        }

    T_Worker_Info *p_t = NULL;

    //updating the workers' states in a fixed interval
    do {
        //
        for (int i=0; i<thread_num; i++) {
            for (int j=0; j<WORKER_THREAD_STATE_NUM; j++) {
                (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color = NONACTIVE_COLOR;
            }
        }

        for (int i=0; i<thread_num ; i++) {
            p_t = g_ws+thread_num_offset +i;
            (wtsg+i*WORKER_THREAD_STATE_NUM+(p_t->state))->color = ACTIVE_COLOR;
        }
        //filling the color on the screen for worker thread states
        for (int i=0; i<thread_num; i++)
            for (int j=0; j<WORKER_THREAD_STATE_NUM; j++) {
                Draw_FillRect(screen,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color);

            }
        SDL_Flip(screen);

        SDL_Delay(300);
        //taking data from the wst and setting UI color
        for (int i=0; i<thread_num ; i++) {
            p_t = g_ws+thread_num_offset +i;
            (wtsg+i*WORKER_THREAD_STATE_NUM+(p_t->state))->color = COMPLETED_COLOR;
        }
        //filling the color on the screen for worker thread states
        for (int i=0; i<thread_num; i++)
            for (int j=0; j<WORKER_THREAD_STATE_NUM; j++) {
                Draw_FillRect(screen,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.x,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->start_point.y,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->width,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->height,
                              (wtsg+i*WORKER_THREAD_STATE_NUM+j)->color);

            }
        SDL_Flip(screen);


        //postponing the time interval
        SDL_Delay(400);

    } while (1);

    return NULL;
}



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Initialize_threads_UI
 *  Description:
 * =====================================================================================
 */
int  Initialize_threads_UI(SDL_Surface *screen, T_Monitor_Packet *pkt, T_Worker_Info *ws, pthread_t *ui_tid_table, int ui_tid_table_offset)
{
    assert(NULL!=screen);
    assert(NULL!=pkt);
    assert(NULL!=ws);

    int client_num = 0;
    client_num = pkt->client_num;
    T_Draw_Thread_State_Param *param = NULL;

    //UI for recv threads
    param = malloc( sizeof(T_Draw_Thread_State_Param) );
    memset(param, 0, sizeof(T_Draw_Thread_State_Param) );

    strcpy(param->cfg_file, ".//cfg_files//tsg4rec.xml" );
    param->scr = screen;
    param->thread_num = pkt->rec_thread_num;
    param->thread_num_offset = 0;
    param->ws = ws;
    Draw_Thread_Txt(param);
    pthread_create(ui_tid_table+ui_tid_table_offset, NULL, (void*)Update_thread_state, (void*)param);


    //UI for decoder threads
    param = malloc( sizeof(T_Draw_Thread_State_Param) );
    memset(param, 0, sizeof(T_Draw_Thread_State_Param) );

    strcpy(param->cfg_file, ".//cfg_files//tsg4dec.xml");
    param->scr = screen;
    param->thread_num = pkt->dec_thread_num;
    param->thread_num_offset = pkt->rec_thread_num;
    param->ws = ws;
    Draw_Thread_Txt(param);
    pthread_create((ui_tid_table+ui_tid_table_offset+1), NULL,(void*)Update_thread_state, (void*)param);

    //UI for mixer threads
    param = malloc( sizeof(T_Draw_Thread_State_Param) );
    memset(param, 0, sizeof(T_Draw_Thread_State_Param) );
    strcpy(param->cfg_file,".//cfg_files//tsg4mix.xml");

    param->scr = screen;
    param->thread_num = pkt->mix_thread_num;
    param->thread_num_offset = pkt->rec_thread_num+ pkt->dec_thread_num  ;
    param->ws = ws;
    Draw_Thread_Txt(param);
    pthread_create((ui_tid_table+ui_tid_table_offset+2), NULL,(void*)Update_thread_state, (void*)param);

    //UI for encoder threads
    param = malloc( sizeof(T_Draw_Thread_State_Param) );
    memset(param, 0, sizeof(T_Draw_Thread_State_Param) );
    strcpy(param->cfg_file,".//cfg_files//tsg4enc.xml" );

    param->scr = screen;
    param->thread_num = pkt->enc_thread_num;
    param->thread_num_offset = pkt->rec_thread_num+ pkt->dec_thread_num + pkt->mix_thread_num ;
    param->ws = ws;
    Draw_Thread_Txt(param);
    pthread_create((ui_tid_table+ui_tid_table_offset+3), NULL,(void*)Update_thread_state, (void*)param);

    //UI for sender threads
    param = malloc( sizeof(T_Draw_Thread_State_Param) );
    memset(param, 0, sizeof(T_Draw_Thread_State_Param) );

    strcpy(param->cfg_file, ".//cfg_files//tsg4sen.xml" );
    param->scr = screen;
    param->thread_num = pkt->snd_thread_num;
    param->thread_num_offset = pkt->rec_thread_num+ pkt->dec_thread_num
                               + pkt->mix_thread_num + pkt->enc_thread_num;
    param->ws = ws;
    Draw_Thread_Txt(param);
    pthread_create((ui_tid_table+ui_tid_table_offset+4), NULL,(void*)Update_thread_state, (void*)param );

    return 1;
}


