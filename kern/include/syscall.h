#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int sys_getpid();
int sys_getppid();
int sys_fork();
int sys_execv();
int sys_waitpid();
int sys_exit();


#endif /* _SYSCALL_H_ */
