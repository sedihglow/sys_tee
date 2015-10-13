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

    filename: teeMain.c
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "tee.h"



int32_t main(int32_t argc, char *argv[])
{
    int32_t appFlag = 0x0;  /* append flag */
    int32_t opt = 0;        /* handles the return value of getopt */ 
    char *path = NULL;      /* name of the path to append */

    puts("\nThis is a remake of the command tee. By default, with no flags or\n"
         "arguments, tee prints what is types to STDOUT.\n\n"
         "With the -a filename flag and argument, it appends the test inputed "
         "into a file.\nInsert text below, signal EOT (ctr+d) when complete.\n");
    
    if(argc == 2){
        noerrExit("\nInvalid arguemnts. $cmd || $cmd -a flag\n");}

    if(argc > 3){
        noerrExit("\nToo many arguments, $cmd || $cmd -flag file\n");}

    /* parse through argv, checking for the -a flag to append */
    if(argc > 1)
    {   /* since there is only 1 flag, the while loop might be overkill, but
           i wanted to do this to properly use since its my first time using
           getopt. Extreme example is in pope_cards programs main */
        while((opt = getopt(argc, argv, "a:")) != -1)
        {
            switch(opt)
            {
                case 'a': appFlag = _APPEND_;
                          path = argv[optind - 1]; break;
                default: noerrExit("\nBad arguemnts, $cmd -a file\n");
            }
        } /* end while */
    } /* end if */

    /* gather user input untill EOF signal */
    /* NOTE: Opt is now used as the return value for tee. */
    do{
        opt = sedihs_tee(((appFlag != _APPEND_) ? "stdout" : path), appFlag);
    }while(opt != EOF && opt != -1);

    if(opt == -1){
        exit(EXIT_FAILURE);} 

    exit(EXIT_SUCCESS);
} /* end main */
