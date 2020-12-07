/* fork.c */

/*
 * Function: sys_fork()
 *
 */

#include <types.h>
#include <syscall.h>
#include <process.h>
#include <thread.h>
#include <curthread.h>


pid_t 
sys_fork(struct trapframe *parent_tf, pid_t *retval)
{
	struct trapframe *child_tf;
	struct addrspace *child_addrspace;
	struct thread *child_thread;

	if ((child_tf = kmalloc(sizeof(struct trapframe))) == NULL) {
		return ENOMEM;
	}
	
	child_addspace = kmalloc(struct addrspace);

	//look for copy function for trapframes
	//copyin or copyout or memcpy?

	*child_thread = thread_fork("child thread", parent_tf, child_tf, md_forkentry, NULL);
	child_thread->ppid = curthread->pid;

	as_copy(curthread->t_vmspace, child_thread->t_vmspace);

	as_activate(child_thread->t_vmspace);
	mips_usermode(child_tf);
}
