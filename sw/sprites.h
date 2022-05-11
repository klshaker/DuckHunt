/* 
   Handles all sprite related data. 
*/

#ifndef _SPRITES_H
#define _SPRITES_H

#include "ppu.h"
#include "game/game.h"

#ifndef __KERNEL__
#include <stdint.h>
#else
#include <linux/types.h> 
#endif

#define NUM_SPRITES 64 
#define NUM_COLOR_TABLE_ENTRIES 4
#define NUM_ATTR_TABLE_ENTRIES 64
#define NUM_SPRITES_PER_DUCK 4

#define NUM_BULLETS 3
#define NUM_SCORE_DIGITS 2 

// Offsets of various classes of sprites in the sprite table. 
// The 0th offset is reserved for sprites we do not want to see on the screen.
#define DUCK_DOWN_EAST_SPRITE_OFFSET 1
#define DUCK_UP_EAST_SPRITE_OFFSET 5 
#define DUCK_DOWN_WEST_SPRITE_OFFSET 13
#define DUCK_UP_WEST_SPRITE_OFFSET 17
#define DUCK_DEAD_SPRITE_OFFSET 29
#define DUCK_FLYING_AWAY_SPRITE_OFFSET 33

#define BULLET_SPRITE_OFFSET 37
// Shaded and non shaded bullets will share the same sprite but point
// to different color tables.
#define NUMBER_SPRITE_OFFSET 38
// 6 + 10 digits = 16
#define CROSSHAIR_SPRITE_OFFSET 48

// Offsets of various classes of entries in the sprite attribution table.
// The order in which these entries are laid out is an implementation decision.
#define DUCK_ATTR_TABLE_OFFSET 0
#define BULLET_ATTR_TABLE_OFFSET NUM_DUCKS_PER_ROUND * NUM_SPRITES_PER_DUCK 
#define SCORE_ATTR_TABLE_OFFSET BULLET_ATTR_TABLE_OFFSET + NUM_BULLETS
#define ROUND_ATTR_TABLE_OFFSET SCORE_ATTR_TABLE_OFFSET + NUM_SCORE_DIGITS
#define CROSSHAIR_ATTR_TABLE_OFFSET ROUND_ATTR_TABLE_OFFSET

#define DUCK_COLOR_TABLE_OFFSET 0
#define SHADED_BULLET_COLOR_TABLE_OFFSET 1
#define UNSHADED_BULLET_COLOR_TABLE_OFFSET 2
#define NUMBER_LETTER_COLOR_TABLE_OFFSET 3

// Populates attr_table_entry_t array with all of the attr table entries. Because of the number of entries in this table and how much data is stored in each entry, it is more readible to populate the entries programtically than by initializing a global array.
int build_sprite_attr_table(attr_table_entry_t * entries);

// Writes all entries in the attribution table to FPGA memory using ioctl calls. Returns 1 if writes succesful, 0 on failure.
int write_sprite_attr_table(int fd);

// Writes the all data in kSpriteTableData to FPGA memory using ioctl calls. Returns 1 if writes succesful, 0 on failure.
int write_sprite_table(int fd);

// Write the color table to FPGA memory using ioctl calls. Returns 1 if writes succesful, 0 on failure.
int write_color_table(int fd);

// Updates score and number of bullets remaining every round.
int update_game_state_attrs(int fd, int num_bullets, int score, int round);

// Updates the duck attr for the duck corresponding to duck_id in the attr table every round.
int update_duck_attr(int fd, duck_t* duck);

// Updates the crosshair attribute for display.
int update_crosshair_attr(int fd, int x_coord, int y_coord);
#endif
