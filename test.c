#include <stdio.h>
#include <stdlib.h>
#include "File.h"

int main(int argc, char *argv[])
{
    //char file[] = "camel.usmarc";
    //File monfichier = File_in( file );

    Record record = new_Record();

    //printf("%d\n", monfichier.cnt);
    Field f995 = new_Field( "995", 0 );
    f995.add_subfield(&f995, 'a', "quelque chose");
    f995.add_subfield(&f995, 'b', "quelque chose d'autre");

    int i = 0;
    while ( i < 3 ) {
        f = new_Field( "630", 0 );
	f.add_subfield(&f, 'a', "Active server pages.");
	Field* tmp = malloc(sizeof(Field));
	tmp = &f;
        record.add_field(&record, tmp);
        i++;
    }

    Field f610 = new_Field( "610", 0 );
    f610.add_subfield(&f610, 'a', "Perl (Computer program language)");

    Field f650 = new_Field( "650", 0 );
    f650.add_subfield(&f650, 'a', "as Martinsson.");

    record.set_leader(&record, "01083njm i 200277   450");
    record.add_field(&record, &f995);
    record.add_field(&record, &f610);
    record.add_field(&record, &f650);

    record.as_text(&record); 

    //char * chose = monfichier.Next(&monfichier);
    //printf("%s\n", chose);
    //printf("%s\n", "-----------------------------------------------------------------");

	/*
    //printf("%d\n", monfichier.cnt);

    char * chose2 = monfichier.Next(&monfichier);
    printf("%s\n", chose2);
    printf("%s\n", "-----------------------------------------------------------------");

    char * chose3 = monfichier.Next(&monfichier);
    printf("%s\n", chose3);
    printf("%s\n", "-----------------------------------------------------------------");
	*/
    //Record myNewRecord = decode(chose);
    //myNewRecord.as_text(&myNewRecord); 
    //printf("LDR %s\n", ldr);

    //printf("%d\n", monfichier.cnt);

    return 0;
}
