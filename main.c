#include <stdio.h>
#include <stdlib.h>
#include "File.h"

int main(int argc, char *argv[]) {
    if ( argc != 2 ) {
	printf("This command expects one argument\n");
	exit(EXIT_FAILURE);
    }
    
    char *file = argv[1];
    File f = File_in( file );

    Record *r = f.Next(&f);
    while ( r != NULL ) {
	r->as_text(r);
	r = f.Next(&f);
    }
}
