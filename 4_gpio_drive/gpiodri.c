#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEVIL");
MODULE_DESCRIPTION("A gpio driver to turn on and off a led");

/**
 * @buffer for data
 */
//static char buffer[255];
//static char buffer_pointer;

/* variable for device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

/**
 * @brief funtion to be called when device is opened
 */
static int device_open(struct inode *device_file, struct file *instance) {
	printk("device open \n");
	return 0;
}

/**
 * @brief funtion to be called when data is read from buffer
 */
static ssize_t driver_read(struct file *File,char *user_buffer, size_t count,loff_t *offs) {
	int to_copy,not_copied,delta;
	char tmp[3] = " \n";
	to_copy = min(count, sizeof(tmp));
	tmp[0] = gpio_get_value(4) + '0';
	not_copied = copy_to_user(user_buffer, &tmp, to_copy);
	delta = to_copy - not_copied;
	printk("Read Driver");
	return delta;	  
}


/**
 * @brief funtion to be called when data is write to  buffer
 */
static ssize_t driver_write(struct file *File,const char *user_buffer, size_t count,loff_t *offs) {
	int to_copy,not_copied,delta;
	char input;
	to_copy = min(count, sizeof(input));
	not_copied = copy_from_user(&input, user_buffer, to_copy);

	switch (input){
		case '0':
			gpio_set_value(4,0);
			printk("gpio 4 turned off");
			break;
		case '1':
			gpio_set_value(4,1);
			printk("gpio 4 turned on");
			break;
		default:
			printk("invalid input");
	}

	
	delta = to_copy - not_copied;
	printk("Write Driver");
	return delta;	  
}


/**
 * @brief funtion to be called when device is closed
 */
static int device_close(struct inode *device_file, struct file *instance) {
	printk("device closed \n");
	return 0;
}

struct file_operations ops = {
	.owner   = THIS_MODULE,
	.open    = device_open,
	.release = device_close,
	.read    = driver_read,
	.write   = driver_write
};

#define DRIVER_NAME "my_driver"
#define DRIVER_CLASS "my_module_class"
static int __init device_init(void) {
	printk("device Initialised\n");
	
	if (alloc_chrdev_region(&my_device_nr, 0,1, DRIVER_NAME) < 0) {
		printk("device nr could not be allocated !\n");
		return -1;
	}
	printk("read_write -device nr Major %d Minor %d \n",my_device_nr >> 20, my_device_nr & 0xfffff);

	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) ==NULL) {
		printk("device class not created! \n");
		goto ClassError;
	}

	if(device_create(my_class, NULL,my_device_nr, NULL, DRIVER_NAME) ==NULL){
		printk("Can not create device file!\n");
		goto FileError;
	}

	cdev_init(&my_device, &ops);

	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel Failerd \n");
		goto AddError;
	}
	if(gpio_request(4,"rpi-gpio-request")) {
		printk("GPIO 4 not free");
		goto AddError; 		
	}

	if(gpio_direction_output(4, 0)) {
		printk("can not set 4 as output");
		goto Gpio4Error;
	}
	return 0;
Gpio4Error:
	gpio_free(4);
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev(my_device_nr,DRIVER_NAME);
	return -1;
 }

static void __exit device_exit(void) {
	gpio_set_value(4, 0);
	gpio_free(4);
	printk("unregistering device\n");
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev(my_device_nr,DRIVER_NAME);
	printk("exiting\n");
}

module_init(device_init);
module_exit(device_exit);
