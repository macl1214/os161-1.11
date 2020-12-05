/*
 * Core process system
 */
#include <types.h>
#include <lib.h>
#include <kern/errno.h>
#include <array.h>
#include <machine/spl.h>
#include <machine/pcb.h>
#include <process.h>
#include <thread.h>
#include <curthread.h>
#include <scheduler.h>
#include <addrspace.h>
#include <vnode.h>
#include <synch.h>
#include "opt-synchprobs.h"

struct process *process_table[MAX_P];

/*
 * Assign an available pid for a process
 *
 * Returns the PID
 */
pid_t
process_create(pid_t pid)
{
	int index;
	pid_t child_pid;

	index = find_space();

	process_table[index] = kmalloc(sizeof(struct process));
	
	process_table[index]->pid = 0;
	process_table[index]->ppid = pid;
	process_table[index]->has_exited = 0;
	process_table[index]->exitcode = -1;

	child_pid = index+1;	// To avoid having a process with a PID of 0

	return child_pid;
}

/*
 * Check whether PID is being used
 *
 * Returns:
 * 1 - true
 * 0 - false
 */
int 
find_space() 
{
	int index, i;

	for (i = 0; i < MAX_P; i++) {
		if (process_table[i] == NULL) {
			index = i;
			break;
		}
	}

	return index;
}

/*
 * Remove a process 
 *
 * Returns:
 * 1 - Success
 * 0 - Failure 
 */
int
remove_process(pid_t pid) 
{
	return 0;
}

/*
 * Return the process being searched by pid
 * from the process table
 *
 * Rreturns:
 * Process - if found
 * NULL		 - if not found
 */
struct
process *
get_process(pid_t pid) 
{
	int index = ((int) pid) - 1;

	return process_table[index];		
}


/*
 * Process table initialization
 */
void
process_bootstrap(void) 
{
	int i;
	
	for (i=0; i<MAX_P; i++) {
		process_table[i] = NULL;
	}	
}
