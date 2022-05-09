/* 

This module is responsible for pulling data from userspace and writing it to FPGA memory using
iowrite calls.

*/
#ifndef _PPU_H_
#define _PPU_H_

#include <linux/ioctl.h>

#ifndef __KERNEL__
#include <stdint.h>
#else
#include <linux/types.h> 
#endif

// sizes of each entry in various tables in memory
#define SPRITE_TABLE_ENTRY_SIZE (16)
#define COLOR_TABLE_ENTRY_SIZE  (4)
#define ATTR_TABLE_ENTRY_SIZE   (1)

// How the bits for each attr table entry are laid out.
#define OBJ_Y_COORD_OFFSET 0
#define OBJ_X_COORD_OFFSET 10
#define OBJ_SPRITE_OFFSET 20
#define OBJ_COLOR_OFFSET 28

#define ATTR_TABLE_MEMORY_OFFSET    (0x0000 * 4)
#define COLOR_TABLE_MEMORY_OFFSET   (0x1000 * 4)
#define SPRITE_TABLE_MEMORY_OFFSET  (0x2000 * 4)

// first argument is dev.base, second argument is distance from table offset.
#define ATTR_WRITE(x, y)  (x + ATTR_TABLE_MEMORY_OFFSET    + (y * 4))
#define SPRITE_WRITE(x,y) (x + SPRITE_TABLE_MEMORY_OFFSET  + (y * 4))
#define COLOR_WRITE(x, y) (x + COLOR_TABLE_MEMORY_OFFSET   + (y * 4))

//Write to address structure - used for debugging. 
struct wta {
    int addr;
    int value;
};

typedef struct {
	// signed so that we can go negative when sprite is partially on the screen.
	int x,y;
} sprite_coord_t;

// An entry in the sprite attribution table.
typedef struct {
	// Location of this attr table entry on the VGA monitor.
	sprite_coord_t coord;
	// Sprite table offset.
	char sprite;
	// Color table offset with RBG values for whichever sprite this attr table entry represents.
	char color_table; 
	// Unique id associated with an attr table entry. Offset in the attr table will 
	// be computed by multiplying id * ATTR_TABLE_ENTRY_SIZE.
	int id;
} attr_table_entry_t;

typedef struct {
    uint32_t id;
    uint32_t line[16];
} sprite_table_entry_t;

#define RED_OFFSET 0
#define GREEN_OFFSET 8  
#define BLUE_OFFSET 16
typedef struct {
    int r, g, b;
} color_t;

typedef struct {
    int id;
    color_t color[4]; //, color1, color2, color3;
} color_table_entry_t;

/* ioctls and their arguments */
#define PPU_MAGIC 'p'
#define ATTR_TABLE_WRITE_DATA   _IOW(PPU_MAGIC, 1, attr_table_entry_t *)
#define SPRITE_TABLE_WRITE_DATA _IOW(PPU_MAGIC, 2, sprite_table_entry_t *)
#define COLOR_TABLE_WRITE_DATA  _IOW(PPU_MAGIC, 3, color_table_entry_t *)
#define WRITE_TO_ADDRESS        _IOW(PPU_MAGIC, 4, struct wta *)

#endif
