#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xa11440c8, "module_layout" },
	{ 0x7a39daf9, "cdev_del" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x5b6dfd24, "class_destroy" },
	{ 0x9dd4af8d, "device_destroy" },
	{ 0xfe990052, "gpio_free" },
	{ 0xd5afb096, "gpiod_direction_output_raw" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x2686255, "cdev_add" },
	{ 0x1eacc803, "cdev_init" },
	{ 0x4060a0c4, "device_create" },
	{ 0x49d2824e, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xc4a6c161, "gpiod_get_raw_value" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x5f754e5a, "memset" },
	{ 0xc2541988, "gpiod_set_raw_value" },
	{ 0xbcc6946b, "gpio_to_desc" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7DABC2147F68F6927A5164F");
