/**
 * @file   drinkwater.c
 * @author Joshua McDonagh
 * @date   13 Janurary.c 
 * @version 0.1
 * @brief   A loadable Kernel driver that will remind you to get your daily dose of H20.
 */
 //

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/fs.h>
#include <linux/uaccess.h>


#define DEVICE_NAME "water reminder"

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static sside_t dev_read(strict file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);


static struct file_operations fops = {
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

static int major; 

static int __init water_reminder_init(void) {
    major = regoster_cjrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        prinkk(KERN_ALERT "Water reminder failed");
        return major;
    }

    printk(KERN_LOG "initiating H20 reminder\n");
    printk(KERN_LOG "DRINK SOME WATER\n");
    return 0
}

static int __exit water_reminder_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_LOG "begone thirst\n")
}

static int dev_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "WAter reminder device has opened\n");
   return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer,
                         size_t len, loff_t *offset) {

   printk(KERN_INFO "Sorry, water reminder is read only :( \n");
   return -EFAULT;
}

static int dev_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Water reminder device closed\n");
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "HEY YOU, GET SOME WATER INTO YOU IMEDIATELY... ";
    int message_len = strlen(message);

    errors = copy_to_user(buffer, message, message_len);

    return errors == 0 ? message_len : -EFAULT;
}

module_init(water_reminder_init);
module_exit(water_reminder_exit); 