#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "File.h"

const char* program_name;

void print_usage (FILE* stream, int exit_code) {

    fprintf(stream, "Use : %s [-f filename ]\n", program_name);

    fprintf(stream,
	" -h --help                      Display usage.\n"
        " -f --file filename             Input file.\n"
	" -o --output filename           Redirect output to a file.\n"
        " -s --search key:expression     Search expression in key. i.e. -s 200$a:foo.\n");

    exit(exit_code);
}

// MAIN //
int main(int argc, char *argv[]) {

    program_name = argv[0];

    const char* output_filename = NULL;
    char *input_file = NULL;
    char *search = NULL;
    char *key = NULL;
    char *occur = NULL;
    //extern char * optarg;

    int next_option;

    const char* short_options = "hf:o:s:";

    const struct option long_options[] = {
	{ "help",     0, NULL, 'h' },
	{ "file",     1, NULL, 'f' },
	{ "output",   1, NULL, 'o' },
	{ "search",   1, NULL, 's' },
	{ NULL,       0, NULL, 0   }
    };

    do {
	next_option = getopt_long (argc, argv, short_options, long_options, NULL);

	switch (next_option)
	{
	    case 'h':
		print_usage (stdout, 0);
	    case 'f':
		input_file = optarg;
	    case 'o':
		output_filename = optarg;
	    case 's':
		search = optarg;
	    case -1:
		break;
	}

    }
    while (next_option != -1);

    if ( input_file == NULL ) {
	print_usage(stderr, 1);
    }

    if ( search != NULL ) {
	printf("Recherche: %s\n", search);
	key = strtok(search, ":" );
	occur = strtok(NULL, ":" );
	printf("Key: %s\n", key);
	printf("Occur: %s\n", occur);
    }
    File f = File_in( input_file );

    Record *r = f.Next(&f);
    while ( r != NULL ) {
        r->as_text(r);
        r = f.Next(&f);
    }
    return 0;
}
