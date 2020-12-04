/** waitpid.c */

/*
 *  Function: sys_waitpid()
 *  Wait for process with pid to exit
 *
 *  Return: pointer status containing exit code
 */

int sys_waitpid(pid_t pid, userptr_t status, int options, int *ret){
	//search global process_table and retrieve process
	//assume this is the retrieved process with corresponding pid
	struct process *p;

	//get calling process
	//assume this is the found calling process
	struct process *calling_proc

	calling_proc->wait = p;

	//have thread go to sleep??
	//done continuously until other process has exited and exitcode defined??
	
}
