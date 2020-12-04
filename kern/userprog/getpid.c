/*  getpid.c */

/*
 *  Function: sys_getpid()
 *
 */

#include <types.h>
#include <syscall.h>
// #include <process.h>
#include <thread.h>
#include <curthread.h>

int
sys_getpid(pid_t *retval)
{
	*retval = curthread->t_pid;
	return 0;
}
