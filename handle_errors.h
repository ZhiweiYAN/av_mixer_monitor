/*
 * =====================================================================================
 *
 *       Filename:  handle_errors.h
 *
 *    Description:  handle the errors which happen anytime
 *
 *        Version:  1.0
 *        Created:  10/4/2010 6:56:06 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */
#ifndef  HANDLE_ERRORS_H_INC
#define  HANDLE_ERRORS_H_INC

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#ifdef DEBUG
# define DBG(format, args...) printf(format, ##args)
#else
# define DBG(format, args...)
# define NDEBUG
#endif


void Log_begin(void);
void Log_string(const char *string);
void Log_error(const char *file_name, const char *func_name, const int line_num);

#define OUTPUT_OK do{printf("%s","[\033[32mOK\033[0m]\n");fflush(NULL);}while(0);
#define OUTPUT_ERROR do{ printf("\t[\033[31mERROR\033[0m]. -->>>Details in log_error.txt.\n");perror("Error Tips");fflush(NULL);Log_error(__FILE__,__FUNCTION__,__LINE__);}while(0);

#endif   /* ----- #ifndef HANDLE_ERRORS_H_INC  ----- */



