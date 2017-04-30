/******************************************************************************
 * copyright (c)2017 Rhomb  - All rights reserved.
 *
 * This software is authored by Rhomb and is Rhomb'
 * intelletual property,including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by Rhomb.
 *
 * This file may not be distributed, copied or reproduced in any manner,
 * electronic or otherwise, without the written consent of Rhomb.
 *
 * This file contains defination of GPIO driver APIs which can be called from
 * kernelspace or userspace.
 ******************************************************************************/

/******************************************************************************
 *
 * File Name   :  user_gpio.c
 *
 * Description :  This C program implement following:
 *                   -  IOCTL to set, reset GPIO Pins
 *                   -  IOCTL to set direction of pins as input or output
 *
 * History     :  April/24/2017, Android Linux Media, Created the file.
 *
 *******************************************************************************/

/******************
 *  Include Files
 ******************/
#include      "user_gpio.h"

/******************
 *  Defines
 ******************/
#define DIRECTION_OUTPUT 	1
#define DIRECTION_INPUT  	0
#define DEFAULT_VALUE           1
/************************
 *      Functions
 ************************/
static struct file_operations gpio_fops = {
	.owner    = THIS_MODULE,
	.read     = gpio_read,
	.write    = NULL,
	.unlocked_ioctl  = gpio_ioctl,
	.open     = gpio_open,
	.release  = NULL,
};

#define GPIO_MINOR      123

static struct miscdevice misc_gpiodev = {
	GPIO_MINOR,
	"usr_gpio",
	&gpio_fops
};

/*******************************************************************************
 * Function Name      :     gpio_open
 *
 * Description        :     Defines what to do when device is opened
 *
 * Parameters         :     struct inode *inode
 *                          [in] device inode descriptor
 *                          struct file *filp
 *                          [in] device file descriptor
 *
 * Return Value       :     int - success(0) or falure(-1)
 *
 ******************************************************************************/
static int gpio_open(struct inode *inode, struct file *filp)
{
	debug_print1("\n\nEntered gpio_open\n\n");
	return SUCCESS;
}

/*******************************************************************************
 *
 * Function Name      :       gpio_read
 *
 * Description        :       Stub function
 *
 * Parameters         :       struct file *filp
 *                            [in] device inode descriptor
 *                            char * buff
 *                            [out] buffer to hold the contents read
 *                            size_t count
 *                            [in] read count
 *                            loff_t *f_pos
 *                            [in] start offset position
 *
 * Return Value       :       int 0
 *
 ******************************************************************************/
static ssize_t gpio_read (struct file *filp, char *buff, size_t count,
		loff_t *f_pos)
{
	debug_print1("READ: entered...\n");
	return SUCCESS;
}

/*******************************************************************************
 *
 * Function Name      :     gpio_ioctl
 *
 * Description        :     Definitions of the Commands
 *
 * Parameters         :     struct inode *inode
 *                          [in] device inode descriptor
 *                          struct file *filp
 *                          [in] device file descriptor
 *                          unsigned int cmd
 *                          [in] command from user
 *                          unsigned long arg
 *                          [in] args from/to user
 *
 * Return Value       :     On success zero is retured
 *
 ******************************************************************************/
static long gpio_ioctl (struct file *flip,
		unsigned int cmd, unsigned long arg)
{
	uint32_t gpio_pin;
	int32_t	retval = 0;
	gpio_arg_t   gpioarg;

	debug_print1("IOCTL: entered...\n");

	/* Before decoding check for correctness of cmd */
	if (_IOC_TYPE(cmd) != GPIO_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > GPIO_IOC_MAXNR) return -ENOTTY;

	/* Verify accesses */
	if (_IOC_DIR(cmd) & _IOC_READ)
		retval = !access_ok(VERIFY_WRITE, (void  *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		retval =  !access_ok(VERIFY_READ, (void  *)arg, _IOC_SIZE(cmd));
	if (retval) return -1;          /*error in access*/

	debug_print1("IOCTL: Access_OK\n");

	if ( (retval = __get_user(gpio_pin, (uint32_t *)arg)) < 0)
	{
		debug_print1("Error:  in __get_user in gpio_ei_ioctl\n" );
		return -EINVAL;
	}
	gpio_request(gpio_pin, "test_gpio");
	switch(cmd)
	{
		case GPIO_GET_VALUE:
			memset(&gpioarg, 0, sizeof(gpio_arg_t));

			/* Get user specified Argument */
			if(copy_from_user(&gpioarg, (gpio_arg_t *)arg,
						sizeof(gpio_arg_t)))
				return -EFAULT;

			gpioarg.value = gpio_get_value(gpioarg.gpio);
			if(copy_to_user((gpio_arg_t *) arg, &gpioarg,
						sizeof(gpio_arg_t)))
				return -EFAULT;

			break;

		case GPIO_SET_VALUE:
			memset(&gpioarg, 0, sizeof(gpio_arg_t));

			/* Get user specified Argument */
			if(copy_from_user(&gpioarg, (gpio_arg_t *)arg,
						sizeof(gpio_arg_t)))
				return -EFAULT;

			gpio_direction_output(gpioarg.gpio, DEFAULT_VALUE);
			gpio_set_value(gpioarg.gpio, gpioarg.value);
			break;

		case GPIO_SET_DIRECTION:
			memset(&gpioarg, 0, sizeof(gpio_arg_t));

			/* Get user specified Argument */
			if(copy_from_user(&gpioarg, (gpio_arg_t *)arg,
						sizeof(gpio_arg_t)))
				return -EFAULT;

			if(DIRECTION_INPUT == gpioarg.value)
				retval = gpio_direction_input(gpioarg.gpio);
			else if(DIRECTION_OUTPUT == gpioarg.value)
				retval = gpio_direction_output(gpioarg.gpio,1);
			break;

		default:
			debug_print2("ERROR: Wrong command\n");
			return -EOPNOTSUPP;
	}
	gpio_free(gpio_pin);
	return retval;
}

/*******************************************************************************
 *
 * Function Name      :       gpio_init
 *
 * Description        :       Allocates MAJOR MINOR number of device
 *                            This is called on "insmod" command
 *
 * Parameters         :       void
 *
 * Return Value       :       Returns 0 on success and -ve value on failure
 *
 ******************************************************************************/
static int __init gpio_init(void)
{
	int ret;
	ret = misc_register(&misc_gpiodev);
	if (ret)
	{
		printk(KERN_WARNING "Unable to register se-gpio device\n");
		return ret;
	}
	return SUCCESS;
}


/*******************************************************************************
 *
 * Function Name      :       gpio_exit
 *
 * Description        :       Cleanup routine when device is closed
 *                            This is called on "rmmod" command
 *
 * Parameters         :       void
 *
 * Return Value       :       void
 *
 ******************************************************************************/
static void __exit gpio_exit(void)
{
	misc_deregister(&misc_gpiodev);
	debug_print1("gpio_exit done\n");
}

module_init(gpio_init);
module_exit(gpio_exit);

/* Module information */
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/******************************************************************************
 * Copyright (c)2017 Rhomb - All rights reserved.
 *
 * This software is authored by Rhomb and is Rhomb'
 * intelletual property,including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by Rhomb.
 *
 * This file may not be distributed, copied or reproduced in any manner,
 * electronic or otherwise, without the written consent of Rhomb.
 ******************************************************************************/
