#ifndef _PROCESS_H_
#define _PROCESS_H_

/*
 * Definition of a process
 */


/* Get machine-dependent stuff */
#include <array.h>
#include <machine/pcb.h>
#include "kern/types.h"

/*
 * Max number of processes
 */
#define MAX_P 256

struct array *process_table;

struct process {
	/************************************************************/
	/* Private process members - internal to the process system */
	/************************************************************/

	pid_t pid;							// pid
	pid_t p_pid;						// parent pid
	struct thread* thrds;		// threads associated with the process

	//	struct process *wait;		// pointer to process that this is waiting on
 
	int has_exited;					// exit status
	int exitcode;						// exit code

};

/** Call once during startup to allocate data structures */
struct process *process_bootstrap(void);

/** Create a process and return the PID */
pid_t process_create();

/** Call to find empty spot in process table and return index */
int find_space();

/** Call to retrieve process (Used to get from process table) */
struct process* get_process(pid_t pid);

/** Remove a process */
int remove_process(pid_t pid);

#endif /* _PROCESS_H_ */
