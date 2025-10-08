#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
// #include <linux/rwlock.h>
#include <linux/rwsem.h>
#include <linux/uacce.h>

// использовал семафоры так как у меня вылетала ошибка адреса при чтении 



static int major = 0;
// static rwlock_t lock;
static struct rw_semaphore lock;
static char test_string[15] = "Hello!\n\0";

static ssize_t read(struct file *fd, char __user *buff, size_t size, loff_t *off){
    size_t rc = 0;
    down_read(&lock);
    // read_lock(&lock);
    printk(KERN_INFO "read: buff=%p, size=%zu, off=%lld, test_string='%s' (len=15)\n", 
           buff, size, *off, test_string);
    rc = simple_read_from_buffer(buff, size, off, test_string, 15);

    printk(KERN_INFO "read: rc=%zd\n", rc);
    up_read(&lock);
    // read_unlock(&lock);
    return rc;
}

static ssize_t write(struct file *fd, const char __user *buff, size_t size, loff_t *off){
    size_t rc = 0;
    if(size > 15){
        return -EINVAL;
    }
    down_write(&lock);
    // write_lock(&lock);
    rc = simple_write_to_buffer(test_string, 15, off, buff, size);
    // write_unlock(&lock);
    up_write(&lock);
    return rc;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read,
    .write = write
};

static int __init start_module(void){
    // rwlock_init(&lock);
    init_rwsem(&lock);
    pr_info("Module loaded !!!\n");
    major = register_chrdev(major, "second_module", &fops);

    if(major < 0){
        return major;
    }
    pr_info("major number: %d\n", major);
    
    return 0;
}

static void __exit end_module(void){
    unregister_chrdev(major, "second_module");
    pr_info("Module unloaded !!!\n");
}

module_init(start_module);
module_exit(end_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Михайлов Виталий");
MODULE_DESCRIPTION("Task for eltex academy");