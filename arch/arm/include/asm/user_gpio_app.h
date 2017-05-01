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
 * This file contains declaration of APIs used in user space GPIO driver.
 *******************************************************************************/

/******************************************************************************
 *
 * File Name   :  user_gpio_app.h
 *
 * Description :  This is a C source code header file for gpio driver.
 *
 * History     :  April/24/2017, Android Linux Media, Created the file.
 *
 *******************************************************************************/

#ifndef _USER_GPIO_APP_H
#define _USER_GPIO_APP_H

/*********************************
 * Defines and Macros and globals
 *********************************/
#define USR_GPIO_DEVICE       "/dev/usr_gpio"
/* IOCTLS */
#define	GPIO_IOC_MAGIC	'G' /* G as Magic number not in " " */

/* COMMANDS	*/
/* type = Magic no.; nr  = ordinal sequence num; size = of usr data */
/* Read Status of a GPIO PIN drive state */
#define	GPIO_GET_VALUE	 _IOR(GPIO_IOC_MAGIC, 1, gpio_arg_t)

/* Set the drive state of a GPIO PIN */
#define	GPIO_SET_VALUE	 _IOW(GPIO_IOC_MAGIC, 2, gpio_arg_t)

/* Set GPIO pin direction input/output */
#define	GPIO_SET_DIRECTION _IOW(GPIO_IOC_MAGIC, 3, gpio_arg_t)


/* MAX num of cmd available */
#define GPIO_IOC_MAXNR  3

/*********************************
 * Typedefs and Structs and Enums
 *********************************/
typedef struct _gpio_arg
{
	unsigned int   gpio;
	unsigned char  value;
}gpio_arg_t;

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
