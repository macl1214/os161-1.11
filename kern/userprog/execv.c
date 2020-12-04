/** execv.c */

/*
 * Function: sys_execv()
 *
 */
#include <types.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <lib.h>
#include <addrspace.h>
#include <thread.h>
#include <curthread.h>
#include <vm.h>
#include <vfs.h>
#include <test.h>
#include <string.h>


// argv[] needs to have a null string at the end of array
int get_argc(char* const argv[]){
	int total = 0;

	int i = 0;
	while(strcmp(argv[i], "") != 0){
		i++;
		total++;
	}

	return total;
}

int execv(const char* path, char* const argv[]){
	struct vnode *v;
	vaddr_t entrypoint, stackptr;
	int result;

	result = vfs_open(progname, O_RDONLY, &v);
	if(result){
		return result;
	}

	assert(curthread->t_vmspace == NULL);

	curthread->t_vmspace = as_create();
	if(curthread->t_vmspace == NULL){
		vfs_close(v);
		return ENOMEN;
	}

	as_activate(curthread->t_vmspace);

	//loading the executable
	result = load_elf(v, &entrypoint);
	if(result){
		vfs_close(v);
		return result;
	}

	//done with the file
	vfs_close(v);
	
	//args put somewhere in here??
	//kern/arch/mip/include/pcb.h
	//kern/arch/mips/mips/trap.c
	md_usermode(0 /*argc*/, NULL /*userspace addr of argv*/, stackptr, entrypoint);
	
	panic("md_usermode returned\n");
	return EINVAL;
}
