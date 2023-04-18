#include <linux/module.h>
#include <net/sock.h>

MODULE_LICENSE("GPL");
#define DEVICE_NAME "testdriver"
#define EXAMPLE_MSG "My precious!\n"
#define MSG_BUFFER_LEN 13

static int __init testdriver_init(void) {
    return 0;
}

static void __exit testdriver_exit(void) {
}

module_init(testdriver_init);
module_exit(testdriver_exit);
