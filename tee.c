/*
    exercise 4.10, page 87, linux programming interface handbook

    Reimplement $tee, aswell as the $tee -a file

    teeMain.c is main, using getopt to parse the command line
    arguments passed.

    $tee reads from standard input until EOF, and writes a copy of the input
    to stdout.

    $tee -a file reads from standard input until EOF, and appends the text to
    the end of a file, given with the file argument after the -a flag.

    USEING I/O SYSTEM CALLS.

    filename: tee.c

    contains all fucntions declared in my_tee.h
*/

#include <sys/types.h>
#include <sys/stat.h>   /* open() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     /* read(), write() */
#include <fcntl.h>      /* open() */
#include <inttypes.h>

#include "tee.h"


int32_t sedihs_tee(const char *path, int32_t flags)
{
    int32_t fd = 0;                  /* file descriptor */
    ssize_t rbytes = 0;              /* ammount of bytes read from buffer */
    char inBuff[BUFF] = {'\0'};      /* read buffer */
    
    /* open(); no third arg. defaulted perms */
    if((flags & _APPEND_) &&        
       (fd = open(path, O_APPEND | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1){                                   
        errExit("open()");} 

    if((flags & _APPEND_) == 0){
        fd = STDOUT_FILENO;} 

    /* gather user input untill EOF, writing at each newline */
    do
    {
        /* clear inBuff */
        memset((void*)inBuff, '\0', BUFF);

        /* read from fd */
        rbytes = read(STDIN_FILENO, (void*)inBuff, BUFF);
        if(rbytes == -1){
            errExit("read()");} 
    
        /* write to file */
        /* ERR NOTE: if it writess less bytes than read, that is considered
                     a fail in this instance. This does not check for that */
        if(write(fd, (void*)inBuff, BUFF) == -1){
            errExit("write");}
    }while(rbytes != 0 && (rbytes == BUFF && inBuff[BUFF-1] != '\n'));
    
    if(rbytes == 0){
        if(close(fd) == -1){
            errExit("close");} /* end if */
        return EOF;
    } /* end if */

    return rbytes;
} /* end sedihs_tee */

