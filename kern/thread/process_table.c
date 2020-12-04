#include <process_table.h>
#include <types.h>

static void shift_left(PROCESS_TABLE* ptable, int index){
	int i;
	for(i = index; i < ptable->size; i++){
		ptable->table[i] = ptable->table[i+1];
		ptable->table[i+1] = NULL;
	}
}

static void shift_right(PROCESS_TABLE* ptable, int index){
	int i;
	for(i = ptable->size; i > index; i--){
		ptable->table[i] = ptable->table[i-1];
		ptable->table[i-1] = NULL;
	}
}

void add_process(PROCESS_TABLE* ptable, struct process* p){
	int i;
	for(i = 0; i < ptable->size; i++){
		struct process* proc = ptable->table[i];

		if(proc == NULL){
			proc = p;
		}else if(p->pid == proc->pid){
			p->pid++;
		}else{
			ptable->size++;
			shift_right(ptable, i);
			ptable->table[i] = p;
			break;
		}
	}
}

void remove_process(PROCESS_TABLE* ptable, struct process* p){
	int i;
	for(i = 0; i < ptable->size; i++){
		struct process* proc = ptable->table[i];
		
		if(proc == p){
			proc = NULL;
			shift_left(ptable, i);
			ptable->size--;
		}
	}
}
