#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <asm/errno.h>
#include <linux/string.h>
#include <linux/uidgid.h>

asmlinkage long sys_log710a2017as2(const struct procdata __user *pudata) {
	
	// pudata cannot be null
	if(!pudata) {
		return -EFAULT;
	}

	// Get process informations
	struct procdata kdata;
	
	kdata.state = current->state;
	kdata.pid = current->pid;
	kdata.parent_pid = current->parent->pid;
	kdata.uid = __kuid_val(current->cred->uid);
	strcpy(kdata.comm, current->comm);
	
	// Copy data from kernel to user
	if(copy_to_user(pudata, &kdata, sizeof kdata)){
		return -EFAULT;
	}

	return 0;
}
