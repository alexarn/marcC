#include <string.h>
#include "Record.h"

static void Record_Init(Record*);

Record *new_Record() {
    Record *This = malloc(sizeof(Record));
    Record_Init(This);
    return This;
}

static void Record_Init(Record *This) {
    This->fields = NULL;
    This->set_leader = Record_set_leader;
    This->add_field = Record_add_field;
    This->as_text = Record_as_text;
}

void Record_set_leader(Record *This, char leader[]) {
    This->leader = leader;
}

void Record_add_field(Record *This, Field *f) {
    if ( This->fields == NULL ) {
        This->fields = f;
    } else {
        Field *temp = This->fields;
        while ( temp->nxt != NULL ) {
            temp = temp->nxt;
        }
        temp->nxt = f;
    }
}

void Record_as_text(Record *This) {
    if ( This->fields == NULL ) {
        printf("Empty record\n");
    } else {
	printf("LDR %s\n", This->leader);
	Field *tmp = This->fields;
	tmp->as_text(tmp);
    	while ( tmp->nxt != NULL ) {
	    tmp = tmp->nxt;
	    tmp->as_text(tmp);
    	}
	printf("\n");
    }
}
