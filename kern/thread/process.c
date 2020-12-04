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

/* Process table for active processes */
static struct process *process_table[100];

/*
 * Assign an available pid for a process
 */
pid_t
gen_pid() {
	return 0;
}

/*
 * Check whether PID is being used
 *
 * Returns:
 * 1 - true
 * 0 - false
 */
int 
check_pid(pid_t pid) {
	return 0;
}

/*
 * Remove a process 
 *
 * Returns:
 * 1 - Success
 * 0 - Failure 
 */
int
remove_process(pid_t pid) {
	return 0;
}


/*
 * Process initialization.
 */
struct process *
process_bootstrap(void) 
{

}
