/** exit.c */

#include <types.h>
#include <syscall.h>
#include <thread.h>
#include <curthread.h>

/*
 *  Function: sys_exit()
 *
 */

int 
sys__exit(int exitcode) 
{
	struct process *parent;
	struct process *cur;
	pid_t cur_pid;

	cur_pid = curthread->pid;
	cur = get_process(cur_pid);
	cur->exited = 1;
	cur->exitcode = exitcode;

	thread_exit();
}
