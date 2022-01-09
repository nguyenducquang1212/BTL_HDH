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
	{ 0xbd4a4d5c, "module_layout" },
	{ 0xd002b257, "i2c_del_driver" },
	{ 0x3320a004, "i2c_unregister_device" },
	{ 0xe8f3ec17, "wake_up_process" },
	{ 0xb7e479f7, "kthread_create_on_node" },
	{ 0xc2c70f41, "i2c_put_adapter" },
	{ 0xb7a49f4a, "i2c_register_driver" },
	{ 0x33737f91, "i2c_new_client_device" },
	{ 0xc8d5ec7e, "i2c_get_adapter" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x83228fb0, "ds" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x97255bdf, "strlen" },
	{ 0xc5850110, "printk" },
	{ 0xf9a482f9, "msleep" },
	{ 0x9d669763, "memcpy" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xfaa9b28e, "i2c_transfer_buffer_flags" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "ds1307");

MODULE_ALIAS("i2c:ETX_OLED");

MODULE_INFO(srcversion, "A65EB1442036D01A7B9C65A");
