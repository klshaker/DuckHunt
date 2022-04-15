#ifndef _DUCK_HUNT_H
#define _DUCK_HUNT_H

#include <linux/ioctl.h>
#include "game/game.h"


#define PPU_MAGIC 'q'

/* ioctls and their arguments */
#define ATTR_TABLE_WRITE_DATA  _IOW(PPU_MAGIC, 1, attr_table_entry_t *)
#define SPRITE_TABLE_WRITE_DATA  _IOW(PPU_MAGIC, 2, int *)

#endif
