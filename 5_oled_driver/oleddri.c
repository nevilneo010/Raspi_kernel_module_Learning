#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEVIL");
MODULE_DESCRIPTION("A Oled driver for Learning purpose");

/* Defines */
#define DRIVER_NAME "ssd1306"
#define DRIVER_CLASS "ssd1306Class"


/* variable for device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;


/* Variables for i2c */
static struct i2c_adapter * ssd1306_i2c_adapter = NULL;
static struct i2c_client * ssd1306_i2c_client = NULL;
#define I2C_BUS_AVAILABLE 1
#define SLAVE_DEVICE_NAME "SSD1306"
#define SSD1306_SLAVE_ADDR 0x3C

static const struct i2c_device_id ssd_id[] =  {
	{ SLAVE_DEVICE_NAME, 0},
	{ }
};

static struct i2c_driver ssd_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};

struct ssd_1306 {
	u8 width;
	u8 height;
	u8 page_size;
	u8 *displayRam;
}oled;


static struct i2c_board_info ssd_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, SSD1306_SLAVE_ADDR) 
};


s32 ssd_send_byte(u8 controlbyte,u8 data) {
	return i2c_smbus_write_byte_data(ssd1306_i2c_client,controlbyte,data);
	 
}


s32 ssd_send_command(u8 data) {
	return ssd_send_byte(0x00,data);

}

s32 ssd_send_data(u8 data) {
	return ssd_send_byte(0x40,data);
}

void ssd_clear(void) {
    u16 i  = 1;
    for(i = 0;i < 1024;i++){
 	i2c_smbus_write_byte_data(ssd1306_i2c_client,0x40,0x0);
	  
    }
	ssd_send_command(0x21);	ssd_send_command(0x0);ssd_send_command(0x7F); //Column Address
	ssd_send_command(0x22);	ssd_send_command(0x00);ssd_send_command(0x07);//vertical Address
}


void ssd_draw_hline(int x,int y,int length){
	int i, page_number, line, array_pointer;
	
	if(y>63 || ((x+length)>127))
		return;

	page_number = y / 8;
	array_pointer = (page_number * oled.width) + x;
	line = y % 8;
	for(i=0;i<length;i++){
	oled.displayRam[array_pointer++] = 1<<line;
	}
}

//void ssd_display(void) {
//	int x,y;

//	for(y = 0;y<8;y++) {
//		for(x = 0;x < 128;x++){
//			i2c_smbus_write_byte_data(ssd1306_i2c_client,0x40,display_ram[y][x]);
	//		printk(KERN_CONT " %d", 0xff*display_ram[y][x]);
//		}
//	//printk("\n \r");	
//	}
//}

void ssd_display_test(void) {
	int x,y;	
	int i;
//	for(i = 0;i < 128;i++)
//		oled.displayRam[i] = i;	
	ssd_send_command(0x21);	ssd_send_command(0x0);ssd_send_command(0x7F); //Column Address
	ssd_send_command(0x22);	ssd_send_command(0x00);ssd_send_command(0x07);//vertical Address

	for(y = 0; y < 8; y++) {
		i2c_smbus_write_i2c_block_data(ssd1306_i2c_client,0x40,32,oled.displayRam+(y*oled.width));
		i2c_smbus_write_i2c_block_data(ssd1306_i2c_client,0x40,32,oled.displayRam+32+(y*oled.width));
		i2c_smbus_write_i2c_block_data(ssd1306_i2c_client,0x40,32,oled.displayRam+64+(y*oled.width));
		i2c_smbus_write_i2c_block_data(ssd1306_i2c_client,0x40,32,oled.displayRam+96+(y*oled.width));
}
}

u8 ssd_init(void) {
	oled.height = 8;
	oled.width = 128;
	oled.page_size = 8;
	u8 display_ram[oled.height * oled.width];
	oled.displayRam = display_ram;
	memset(oled.displayRam,0,(oled.height * oled.width));
	ssd_send_command(0xAE);
	ssd_send_command(0xD5);
	ssd_send_command(0x80);
	ssd_send_command(0xA8);
	ssd_send_command(0x3F);
	ssd_send_command(0xD3);
	ssd_send_command(0x0);
	ssd_send_command(0x40);;
	ssd_send_command(0x8D);
	ssd_send_command(0x14);
	ssd_send_command(0x20);
	ssd_send_command(0x0);
	ssd_send_command(0xA1);
	ssd_send_command(0xC8);
	ssd_send_command(0xDA);
	ssd_send_command(0x12);
	ssd_send_command(0x81);
	ssd_send_command(0xCF);
	ssd_send_command(0xD9);
	ssd_send_command(0xF1);
	ssd_send_command(0xDB);
	ssd_send_command(0x40);
	ssd_send_command(0xA4);
	ssd_send_command(0xA6);  	
	int ret = ssd_send_command(0xAF);
	if(ret !=0)
	    return -1;
	ssd_clear();
//	i2c_smbus_write_byte_data(ssd1306_i2c_client,0x40,0xFF);
//	i2c_smbus_write_byte_data(ssd1306_i2c_client,0x18,0x18);
//	i2c_smbus_write_byte_data(ssd1306_i2c_client,0x18,0xFF);
//	i2c_smbus_write_byte_data(ssd1306_i2c_client,0xFF,0x0);    
//	i2c_smbus_write_byte_data(ssd1306_i2c_client,0x40,0xFF);
  
	printk("initiliased \n");
	int loop,random_x,random_y,random_len;
	for(loop=0;loop<300;loop++){
		random_x = get_random_int() % 128;
		random_y = get_random_int() % 64;
	       	random_len = get_random_int() % 10;
		ssd_draw_hline(random_x ,random_y ,random_len );

//		ssd_draw_hline(0 ,0  ,10 );
//		ssd_draw_hline(0 ,1  ,10 );
//		ssd_draw_hline(0 ,2 ,10 );
//		ssd_draw_hline(0 ,3 ,10 );
//		ssd_draw_hline(0 ,4 ,10 );
////		ssd_draw_hline(0 ,5 ,10 );
	ssd_display_test();
}

	return 0;
}
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
/*
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

*/	
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

static int __init device_init(void) {
	printk("device Initialised\n");
	int ret = -1;
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

	ssd1306_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

	if(ssd1306_i2c_adapter != NULL) {
		ssd1306_i2c_client = i2c_new_client_device(ssd1306_i2c_adapter, &ssd_i2c_board_info);
	
		if(ssd1306_i2c_client != NULL) { 
	 		if(i2c_add_driver(&ssd_driver) != -1) 
				ret = 0;
			else
				printk("Cant add ssd1306 driver \n");
		}
		i2c_put_adapter(ssd1306_i2c_adapter);
	}

	printk("BMP280 Driver Added! \n");
	ssd_init();

	return ret;
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev(my_device_nr,DRIVER_NAME);
	return -1;
 }

static void __exit device_exit(void) {
	printk("bye bye i2c\n");
	i2c_unregister_device(ssd1306_i2c_client);
	i2c_del_driver(&ssd_driver);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr,1);
	printk("exiting\n");
}

module_init(device_init);
module_exit(device_exit);
