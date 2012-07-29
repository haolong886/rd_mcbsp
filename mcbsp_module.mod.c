#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x42c712ef, "module_layout" },
	{ 0x7efa5d4d, "cdev_del" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xaa3e23b1, "cdev_init" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x1a9df6cc, "malloc_sizes" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xc3fd4289, "device_destroy" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x956a91ba, "gpio_get_value_cansleep" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x3441c3d6, "gpio_set_value_cansleep" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xea147363, "printk" },
	{ 0xef9d09e1, "fasync_helper" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x3b080c0d, "device_create" },
	{ 0x859c6dc7, "request_threaded_irq" },
	{ 0xa61e4362, "omap_request_dma" },
	{ 0xe4dace45, "cdev_add" },
	{ 0xbb4f6c53, "kmem_cache_alloc" },
	{ 0xe9ce8b95, "omap_ioremap" },
	{ 0x15331242, "omap_iounmap" },
	{ 0xfe990052, "gpio_free" },
	{ 0x37a0cba, "kfree" },
	{ 0x8cd8c339, "omap_free_dma" },
	{ 0x6128b5fc, "__printk_ratelimit" },
	{ 0x36916f12, "class_destroy" },
	{ 0x4dd231a9, "kill_fasync" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xdaee8348, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xf20dabd8, "free_irq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "BD95F24C10247EF2C1C09AB");
