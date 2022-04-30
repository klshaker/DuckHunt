/* 

This module is responsible for pulling data from userspace and writing it to FPGA memory using
iowrite calls.

*/
#ifndef _PPU_H_
#define _PPU_H_

#include <linux/ioctl.h>

#define PPU_MAGIC 'q'

/* ioctls and their arguments */
#define ATTR_TABLE_WRITE_DATA  _IOW(PPU_MAGIC, 1, attr_table_entry_t *)
#define SPRITE_TABLE_WRITE_DATA  _IOW(PPU_MAGIC, 2, int *)
#define COLOR_TABLE_WRITE_DATA  _IOW(PPU_MAGIC, 3, int *)
#define WRITE_TO_ADDRESS        _IOW(PPU_MAGIC, 4, int *)


#endif
