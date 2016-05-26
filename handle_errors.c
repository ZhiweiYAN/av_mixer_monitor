/*
 * =====================================================================================
 *
 *       Filename:  handle_errors.c
 *
 *    Description:  deal with errors which happen anytime.
 *
 *        Version:  1.0
 *        Created:  10/4/2010 6:54:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhi-wei YAN (Jerod YAN), jerod.yan@gmail.com
 *        Company:  DrumTm
 *
 * =====================================================================================
 */

#include "handle_errors.h"


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Log_error
 *  Description:  Record the position when and where the errors take place into log file
 * =====================================================================================
 */
void Log_error(const char *file_name, const char *func_name, const int line_num)
{
    FILE* fp_log = NULL;
    time_t t;

    fp_log = fopen("log_errors.txt","a+");
    if (NULL==fp_log) {
        fclose(fp_log);
        fp_log = NULL;
        return;
    }

    t = time(NULL);
    fprintf(fp_log,"ERROR happened on %s-->>> Function_Name: %s(), File_Name: %s:(%d)\n\n",ctime(&t),func_name,file_name,line_num);

    fflush(fp_log);
    fclose(fp_log);
    fp_log = NULL;

    return;

}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  Log_string
 *  Description:  Record a string into the log file
 * =====================================================================================
 */
void Log_string(const char *string)
{
    FILE* fp_log = NULL;
    time_t t;

    fp_log = fopen("log_errors.txt","a+");
    if (NULL==fp_log) {
        fclose(fp_log);
        fp_log = NULL;
        return;
    }

    t = time(NULL);
    fprintf(fp_log,"STRING:|%s|",string);

    fflush(fp_log);
    fclose(fp_log);
    fp_log = NULL;

    return;

}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  void Log_errors(void)
 *  Description:  create a log file
 * =====================================================================================
 */
void Log_begin(void)
{
    FILE* fp_log = NULL;
    time_t t;

    fp_log = fopen("log_errors.txt","w");
    if (NULL==fp_log) {
        fclose(fp_log);
        fp_log = NULL;
        return;
    }

    t = time(NULL);
    fprintf(fp_log,"LOG BEGIN ON %s\n",ctime(&t));

    fflush(fp_log);
    fclose(fp_log);
    fp_log = NULL;
    printf("LOG SYSTEM: [\033[32mOK\033[0m]\n");
    fflush(NULL);

    return;

}


