#ifndef _PROCESS_H_
#define _PROCESS_H_

/*
 * Definition of a process
 */

/* Get machine-dependent stuff */
#include <machine/pcb.h>
#include "kern/types.h"

/*
 * Max number of processes
 */
#define MAX_P 2048

struct process {
	/************************************************************/
	/* Private process members - internal to the process system */
	/************************************************************/

	pid_t pid;							// pid
	pid_t p_pid;						// parent pid
	struct thread* thrds;		// threads associated with the process

	struct process *wait;	//pointer to process that this is waiting on
 
	int has_exited;					// exit status
	int exitcode;						// exit code

};

struct process_table {
	pid_t pid;
	
}

/** Call once during startup to allocate data structures */
struct process *process_bootstrap(void);

/** Generate pid for a process */
pid_t gen_pid();

/** Call to check if pid exists */
int check_pid(pid_t pid);

/** Remove a process */
int remove_process(pid_t pid);

#endif /* _PROCESS_H_ */
