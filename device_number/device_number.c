#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEVIL");
MODULE_DESCRIPTION("learning device number");

/**
 * @brief driver open
 */
static int driver_open(struct inode *device_file,struct file *instance) {

	printk("device opened\n");
	return 0;

}


/**
 * @brief driver close
 */
static int driver_close(struct inode *device_file,struct file *instance) {

	printk("device close\n");
	return 0;

}


	
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};

#define MYMAJOR 90

static int __init device_init(void) {
	int retval;
	printk("device Initiated");
	retval = register_chrdev(MYMAJOR,"device number Testing",&fops);
	if(retval == 0)
		printk("device opened with Major %d Minor %d\n",MYMAJOR,0);
	else if(retval > 0)
		printk("device opened with Major %d minor %d\n",retval>>20,retval&0xfffff);
	else { 
		printk("couldnt open device");
		return -1;
	}
	return 0;
}

static void __exit device_exit(void) {
	unregister_chrdev(MYMAJOR,"device number Testing");
	printk("device exited\n");
}

module_init(device_init);
module_exit(device_exit);
