/*
 * =====================================================================================
 *
 *       Filename:  queues_ui_manager.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/6/2010 1:05:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#include "queues_ui_manager.h"

void *Update_queue_state(T_Draw_Queue_State_Param *param)
{
    assert( NULL!=param );

    T_Draw_Queue_State_Param *p = NULL;
    p = malloc( sizeof(T_Draw_Queue_State_Param) );
    memcpy(p, param, sizeof(T_Draw_Queue_State_Param) );

    pthread_detach(pthread_self());
    free(param);
    param = NULL;

    //saving the all ui circles information on the screen
    T_Text *qtsg = NULL;
    qtsg = malloc( p->queue_num *sizeof(T_Text));
    assert(NULL!=qtsg);

    FILE *fp_cfg = NULL;
    mxml_node_t *node = NULL;
    mxml_node_t *res = NULL;
    mxml_node_t *tree = NULL;

    fp_cfg = fopen(p->cfg_file, "r");
    assert(NULL!=fp_cfg);

    tree = mxmlLoadFile(NULL, fp_cfg, MXML_OPAQUE_CALLBACK);
    fclose(fp_cfg);
    fp_cfg = NULL;

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

    T_Text qstg_text_info;
    memset(&qstg_text_info, 0, sizeof(T_Text) );
    node = mxmlWalkNext(res,tree,MXML_NO_DESCEND);
    res = ReadNextTextInfo(tree,node,&qstg_text_info);

    int vertical_span = 0;
    int horizon_span = 0;

    if (1<p->queue_num) {
        vertical_span = (rb_node.start_point.y - lu_node.start_point.y)
                        / (p->queue_num-1);
    } else {
        vertical_span = 0;
    }
    horizon_span = (rb_node.start_point.x - lu_node.start_point.x)
                   / (6);

    //print the thread index number on the left of retangle matrix
    for (int i=0;i<p->queue_num;i++) {
        memset(qstg_text_info.content, 0, STRINGS_LEN);
        sprintf(qstg_text_info.content, "%d", 0);
        qstg_text_info.start_point.x = lu_node.start_point.x + horizon_span;
        qstg_text_info.start_point.y = lu_node.start_point.y + i * vertical_span - 12;
        memcpy(qtsg+i, &qstg_text_info, sizeof(T_Text) );
        SDL_LockMutex(p->qs_mutex);
        Draw_text(p->scr, &qstg_text_info,&scr_info);
        SDL_UnlockMutex(p->qs_mutex);
    }

    do {

        for (int i=0; i<p->queue_num; i++) {
            memset((qtsg+i)->content, 0, STRINGS_LEN);
            sprintf((qtsg+i)->content,"  %-3d  ", (p->qs+p->queue_num_offset+i)->length);
            SDL_LockMutex(p->qs_mutex);
            Draw_text(p->scr, (qtsg+i),&scr_info);
            SDL_UnlockMutex(p->qs_mutex);
            SDL_Flip(p->scr);
        }
        SDL_Delay(10);

    } while (1);

    return (void*) NULL;
}

int  Initialize_queues_UI(SDL_Surface *screen, T_Monitor_Packet *pkt, T_Queue_Info *qs,  pthread_t *ui_tid_table,int ui_tid_table_offset)
{
    assert(NULL!=screen);
    assert(NULL!=pkt);
    assert(NULL!=qs);

    int err = 0;

    int client_num = 0;
    client_num = pkt->client_num;

    //mutex for sharing memories
    SDL_mutex *qs_mutex;

    qs_mutex = SDL_CreateMutex();
    assert(NULL != qs_mutex);

    //UI for recv queues

//   pthread_t tid_ui_recv_q;
    T_Draw_Queue_State_Param *param;
    param = malloc( sizeof(T_Draw_Queue_State_Param) );
    assert(NULL!=param);
    memset(param, 0, sizeof(T_Draw_Queue_State_Param));

    char f_name[]=".//cfg_files//qsg4rec.xml";
    param->scr = screen;
    param->queue_num = pkt->rec_queue_num;
    param->queue_num_offset = 0;
    memcpy(param->cfg_file,f_name, strlen(f_name) );
    param->qs = qs;
    param->qs_mutex = qs_mutex;
    err = pthread_create(ui_tid_table+ui_tid_table_offset, NULL, (void*)Update_queue_state, (void*)param);

    //UI for decoder threads
//    pthread_t tid_ui_decoder;
    T_Draw_Queue_State_Param *ui_decoder_param;
    ui_decoder_param = malloc( sizeof(T_Draw_Queue_State_Param) );
    assert(NULL!=ui_decoder_param);
    memset(ui_decoder_param, 0, sizeof(T_Draw_Queue_State_Param));

    char decoder_thread_cfg_name[]=".//cfg_files//qsg4dec.xml";
    ui_decoder_param->scr = screen;
    ui_decoder_param->queue_num = pkt->dec_queue_num;
    ui_decoder_param->queue_num_offset = pkt->rec_queue_num;
    memcpy(ui_decoder_param->cfg_file,decoder_thread_cfg_name, strlen(decoder_thread_cfg_name) );
    ui_decoder_param->qs = qs;
    ui_decoder_param->qs_mutex = qs_mutex;
    pthread_create(ui_tid_table+ui_tid_table_offset+1, NULL,(void*)Update_queue_state, (void*)ui_decoder_param);


    //UI for mixed queues
//    pthread_t tid_ui_mixed;
    T_Draw_Queue_State_Param *ui_mixed_param;
    ui_mixed_param = malloc( sizeof(T_Draw_Queue_State_Param) );
    assert(NULL!=ui_mixed_param);
    memset(ui_mixed_param, 0, sizeof(T_Draw_Queue_State_Param));

    char mixed_thread_cfg_name[]=".//cfg_files//qsg4mix.xml";
    ui_mixed_param->scr = screen;
    ui_mixed_param->queue_num = pkt->mix_queue_num;
    ui_mixed_param->queue_num_offset = pkt->rec_queue_num + pkt->rec_queue_num ;
    memcpy(ui_mixed_param->cfg_file,mixed_thread_cfg_name, strlen(mixed_thread_cfg_name) );
    ui_mixed_param->qs = qs;
    ui_mixed_param->qs_mutex = qs_mutex;
    pthread_create(ui_tid_table+ui_tid_table_offset+2, NULL,(void*)Update_queue_state, (void*)ui_mixed_param);


    //UI for encoded queues
//    pthread_t tid_ui_encoded;
    T_Draw_Queue_State_Param *ui_encoded_param;
    ui_encoded_param = malloc( sizeof(T_Draw_Queue_State_Param) );
    assert(NULL!=ui_encoded_param);
    memset(ui_encoded_param, 0, sizeof(T_Draw_Queue_State_Param));

    char encoded_thread_cfg_name[]=".//cfg_files//qsg4enc.xml";
    ui_encoded_param->scr = screen;
    ui_encoded_param->queue_num = 1;
    ui_encoded_param->queue_num_offset = pkt->rec_queue_num + pkt->rec_queue_num + pkt->mix_queue_num;
    memcpy(ui_encoded_param->cfg_file,encoded_thread_cfg_name, strlen(encoded_thread_cfg_name) );
    ui_encoded_param->qs = qs;
    ui_encoded_param->qs_mutex = qs_mutex;
    pthread_create(ui_tid_table+ui_tid_table_offset+3, NULL,(void*)Update_queue_state, (void*)ui_encoded_param);
    SDL_Delay(500);
    return 1;


}

