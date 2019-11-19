#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>        // file ops
#include <linux/cdev.h>      // for cdev, (character drivers)
#include <linux/semaphore.h> // for semaphores; makes device syncronous
#include <linux/uaccess.h>   //copy to user;

#define DEVICE_SIZE 200

// Fake device struc
struct fake_device
{
    char data[DEVICE_SIZE];
    struct semaphore sem;
} virtual_dev; // Stands for "virtual device "

// Important variables

struct cdev *mcdev; // "my character device"
int major_number;   // stores major number
int ret;            // hold return values
dev_t dev_num;      // Holds najor number given by the kernel

#define DEVICE_NAME "myCharDevice" // name found in /proc/devices

/*
* Called when opening device
* inode is a file reference with its important info.
* flip is an abstract opened file
*/
int device_open(struct inode *inode, struct file *flip)
{
    /*
    * Allow only 1 process to open device
    * using semaphore as a  mutext (which is short for mutual exclusive lock)
    */
    if (down_interruptible(&virtual_dev.sem) != 0)
    {
        printk(KERN_ALERT "myCharDevice: couldn't lock device during open");
        return -1;
    }

    printk(KERN_INFO "myCharDevice: Opened device");
    return 0;
}

// Called when the user wants to read the device
ssize_t device_read(struct file *filp, char *dataBuffer, size_t bufCount, loff_t *curOffset)
{
    printk(KERN_INFO "myCharDevice: Reading from device");
    ret = copy_to_user(dataBuffer, virtual_dev.data, bufCount);
    return ret;
}

// Called when the user wants to write to the device
ssize_t device_write(struct file *filp, const char *dataBuffer, size_t bufCount, loff_t *curOffset)
{
    // send data from user to kernel
    if (bufCount >= DEVICE_SIZE) // buff size check to avoid memory leak
        bufCount = DEVICE_SIZE;
    printk(KERN_INFO "myCharDevice: Writing to device");
    ret = copy_from_user(virtual_dev.data, dataBuffer, bufCount);
    return ret;
}

// Called when user closes the device
int device_close(struct inode *inode, struct file *flip)
{
    // Release mutext obtained when device open allowing other processes to access it
    up(&virtual_dev.sem);
    printk(KERN_INFO "myCharDevice: Closed device");
    return 0;
}

/* 
* Tells kernel what to call when the user operates on our device file.
*/
struct file_operations fops = {
    .owner = THIS_MODULE,    // Prevents module from being unloaded when operation going on
    .open = device_open,     // function pointer for device open
    .release = device_close, // function pointer for device close
    .write = device_write,   // function pointer for device write
    .read = device_read      // function pointer for device read
};

static int __init driver_entry(void)
{
    // Register device driver
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
    {
        printk(KERN_ALERT "myCharDevice: failed to allocate a major number");
        return ret;
    }
    major_number = MAJOR(dev_num);
    printk(KERN_INFO "myCharDevice: major number == %d", major_number);
    printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" to create our device file", DEVICE_NAME, major_number);

    mcdev = cdev_alloc(); // Initialize cdev structure
    mcdev->ops = &fops;   // Assignes file operations to it
    mcdev->owner = THIS_MODULE;
    ret = cdev_add(mcdev, dev_num, 1); // add cdev to kernel since
    if (ret < 0)
    {
        printk(KERN_ALERT "myCharDevice: unable to add cdev to kernel");
        return ret;
    }
    // Init our semaphore with a value of 1
    sema_init(&virtual_dev.sem, 1);
    return 0;
}

static void __exit driver_exit(void)
{
    // unregister everything (must be in reverse order)
    cdev_del(mcdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ALERT "myCharDevice: unallocated module");
}

// Module initialization and exit
module_init(driver_entry);
module_exit(driver_exit);

// Module info
MODULE_LICENSE("MIT");
MODULE_AUTHOR("Oren Ben-Meir");
MODULE_VERSION("1:1.0");
MODULE_DESCRIPTION("Driver for a fake character device.");
