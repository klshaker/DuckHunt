#include "duck_hunt.h"
#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "duck_hunt"

/* Device registers */
// Are these registers or just selectors? Don't we just use this ass the address? 
#define SCORE(x) (x) 
#define BULLETS(x) ((x)+1)
#define ROUND(x) ((x)+2)
#define DUCK_1_X(x) ((x)+3)
#define DUCK_1_Y(x) ((x)+4)
#define DUCK_1_STATE(x) ((x)+5)
#define DUCK_2_X(x) ((x)+6)
#define DUCK_2_Y(x) ((x)+7)
#define DUCK_2_STATE(x) ((x)+8)
#define GAME_STATE(X) ((x+9)) // start, game over, game 

/*
 * Information about our device
 */
struct duck_hunt_dev {
	struct resource res; /* Resource: our registers */
	void __iomem *virtbase; /* Where registers can be accessed in memory */
        all_game_data_t game;
} dev;

/*
 * Write segments of a single digit
 * Assumes digit is in range and the device information has been set up
 */
// Selector is which duck we are writing information about 
static void write_duck_config(duck_config_t *duck_conf)
{
	iowrite16(duck_conf->x, DUCK_1_X(dev.virtbase) );
	iowrite16(duck_conf->y, DUCK_1_Y(dev.virtbase) );
	iowrite16(duck_conf->state, DUCK_1_STATE(dev.virtbase) );
}

/*
 * Handle ioctl() calls from userspace:
 * Read or write the segments on single digits.
 * Note extensive error checking of arguments
 */
static long duck_hunt_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
	all_game_data_t game_data;

	switch (cmd) {
	case DUCK_HUNT_WRITE_GAME_DATA:
		if (copy_from_user(&game_data, (all_game_data_t *) arg,
				   sizeof(all_game_data_t)))
			return -EACCES;
		write_duck_config(&game_data.duck_1);
		break;

	case DUCK_HUNT_READ_GAME_DATA:
	  	game_data = dev.game;
		if (copy_to_user((all_game_data_t *) arg, &game_data,
				 sizeof(all_game_data_t)))
			return -EACCES;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

/* The operations our device knows how to do */
static const struct file_operations duck_hunt_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = duck_hunt_ioctl,
};

/* Information about our device for the "misc" framework -- like a char dev */
static struct miscdevice duck_hunt_misc_device = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= DRIVER_NAME,
	.fops		= &duck_hunt_fops,
};

/*
 * Initialization code: get resources (registers) and display
 * a welcome message
 */
static int __init duck_hunt_probe(struct platform_device *pdev)
{
        //vga_ball_color_t beige = { 0xf9, 0xe4, 0xb7 };
	int ret;

	/* Register ourselves as a misc device: creates /dev/vga_ball */
	ret = misc_register(&duck_hunt_misc_device);

	/* Get the address of our registers from the device tree */
	ret = of_address_to_resource(pdev->dev.of_node, 0, &dev.res);
	if (ret) {
		ret = -ENOENT;
		goto out_deregister;
	}

	/* Make sure we can use these registers */
	if (request_mem_region(dev.res.start, resource_size(&dev.res),
			       DRIVER_NAME) == NULL) {
		ret = -EBUSY;
		goto out_deregister;
	}

	/* Arrange access to our registers */
	dev.virtbase = of_iomap(pdev->dev.of_node, 0);
	if (dev.virtbase == NULL) {
		ret = -ENOMEM;
		goto out_release_mem_region;
	}
        
	/* Set an initial color */
        //write_background(&beige);

	return 0;

out_release_mem_region:
	release_mem_region(dev.res.start, resource_size(&dev.res));
out_deregister:
	misc_deregister(&duck_hunt_misc_device);
	return ret;
}

/* Clean-up code: release resources */
static int duck_hunt_remove(struct platform_device *pdev)
{
	iounmap(dev.virtbase);
	release_mem_region(dev.res.start, resource_size(&dev.res));
	misc_deregister(&duck_hunt_misc_device);
	return 0;
}

/* Which "compatible" string(s) to search for in the Device Tree */
#ifdef CONFIG_OF
static const struct of_device_id duck_hunt_of_match[] = {
	// set this in the hardware program thingy
	{ .compatible = "csee4840,duck_hunt-1.0" },
	{},
};
MODULE_DEVICE_TABLE(of, duck_hunt_of_match);
#endif

/* Information for registering ourselves as a "platform" driver */
static struct platform_driver duck_hunt_driver = {
	.driver	= {
		.name	= DRIVER_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(duck_hunt_of_match),
	},
	.remove	= __exit_p(duck_hunt_remove),
};

/* Called when the module is loaded: set things up */
static int __init duck_hunt_init(void)
{
	pr_info(DRIVER_NAME ": init\n");
	return platform_driver_probe(&duck_hunt_driver, duck_hunt_probe);
}

/* Calball when the module is unloaded: release resources */
static void __exit duck_hunt_exit(void)
{
	platform_driver_unregister(&duck_hunt_driver);
	pr_info(DRIVER_NAME ": exit\n");
}

module_init(duck_hunt_init);
module_exit(duck_hunt_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephen A. Edwards, Columbia University");
MODULE_DESCRIPTION("Duck Hunt driver");
