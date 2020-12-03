#ifndef _PROCESS_TABLE_H_
#define _PROCESS_TABLE_H_

typedef struct PROCESS_TABLE {
	int size;
	struct process** table;
} PROCESS_TABLE;

void add_process(PROCESS_TABLE* ptable,struct process* p);
void remove_process(PROCESS_TABLE* ptable, struct process* p);

#endif
