#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/random.h>
#include <linux/random.h>
#include <linux/uaccess.h>

static dev_t device ;  // variable for device number
static dev_t varx;
static dev_t vary ;
static dev_t varz ;
static struct cdev c_devx;
static struct class *clsx;
static struct cdev c_devy;
//static struct class *clsy;
static struct cdev c_devz;
//static struct class *clsz;
uint16_t val;


uint16_t getrandval(void){
	uint16_t randval;
	get_random_bytes(&randval, 2);
	return randval;
}



uint16_t cb_funct(void)    // callback function.
{
    int rand;
    get_random_bytes(&rand, sizeof(rand));
    rand%=250;

    //seq_printf(m, "random number : %d\n", rand);
    //...
 return rand;
}



//driver callback func  -- step4

static int accx_open(struct inode *i, struct file *f)

{
printk(KERN_INFO "accx: open()\n");
return 0;
}

static int accx_close(struct inode *i, struct file *f)

{
printk(KERN_INFO "accx: close()\n");
return 0;
}

//static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
//{
//  printk(KERN_INFO "mychar: read()\n");  
//return 0;   
//}

static ssize_t accx_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "accx:read()\n");
val=getrandval()&0x3ff;
printk(KERN_INFO "%d\n",val);
copy_to_user(buf, &val, 2);
return 0;
}



static int accy_open(struct inode *i, struct file *f)

{
printk(KERN_INFO "accy: open()\n");
return 0;
}

static int accy_close(struct inode *i, struct file *f)

{
printk(KERN_INFO "accy: close()\n");
return 0;
}


static ssize_t accy_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "accy:read()\n");
val=getrandval()&0x3ff;
printk(KERN_INFO "%d\n",val);
copy_to_user(buf, &val, 2);
return 0;
}


static int accz_open(struct inode *i, struct file *f)

{
printk(KERN_INFO "accz: open()\n");
return 0;
}

static int accz_close(struct inode *i, struct file *f)

{
printk(KERN_INFO "accz: close()\n");
return 0;
}

static ssize_t accz_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "accz:read()\n");
val=getrandval()&0x3ff;
printk(KERN_INFO "%d\n",val);
copy_to_user(buf, &val, 2);
return 0;
}



static ssize_t accz_write(struct file *f, const char __user *buf,
  size_t len, loff_t *off)
{
  printk(KERN_INFO "Driver: write()\n");
  return len;
}

static struct file_operations fops =
{
  .owner = THIS_MODULE,
  .open = accx_open,
  .release = accx_close,
  .read = accx_read,
  //.write = accx_write
};
static struct file_operations fops1 =
{
  .owner = THIS_MODULE,
  .open = accy_open,
  .release = accy_close,
  .read = accy_read,
  //.write = accy_write
};
static struct file_operations fops2 =
{
  .owner = THIS_MODULE,
  .open = accz_open,
  .release = accz_close,
  .read = accz_read,
  .write = accz_write
};


 

static int __init mychar_init(void)
{
    printk(KERN_INFO "mychar registered\n\n");

//reserve major and minor number - step1
    if(alloc_chrdev_region(&device, 1, 3, "BITS-PILANI") < 0)
    {
      return -1;
    }

        varx=MKDEV(MAJOR(device), MINOR(device)+0);
	vary=MKDEV(MAJOR(device), MINOR(device)+1);
	varz=MKDEV(MAJOR(device), MINOR(device)+2);


//reserve major and minor number - step1
  //  if(alloc_chrdev_region(&vary, 0, 3, "BITS-PILANI") < 0)
  //  {
  //    return -1;
   // }

if((clsx = class_create(THIS_MODULE,"chardevx")) == NULL)
{
unregister_chrdev_region(device, 3);
return -1;
}
if(device_create(clsx, NULL, varx, NULL, "adxl_x") == NULL)
{
class_destroy(clsx);
unregister_chrdev_region(varx, 1);
return -1;
}

//if((clsy = class_create(THIS_MODULE,"chardevy")) == NULL)
//{
//unregister_chrdev_region(vary, 1);
//return -1;
//}
if(device_create(clsx, NULL, vary, NULL, "adxl_y") == NULL)
{
class_destroy(clsx);
unregister_chrdev_region(vary, 1);
return -1;
}

//if((clsz = class_create(THIS_MODULE,"chardevz")) == NULL)
//{
//unregister_chrdev_region(varz, 1);
///return -1;
//}
if(device_create(clsx, NULL, varz, NULL, "adxl_z") == NULL)
{
class_destroy(clsx);
unregister_chrdev_region(varz, 1);
return -1;
}

//step3 - link fops and cdev to device to the device node

cdev_init(&c_devx, &fops);
if(cdev_add(&c_devx, varx, 1) == -1)
{
 device_destroy(clsx, varx);
  class_destroy(clsx);
unregister_chrdev_region(varx, 1);
return -1;

}

cdev_init(&c_devy, &fops1);
if(cdev_add(&c_devy, vary, 1) == -1)
{
 device_destroy(clsx, vary);
  class_destroy(clsx);
unregister_chrdev_region(vary, 1);
return -1;

}

cdev_init(&c_devz, &fops2);
if(cdev_add(&c_devz, varz, 1) == -1)
{
 device_destroy(clsx, varz);
  class_destroy(clsx);
unregister_chrdev_region(varz, 1);
return -1;

}
return 0;
}






static void __exit mychar_exit(void) 
{
cdev_del(&c_devx);
cdev_del(&c_devy);
cdev_del(&c_devz);
device_destroy(clsx, varx);
device_destroy(clsx, vary);
device_destroy(clsx, varz);
  class_destroy(clsx);
unregister_chrdev_region(varx, 1);
printk(KERN_INFO "mychar unregistered\n\n");
}


module_init(mychar_init);
module_exit(mychar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("anurag gupta");
MODULE_DESCRIPTION("FIRST CHAR DRIVER");
