/*
	Make with Makefile, load with insmod.
	Can see output with dmesg | tail -4
	Right to file with echo "message" > /proc/simpleproc
	Read file with cat /proc/simpleproc
	Remove with rmmod
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm-generic/uaccess.h>

static char message[128];
static int len = 0;
static int len_check = 1;

//Open the proc
int simple_proc_open(struct inode * sp_inode, struct file *sp_file){
	printk(KERN_ALERT "called open\n");
	return 0;
}

//Release the proc
int simple_proc_release(struct inode *sp_inode, struct file *sp_file){
	printk(KERN_ALERT "called release\n");
	return 0;
}

//Read the file
int simple_proc_read(struct file *sp_file, char __user *buf, size_t size, loff_t *offset){
	//Reads the file when cat is called
	if(len_check){
		len_check = 0;
	}else{
		len_check = 1;
		return 0;
	}
	printk(KERN_ALERT "called read %zu\n", size);
	copy_to_user(buf, message, len);
	return len;
}

//Write to file
int simple_proc_write(struct file *sp_file, const char __user *buf, size_t size, loff_t *offset){
	printk(KERN_ALERT "called write\n");
	len = size;
	copy_from_user(message, buf, len);
	return len;
}

//Assign functions to file
struct file_operations fops = {
	.open = simple_proc_open,
	.read = simple_proc_read,
	.write = simple_proc_write,
	.release = simple_proc_release
};

//Start function
static int __init init_simpleproc(void){
	printk(KERN_ALERT "startin da proc\n");
	if(!proc_create("simpleproc", 0666, NULL, &fops)){
		printk(KERN_ALERT "Error creating\n");
		remove_proc_entry("simpleproc", NULL);
		return -1;
	}
	return 0;
}

//Exit function
static void __exit exit_simpleproc(void){
	remove_proc_entry("simpleproc", NULL);
	printk(KERN_ALERT "leavin da proc\n");
}

module_init(init_simpleproc);
module_exit(exit_simpleproc);

MODULE_AUTHOR("The Dosh");
MODULE_LICENSE("GPL v3");
MODULE_DESCRIPTION("Testing input & output of proc files");
