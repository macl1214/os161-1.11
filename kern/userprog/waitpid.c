/** waitpid.c */

/*
 *  Function: sys_waitpid()
 *  Wait for process with pid to exit
 *
 *  Return: pid, assign pointer status containing exit code
 */

int sys_waitpid(pid_t pid, userptr_t status, int options, int *ret){
	/*
 	* Get child process with pid
 	* check if calling process is pointing to child process with wait pointer
 	* If calling process is defined then check if child process has hasexited and exitcode defined
 	* If not defined then have calling process yield continuously or sleep continuously until the child process has
 	* Once defined set outputs and clear wait pointer
 	*
 	* Child process cannot exit until calling process has changed their wait pointer to something else
 	* until then child process has to wait as well
 	* Once calling process has removed child process from wait pointer then child process can proceed to process removal procedures
 	* 	This all may have to be checked inside of thread_exit
 	*/

	// == CHECK IF OPTION ARGS ARE INVALID/UNSUPPORTED AND IF STATUS WAS INVALID ==
	// 	Assign *ret to error codes: EINVAL/EFAULT
	// 	return -1

	//options check
	if(options != 0){
		retval = EINVAL;
		return -1;
	}

	//get child process with pid
	//assume this is found child process
	struct process *child_p;

	//get calling process
	//assume this is found calling process
	struct process *calling_p;

	//define calling process waiting on child process
	calling_p->wait = child_p;

	//check if child process has exited and has exit code
	while(child_p->has_exit == NULL && child_p->exitcode == NULL){
		//have calling process sleep/wait
		thread_yield();
	}
	
	//set outputs
	status = child_p->exitcode;
	
	return pid;
}
