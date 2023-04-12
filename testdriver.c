#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include <net/sock.h>

MODULE_LICENSE("GPL");
#define DEVICE_NAME "testdriver"
#define EXAMPLE_MSG "My precious!\n"
#define MSG_BUFFER_LEN 13

struct Dog {
        int n;
        unsigned char ch;
};

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int major_num;
static int device_open_count = 0;
static char msg_buffer[MSG_BUFFER_LEN];
static char *msg_ptr;
static int counter = 0;

static struct file_operations file_ops = {.read = device_read,
                                          .write = device_write,
                                          .open = device_open,
                                          .release = device_release};

static ssize_t device_read(struct file *flip, char *buffer, size_t len,
                           loff_t *offset) {
    struct Dog *pDog = NULL;
    int bytes_read = 0;
    printk(KERN_ALERT "** READ OPS detected[%d] ***\n", counter);
    counter++;
    if (*msg_ptr == 0)
        msg_ptr = msg_buffer;
    while (len && *msg_ptr) {
        put_user(*(msg_ptr++), buffer++);
        len--;
        bytes_read++;
    }

    pDog = kmalloc(sizeof(struct Dog), GFP_KERNEL);
    if (pDog) {
        printk(KERN_ALERT "--- struct Dog successfully allocated ---\n");
        kfree(pDog);
    } else {
        printk(KERN_ALERT "--- struct Dog failed allocation ---\n");
    }

    return bytes_read;
}

static ssize_t device_write(struct file *flip, const char *buffer, size_t len,
                            loff_t *offset) {
    printk(KERN_ALERT "This operation is not supported.\n");
    return -EINVAL;
}

static int device_open(struct inode *inode, struct file *file) {
    if (device_open_count)
        return -EBUSY;
    device_open_count++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    device_open_count--;
    module_put(THIS_MODULE);
    return 0;
}

static int __init testdriver_init(void) {
    strncpy(msg_buffer, EXAMPLE_MSG, MSG_BUFFER_LEN);
    msg_ptr = msg_buffer;
    major_num = register_chrdev(0, "testdriver", &file_ops);
    if (major_num < 0) {
        printk(KERN_ALERT "Could not register device : % d\n", major_num);
        return major_num;
    } else {
        printk(KERN_INFO
               "testdriver module loaded with device major number % d\n",
               major_num);
        return 0;
    }
}

static void __exit testdriver_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Goodbye, testdriver !\n");
}

module_init(testdriver_init);
module_exit(testdriver_exit);
