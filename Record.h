#include <stdio.h>
#include <stdlib.h>
#include "Field.h"

typedef struct Record
    {
	char *leader;
	Field *fields;

	void(*set_leader)(struct Record*, char*);
	void(*add_field)(struct Record*, struct Field*);
	void(*as_text)(struct Record*);
    } Record;

Record *new_Record();
void Record_set_leader(Record*, char*);
void Record_add_field(Record*, Field*);
void Record_as_text(Record*);
