pid_t sys_fork(struct trapframe *parent_tf){
	struct trapframe *child_tf = malloc(sizeof(struct trapframe));
	struct addrspace *child_addrspace = malloc(struct addrspace);

	//look for copy function for trapframes
	//copyin or copyout or memcpy?

	struct thread *child_thread = thread_fork("child thread", parent_tf, child_tf, md_forkentry, NULL);
	child_thread->ppid = curthread->pid;

	as_copy(curthread->t_vmspace, child_thread->t_vmspace);

	as_activate(child_thread->t_vmspace);
	mips_usermode(child_tf);
}
