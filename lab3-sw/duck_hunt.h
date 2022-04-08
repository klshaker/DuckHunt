#ifndef _VGA_BALL_H
#define _VGA_BALL_H

#include <linux/ioctl.h>

enum duck_state { flap_up, flap_down, dead, inactive };

typedef struct {
	// none of these values are larger than 16 bits
	unsigned int16_t x, y, vx, vy, value;
	duck_state state;
} duck_config_t;
  

typedef struct {
  // We should only need 8 bits for each of these
  unsigned char bullets, score, round;
} game_config_t;

#define DUCK_HUNT_MAGIC 'q'

/* ioctls and their arguments */
#define DUCK_HUNT_WRITE_DUCK _IOW(DUCK_HUNT_MAGIC, 1, duck_config_t *)
#define DUCK_HUNT_WRITE_GAME_CONFIG _IOW(DUCK_HUNT_MAGIC, 1, game_config_t *)

#define VGA_BALL_READ_BACKGROUND  _IOR(DUCK_HUNT_MAGIC, 2, vga_ball_arg_t *)

#endif
