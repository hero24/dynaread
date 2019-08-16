#include <stdio.h>
#include <stdlib.h>

/*
 * "But in the end It doesn't even matter" ~ Linkin Park, In the end
 */

#define INIT_BUFF 80
#define INC_BUFF 10
#define INC_BUFFSZ 25
#define LINE_END '\n'
#define STR_END '\0'


char * read_in(int* count, char sep, int buff_sz, int inc_buffsz)
{
        /*
         * Read input from STDIN whilst dynamically allocating buffers.
         * Will retrun the length of the read in string and the string.
         * In case of allocation errors will return the string read in so far
         * and its length. If the failure happens on initial allocation returns
         * NULL pointer.
         */
        char* buff = malloc(sizeof(char)*buff_sz);
        *count = 0;
        if(!buff)
                return buff;
        char* buff_stp = buff;
        int c,rd_cnt = 0;
        for(c=getchar(); c != sep && rd_cnt < buff_sz; c = getchar(), rd_cnt++){
                if(rd_cnt == buff_sz-1){
                        buff_stp = realloc(buff_stp, sizeof(char) * (buff_sz + inc_buffsz));
                        if(!buff_stp)
                                break;
                        buff_sz += inc_buffsz;
                        buff = buff_stp + rd_cnt;
                }
                *buff = c;
                buff++;
        }
        *count = rd_cnt;
        *buff = STR_END;
        if(buff_stp)
                buff_stp = realloc(buff_stp, rd_cnt * sizeof(char));
        if(!buff_stp)
                buff_stp = buff - rd_cnt;
        return buff_stp;
}


char * readline_in(int* count)
{
        /*
         * Read a line from STDIN whilst allocating dynamically buffers for
         * incoming string. Returns a string and its length.
         * In case of failure while resizing buffer size, returns the string
         * read in so far and its length.
         * In case of failure in buffer allocation returns a NULL pointer.
         */
        return read_in(count, LINE_END, INIT_BUFF, INC_BUFF);
}

char * readpipe_in(int* count)
{
        /*
         * Read a piped input from STDIN whilst allocating dynamically buffers
         * for incoming string. Returns a string and its length.
         * In case of failure while resizing buffer size, returns the string
         * read in so far and its length.
         * In case of failure in buffer allocation returns a NULL pointer.
         */
        return read_in(count, EOF, INIT_BUFF, INC_BUFFSZ);
}
