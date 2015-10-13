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

    filename: tee.h

    contains all header information required for the tee command functions 
*/

#include <inttypes.h>
#include "err_handle/err_handle.h"

#define _APPEND_    0x1
#define BUFF        512

/* initiate the tee functionality, flag indicates append option.
   returns EOF on end of file, bytes read from stdin on sucess, -1 on error */ 
int32_t sedihs_tee(const char *path, int32_t flag);

