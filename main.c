#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "File.h"

const char* program_name;

void print_usage (FILE* stream, int exit_code) {

    fprintf(stream, "Use : %s [ filename ]\n", program_name);

    fprintf(stream,
	" -h --help               Display usage.\n"
	" -o --output filename    Redirect output to a file.\n");

    exit(exit_code);
}

int main(int argc, char *argv[]) {

    program_name = argv[0];

    if ( argc != 2 ) {
	printf("This command expects one argument\n");
	exit(EXIT_FAILURE);
    }

    int next_option;

    const char* const short_options = "ho";

    const struct option long_options[] = {
	{ "help",     0, NULL, 'h' },
	{ "output",   1, NULL, 'o' },
	{ NULL,       0, NULL, 0   }
    };

    do {
	next_option = getopt_long (argc, argv, short_options,
	    long_options, NULL);

	switch (next_option)
	{
	    case 'h':
		print_usage (stdout, 0);
	}

    }
    while (next_option != -1);

    
    char *file = argv[1];
    File f = File_in( file );

    Record *r = f.Next(&f);
    while ( r != NULL ) {
	r->as_text(r);
	r = f.Next(&f);
    }
}
