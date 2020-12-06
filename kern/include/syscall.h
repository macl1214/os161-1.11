#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int sys_getpid(pid_t *retval);
int sys_getppid(pid_t *retval);
int sys_fork(struct trapframe *parent_tf, pid_t *retval);
int sys_execv(const char* path, char* const argv[]);
int sys_waitpid(pid_t pid, userptr_t status, int options, int *retval);
int sys__exit(int exitcode);


#endif /* _SYSCALL_H_ */
