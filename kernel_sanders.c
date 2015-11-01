//Load with insmod
//Unload with rmmod

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello(void){
	//Can see output in /var/log/kern.log
	printk(KERN_ALERT "We up in here.\n");
	return 0;
}

static void outro(void){
	printk(KERN_ALERT "We out.\n");
}

//Every kernel needs an init function and exit
module_init(hello);
module_exit(outro);

MODULE_AUTHOR("The Dosh");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Creepin");