/*******************************************************************************
* Copyright (c)2017 Rhomb - All rights reserved.
*
* This software is authored by Rhomb and is Rhomb'
* intelletual property,including the copyrights in all countries in the world.
* This software is provided under a license to use only with all other rights,
* including ownership rights, being retained by Rhomb.
*
* This file may not be distributed, copied or reproduced in any manner,
* electronic or otherwise, without the written consent of Rhomb.
*
* This file contains declaration of APIs used in kernel space GPIO driver.
*******************************************************************************/

/******************************************************************************
*
* File Name   :  user_gpio.h
*
* Description :  This is a C source code header file for gpio driver for
*                LU600 IMX6Q based core card.
*
* History     :  April/21/2017, Android Linux Media, Created the file.
*
*******************************************************************************/

#ifndef _USER_GPIO_H
#define _USER_GPIO_H

/******************
 *  Include Files
 ******************/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <linux/types.h>
#include <asm/uaccess.h>

#include <linux/moduleparam.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_reg.h>
#include <linux/serial_core.h>
#include <linux/serial.h>

#include <asm/gpio.h>
#include <asm/irq.h>
#include <linux/miscdevice.h>

#include <asm/user_gpio_app.h>

/*********************************
 * Defines and Macros and globals
 *********************************/

#define DRIVER_AUTHOR "Android Linux Media (android.linuxmedia@gmail.com)"
#define DRIVER_DESC "GPIO driver"

#define SUCCESS 0

/* Enables or disables debug output */
#ifdef __DEBUG
#define	debug_print1(x...) printk(KERN_ALERT "GPIO: " x)
#define	debug_print2(x...) printk(KERN_EMERG "GPIO: " x)
#else
#define debug_print1(args...)
#define debug_print2(args...)
#endif

/*********************************
 * Typedefs and Structs and Enums
 *********************************/

/************************
 * Function Declarations
 ************************/

/* This function readys the gpio controller */
static int gpio_open(struct inode *inode, struct file *filp);

/* This is a stub function as of now */
static ssize_t gpio_read(struct file *filp, char *buff, size_t count,
                         loff_t *f_pos );

/* This function implements the various features of gpio controller */
static long gpio_ioctl(struct file *flip,
                      unsigned int cmd, unsigned long arg);

/* This function initializes the gpio controller */
static int __init gpio_init(void);

/* This function performs the cleanup before device is closed */
static void  __exit gpio_exit(void);

#endif


/*******************************************************************************
* Copyright (c)2017 Rhomb - All rights reserved.
*
* This software is authored by Rhomb and is Rhomb'
* intelletual property,including the copyrights in all countries in the world.
* This software is provided under a license to use only with all other rights,
* including ownership rights, being retained by Rhomb.
*
* This file may not be distributed, copied or reproduced in any manner,
* electronic or otherwise, without the written consent of Rhomb.
*******************************************************************************/
