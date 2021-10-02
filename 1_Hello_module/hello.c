#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEVIL");
MODULE_DESCRIPTION("HELLO WORKD LKM");

static int __init initModule(void) {
	printk("HELLO WORLD from linux Kernel \n");
	return 0;

}

static  void __exit finished(void) {
	printk("Good Bye\n");


}

module_init(initModule);
module_exit(finished);
