#ifndef _VGA_BALL_H
#define _VGA_BALL_H

#include <linux/ioctl.h>

enum duck_state { flap_up, flap_down, dead, inactive };

typedef struct {
	// none of these values are larger than 16 bits
	unsigned int x, y, vx, vy, value;
	enum duck_state state;
} duck_config_t;

typedef struct {
  // We should only need 8 bits for each of these
  unsigned char bullets, score, round;
} game_config_t;

typedef struct {
  duck_config_t duck_1;
  duck_config_t duck_2;
  game_config_t game_conf;
} all_game_data_t;

#define DUCK_HUNT_MAGIC 'q'

/* ioctls and their arguments */
#define DUCK_HUNT_WRITE_GAME_DATA  _IOW(DUCK_HUNT_MAGIC, 1, all_game_data_t *)
#define DUCK_HUNT_READ_GAME_DATA _IOW(DUCK_HUNT_MAGIC, 2, all_game_data_t *)

#endif
