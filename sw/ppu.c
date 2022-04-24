#include "ppu.h"
#include "sprites.h"
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

#define DRIVER_NAME "ppu"

// How the bits for each attr table entry are laid out.
#define OBJ_SPRITE_OFFSET 20
#define OBJ_X_COORD_OFFSET 10
#define OBJ_Y_COORD_OFFSET 0
#define OBJ_COLOR_OFFSET 28

#define ATTR_TABLE_MEMORY_OFFSET 0x00
#define SPRITE_TABLE_MEMORY_OFFSET 0x100 
#define COLOR_TABLE_MEMORY_OFFSET 0x200 

// first argument is dev.base, second argument is distance from table offset.
#define ATTR_TABLE_MEMORY_WRITE(x, y) (x + ATTR_TABLE_MEMORY_OFFSET + y)
#define SPRITE_TABLE_MEMORY_WRITE(x,y) (x + SPRITE_TABLE_MEMORY_OFFSET + y)
#define COLOR_TABLE_MEMORY_WRITE(x, y) (x + COLOR_TABLE_MEMORY_OFFSET + y)

/*
 * Information about our device
 */
struct ppu_dev {
	struct resource res; /* Resource: our registers */
	void __iomem *virtbase; /* Where registers can be accessed in memory */
	all_game_data_t game;
} dev;

// Write to the attribution table sprite related information. Addr will vary based on which sprite we are updating. 
static void write_to_sprite_attr_table(attr_table_entry_t *sprite)
{

	int data = 0xFFFF;

	data = data && (sprite->coord.x << OBJ_X_COORD_OFFSET);
	data = data && (sprite->coord.y << OBJ_Y_COORD_OFFSET);
	data = data && (sprite->sprite  << OBJ_SPRITE_OFFSET);
	data = data && (sprite->color_table   << OBJ_COLOR_OFFSET);

	iowrite32(data, ATTR_TABLE_MEMORY_WRITE(dev.virtbase , sprite->id * ATTR_TABLE_ENTRY_SIZE));

}

static void write_to_color_table(int *color)
{

	// All color tables take up COLOR_TABLE_ENTRY_SIZE 'rows' in the 32 bit FPGA memory. Each call to this function represents one color 
	// table being written.
	static int color_table_written = 0;
	int i = 0;
	for(; i < COLOR_TABLE_ENTRY_SIZE; ++i){
		int data = 0xFFFF;
		iowrite32(data, COLOR_TABLE_MEMORY_WRITE(dev.virtbase , (color_table_written * COLOR_TABLE_ENTRY_SIZE) + i));
	}	
	// The next color table will start at COLOR_TABLE_ENTRY_SIZE away from this one.
	++color_table_written;

}

// Called at program startup to initialize all of the sprites. This data will not change throughout the lifetime of the program.
static void write_to_sprite_table(int * sprite)
{

	static int sprites_written = 0;
	printk("writing sprite to memory\n");
	// All sprites take up SPRITE_TABLE_ENTRY_SIZE 'rows' in the 32 bit FPGA memory. We have to keep track of how many sprites
	// have so far been written, so we can ensure each sprite comes after the previous one.
	int i = 0;
	for(; i < SPRITE_TABLE_ENTRY_SIZE; i ++){
		iowrite32(sprite[i], SPRITE_TABLE_MEMORY_WRITE(dev.virtbase , (sprites_written * SPRITE_TABLE_ENTRY_SIZE) + i));
	}

	// This function will be called exactly once per sprite.
	++sprites_written;
}

/*
 * Handle ioctl() calls from userspace:
 * Read or write the segments on single digits.
 * Note extensive error checking of arguments
 */
static long ppu_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
	attr_table_entry_t attr_table_entry;
	int sprite[SPRITE_TABLE_ENTRY_SIZE];
	int color[COLOR_TABLE_ENTRY_SIZE];

	switch (cmd) {
		case ATTR_TABLE_WRITE_DATA:  
			if (copy_from_user(&attr_table_entry, (attr_table_entry_t *) arg,
						sizeof(attr_table_entry_t)))
				return -EACCES;
			write_to_sprite_attr_table(&attr_table_entry);
			break;

		case SPRITE_TABLE_WRITE_DATA:
			if (copy_from_user(&sprite, (int*) arg, sizeof(int)))
				return -EACCES;
			write_to_sprite_table(sprite);
			break;
		case COLOR_TABLE_WRITE_DATA:
			if (copy_from_user(&color, (int*) arg,
						sizeof(int)))
				return -EACCES;
			write_to_color_table(color);
			break;

		default:
			return -EINVAL;
	}

	return 0;
}

/* The operations our device knows how to do */
static const struct file_operations ppu_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = ppu_ioctl,
};

/* Information about our device for the "misc" framework -- like a char dev */
static struct miscdevice ppu_misc_device = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= DRIVER_NAME,
	.fops		= &ppu_fops,
};

/*
 * Initialization code: get resources (registers).
 */
static int __init ppu_probe(struct platform_device *pdev)
{
	int ret;

	/* Register ourselves as a misc device: creates /dev/vga_ball */
	ret = misc_register(&ppu_misc_device);

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

	return 0;

out_release_mem_region:
	release_mem_region(dev.res.start, resource_size(&dev.res));
out_deregister:
	misc_deregister(&ppu_misc_device);
	return ret;
}

/* Clean-up code: release resources */
static int ppu_remove(struct platform_device *pdev)
{
	iounmap(dev.virtbase);
	release_mem_region(dev.res.start, resource_size(&dev.res));
	misc_deregister(&ppu_misc_device);
	return 0;
}

/* Which "compatible" string(s) to search for in the Device Tree */
#ifdef CONFIG_OF
static const struct of_device_id ppu_of_match[] = {
	// set this in the hardware program thingy
	{ .compatible = "csee4840,ppu-1.0" },
	{},
};
MODULE_DEVICE_TABLE(of, ppu_of_match);
#endif

/* Information for registering ourselves as a "platform" driver */
static struct platform_driver ppu_driver = {
	.driver	= {
		.name	= DRIVER_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ppu_of_match),
	},
	.remove	= __exit_p(ppu_remove),
};

/* Called when the module is loaded: set things up */
static int __init ppu_init(void)
{
	pr_info(DRIVER_NAME ": init\n");
	return platform_driver_probe(&ppu_driver, ppu_probe);
}

/* Calball when the module is unloaded: release resources */
static void __exit ppu_exit(void)
{
	platform_driver_unregister(&ppu_driver);
	pr_info(DRIVER_NAME ": exit\n");
}

module_init(ppu_init);
module_exit(ppu_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kristen Shaker");
MODULE_DESCRIPTION("PPU driver");
