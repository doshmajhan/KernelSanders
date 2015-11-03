#include <linux/linkage.h>
#include <asm/uaccess.h>
asmlinkage long sys_syscall(char __user *buf, int len){
	char message[200];
	if(strlen_user(buf) > 200){
		return -EINVAL;
	}
	copy_from_user(message, buf, strlen_user(buf));
	printk("syscall: %s\n", message);
	copy_to_user(buf, "It's alive", strlen("It's alive") + 1);
	return strlen("It's alive")+1;
}
