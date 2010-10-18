#include <stdio.h>
#include <stdlib.h>
#include "Record.h"

typedef struct File
    {
	int cnt;
	char *filename;
	FILE* fh;
	/* Methode */
	Record*(*Next)(struct File*);
    } File; 

File File_in(char chaine[] );
Record * File_Next(File*);
char * get_next_record(File*);
Record * decode(char*);
char * substr(char*, int, int);
