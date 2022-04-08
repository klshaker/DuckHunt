#ifndef _VGA_BALL_H
#define _VGA_BALL_H

#include <linux/ioctl.h>
#include "game.h"


#define DUCK_HUNT_MAGIC 'q'

/* ioctls and their arguments */
#define DUCK_HUNT_WRITE_GAME_DATA  _IOW(DUCK_HUNT_MAGIC, 1, all_game_data_t *)
#define DUCK_HUNT_READ_GAME_DATA _IOW(DUCK_HUNT_MAGIC, 2, all_game_data_t *)

#endif
