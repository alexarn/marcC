#include <string.h>
#include "Field.h"

static void Field_Init(Field*);

Field *new_Field(char * tag, int is_control_field) {
    Field *This = malloc(sizeof(Field));
    //Field This;
    This->tag = tag;
    This->pos1 = ' ';
    This->pos2 = ' ';
    This->is_control_field = is_control_field;
    This->subfields = NULL;
    This->nxt = NULL;
    Field_Init(This);
    return This;
}

static void Field_Init(Field *This) {
    This->add_indicators = Field_add_indicators;
    This->add_subfield = Field_add_subfield;
    This->as_text = Field_as_text;
}

void Field_add_indicators(Field *This, char indicators1, char indicators2) {
    This->pos1 = indicators1;
    This->pos2 = indicators2;
}

void Field_add_subfield(Field *This, char subtag, char value[]) {
    Subfield* newSubfield = malloc(sizeof(Subfield));
    newSubfield->subtag = subtag;
    newSubfield->value = value;
    newSubfield->nxt = NULL;

    if ( This->subfields == NULL ) {
	This->subfields = newSubfield;
    } else {
        Subfield *tmp = This->subfields; 
        while ( tmp->nxt != NULL ) {
            tmp = tmp->nxt;
        }
        tmp->nxt = newSubfield;
    }
}

void Field_as_text(Field *This) {
	
    if ( This->subfields == NULL ) {
        printf("Empty field\n");
    } else {
        printf("%s %c%c _", This->tag, This->pos1, This->pos2);
        Subfield *tmp = This->subfields;
	if ( This->is_control_field ) {
	    printf("%s\n", tmp->value);
	} else {
	    printf("%c%s\n", tmp->subtag, tmp->value);
	    while ( tmp->nxt != NULL ) {
		tmp = tmp->nxt;
		printf("       _%c%s\n", tmp->subtag, tmp->value);
	    }
	}
    }
}

int Field_is_controlfield(char * tagno) {

	char * bytag = "001";
	if ( strcmp(tagno, bytag)==0 ) {
		return 1;
	} else {
		return 0;
	}
}
