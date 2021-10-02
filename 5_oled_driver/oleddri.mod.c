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
	{ 0x3364d393, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x80a1a9e4, "cdev_del" },
	{ 0x6f2d808c, "i2c_del_driver" },
	{ 0x938358f4, "i2c_unregister_device" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x501e0e43, "class_destroy" },
	{ 0xd3686b90, "i2c_put_adapter" },
	{ 0x3388efe0, "i2c_register_driver" },
	{ 0xba3dfa7e, "i2c_new_client_device" },
	{ 0xe98a2381, "i2c_get_adapter" },
	{ 0x3d5f7e24, "device_destroy" },
	{ 0x408bae9a, "cdev_add" },
	{ 0xd8135e1a, "cdev_init" },
	{ 0xea9b5888, "device_create" },
	{ 0x32e12e8, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xd36dc10c, "get_random_u32" },
	{ 0x826a131b, "i2c_smbus_write_byte_data" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xc959d152, "__stack_chk_fail" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "64BD948D700790D72F61740");
