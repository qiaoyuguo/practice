/*
 * =====================================================================================
 *
 *       Filename:  hello-1.c
 *
 *    Description:  The simplest kernel module
 *
 *        Version:  1.0
 *        Created:  01/14/2014 08:37:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "Hello world 1.\n");
	/* A non 0 return means init_module failed; module can't be loaded */

	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}


