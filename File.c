#include <string.h>
#include "File.h"

#define LEADER_LEN 24
#define DIRECTORY_ENTRY_LEN 12

static void File_Init(File*);

File File_in( char file[] )
{
    File This;
    File_Init(&This);
    This.filename = file;
    This.cnt = 0;
    This.fh = fopen(file, "r+");
    return This;
}

static void File_Init(File *This) {
    This->Next = File_Next;
}

char * File_Next(File *This) {

    char * record = get_next_record(This);
    return record;
}

char * get_next_record(File *This) {

    char * recBuffer, record[10000];
    int caractere;
    int i = 0;
    while ( (caractere = fgetc(This->fh)) ) {
	if ( caractere == 29 || caractere == EOF ) { break; }
	record[i] = caractere;
	i++;
    }

    recBuffer = malloc(strlen(record) + 1);
    if (recBuffer != NULL) {
	strcpy(recBuffer, record);
    }

    return recBuffer;
}

Record decode(char *record) {

    Record myNewRecord = new_Record();
    char * r = record;

    // Extract LDR ( characters 0 to 23 )
    char * ldr = substr(r, 0, LEADER_LEN); 
    myNewRecord.set_leader(&myNewRecord, ldr);

    //Extract Data start
    int start_data = atoi(substr(r, 12, 5)); 

    // The directory comes immediatly after the leader
    char * dir = substr(r, LEADER_LEN, start_data - LEADER_LEN -1);

    int nfields;
    if ( strlen(dir) % DIRECTORY_ENTRY_LEN == 0 ) {
	nfields = strlen(dir) / DIRECTORY_ENTRY_LEN;
		
	int i = 0;
	while ( i < nfields ) {
	    char * field = substr(dir, i*DIRECTORY_ENTRY_LEN, DIRECTORY_ENTRY_LEN);
	    char * tag = substr(field, 0, 3);
	    int taglen = atoi(substr(field, 3, 4));
	    int offset = atoi(substr(field, 7, 5));
	    char * tagdata = substr(r, start_data + offset, taglen);
	    char * value = substr(tagdata, 0, strlen(tagdata) -1);
	    char * tmp_controlchar = substr(value, 2, 1);
	    int controlchar = tmp_controlchar[0];

	    int is_control_field = ( controlchar == 31 ) ? 0 : 1;
printf("Nouveau Field");
	    Field *myNewField = new_Field(tag, is_control_field);
printf(" => passé\n");

	    // TEMP
	    printf("tagdata: '%s'\n", tagdata);
	    printf("tag: '%s'\n", tag);
	    printf("Control: '%d'\n", controlchar);
	    if ( controlchar == 31 ) { 
		printf("true\n");
	    }

	    // if control field
	    if ( controlchar != 31 ) {

printf("Nouveau SubField de controle");
		myNewField->add_subfield(myNewField, ' ', value);
printf(" => passé\n");
		//myNewField.as_text(&myNewField);
		//myNewRecord.add_field(&myNewRecord, &myNewField);
	    }

	    // if no control field 
	    else {

		char * subfield;
		const char base[] = "";
		char delimiter [1];
		char ascii = 31;
		sprintf(delimiter, "%s%c", base, ascii);

		int nsf = 0;
		subfield = strtok(value, delimiter );
		while ( subfield != NULL ) {
		    if ( nsf > 0 ) {
			char * tmpsubtag = substr(subfield, 0, 1);
			char subtag = tmpsubtag[0];
			char * value_of_subfiled = substr(subfield, 1, strlen(subfield)-1);

printf("Nouveau SubField");
			myNewField->add_subfield(myNewField, subtag, value_of_subfiled);
printf(" => passé\n");
						
		    }
		    subfield = strtok(NULL, delimiter );
		    nsf++;
		}
		//myNewField.as_text(&myNewField);
		//myNewRecord.add_field(&myNewRecord, &myNewField);
	    }
	    i++;
printf("Ajout du Field au record");
	    myNewRecord.add_field(&myNewRecord, myNewField);
printf(" => passé\n");
printf("--------------------------------\n");
	}
    } 
    else {
	printf("That's wrong\n");
    }
    return myNewRecord;
    //return record;
}

char * substr(char *src, int pos, int len) { 
    char *dest=NULL;                        
    if (len>0) {                            
	dest = (char *) malloc(len+1);        
	strncat(dest,src+pos,len);            
    }                                       
    return dest;                            
}
