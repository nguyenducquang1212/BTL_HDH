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
	{ 0xf9a482f9, "msleep" },
	{ 0xd002b257, "i2c_del_driver" },
	{ 0xfff5afc, "time64_to_tm" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xc2c70f41, "i2c_put_adapter" },
	{ 0xb7e479f7, "kthread_create_on_node" },
	{ 0x33737f91, "i2c_new_client_device" },
	{ 0xc5850110, "printk" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0x3320a004, "i2c_unregister_device" },
	{ 0xb7a49f4a, "i2c_register_driver" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xe8f3ec17, "wake_up_process" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xfaa9b28e, "i2c_transfer_buffer_flags" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xc8d5ec7e, "i2c_get_adapter" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:ETX_RTC");

MODULE_INFO(srcversion, "42338ECEBFA7BBFA6203A57");
