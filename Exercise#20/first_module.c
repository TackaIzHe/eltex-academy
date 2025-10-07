#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init start_module(void){
    pr_info("Module loaded !!!\n");
    return 0;
}

static void __exit end_module(void){
    pr_info("Module unloaded !!!\n");
}

module_init(start_module);
module_exit(end_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Михайлов Виталий");
MODULE_DESCRIPTION("Task for eltex academy");