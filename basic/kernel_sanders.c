//Load with insmod
//Unload with rmmod

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

//Declare variables
static char	*username = "dosh";

//Make the variable a command line argument
module_param(username, charp, 0000);
MODULE_PARM_DESC(username, "The user to give root access");

static int hello(void){
	//Can see output in /var/log/kern.log
	printk(KERN_ALERT "We up in here.\n");
	printk(KERN_ALERT "Username : %s\n", username);
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
