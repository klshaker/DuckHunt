/* 
   Handles all sprite related data. 
*/

#ifndef _SPRITES_H
#define _SPRITES_H

#include "game/game.h"
#include "ppu.h"

#ifndef __KERNEL__
#include <stdint.h>
#else
#include <linux/types.h> 
#endif

#define NUM_SPRITES 16 

#define NUM_BULLETS 3
#define NUM_DUCKS 2
#define NUM_SCORE_DIGITS 2 

// offsets of various classes of sprites in the sprite table. 
#define DUCK_SPRITE_OFFSET 0
#define BULLET_SPRITE_OFFSET 2
#define NUMBER_SPRITE_OFFSET 5
#define CROSSHAIR_SPRITE_OFFSET 15

// offsets of various classes of entries in the sprite attribution table.
// the order in which these entries are laid out is an implementation decision.
#define DUCK_SPRITE_ATTR_TABLE_OFFSET 0
#define BULLET_SPRITE_ATTR_TABLE_OFFSET 2
#define SCORE_SPRITE_ATTR_TABLE_OFFSET 5
#define ROUND_SPRITE_ATTR_TABLE_OFFSET 7
#define CROSSHAIR_SPRITE_ATTR_TABLE_OFFSET 8

// Populates attr_table_entry_t array with all of the attr table entries. Because of the number of entries in this table and how much data is stored in each entry, it is more readible to populate the entries programtically than by initializing a global array.
int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries);

// Writes all entries in the attribution table to FPGA memory using ioctl calls. Returns 1 if writes succesful, 0 on failure.
int write_sprite_attr_table(int fd);

// Writes the all data in kSpriteTableData to FPGA memory using ioctl calls. Returns 1 if writes succesful, 0 on failure.
int write_sprite_table(int fd);

// Write the color table to FPGA memory using ioctl calls. Returns 1 if writes succesful, 0 on failure.
int write_color_table(int fd);

// Takes the data structure used to represent a duck in the game (duck_t) and pulls the info that is needed for the attr table for it. Writes that info to the attribution table with an ioctl call.
int update_duck_attr(int fd, duck_t * ducks);

#endif
