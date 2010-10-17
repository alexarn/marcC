#include <stdio.h>
#include <stdlib.h>

typedef struct Subfield
    {
	char subtag;
	char *value;
	struct Subfield *nxt;
    } Subfield;

//typedef Subfield* l_fields;

typedef struct Field
    {
	char *tag;
	Subfield *subfields;
	int is_control_field;
	struct Field *nxt;

	void(*add_subfield)(struct Field*, char, char*);
	void(*as_text)(struct Field*);
    } Field;

Field *new_Field(char*, int);
void Field_add_subfield(Field*, char, char*);
void Field_as_text(Field*);
int Field_is_controlfield(char*);
