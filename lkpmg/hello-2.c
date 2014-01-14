/*
 * =====================================================================================
 *
 *       Filename:  hello-2.c
 *
 *    Description:  hello-2.c -- demonstrating the module_init() and 
 *                  module_exit()
 *        Version:  1.0
 *        Created:  01/14/2014 03:10:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int  __init hello_2_init(void)
{
	printk(KERN_INFO "Hello, world 2\n");

	return 0;
}

static void __exit hello_2_exit(void)
{
	printk(KERN_INFO "Goodbye, world 2\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

