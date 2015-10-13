main:	teeMain.c tee.c err_handle/err_handle.c
	gcc -Wall -Wextra -g -O0 -m64 teeMain.c tee.c err_handle/err_handle.c
