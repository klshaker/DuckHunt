/* Converts game data to sprite attribute data.
   Populates data structures containing sprite attribute table, sprite table, and color tables.
*/

#ifndef _SPRITES_H
#define _SPRITES_H

#include "game/game.h"

#define NUM_SPRITES 16 // may add more later
#define NUM_BULLETS 3
#define SPRITE_SIZE 16
// assume the duck sprites are the first sprites in the sprite table.
#define NUM_DUCKS 2
#define DUCK_SPRITE_OFFSET 0
#define DUCK_SPRITE_ATTR_TABLE_OFFSET 0

#define BULLET_SPRITE_OFFSET 48
#define BULLET_SPRITE_ATTR_TABLE_OFFSET 2
#define BULLET_SPRITE_X_LOC 10
#define BULLET_SPRITE_Y_LOC 10

#define NUMBER_SPRITE_OFFSET 80
#define SCORE_SPRITE_ATTR_TABLE_OFFSET 5
#define NUM_SCORE_DIGITS 2 

#define CROSSHAIR_SPRITE_OFFSET 240


#define ATTR_TABLE_OFFSET 0x000 
#define ATTR_TABLE_WRITE_LOCATION(x,y) (x + ATTR_TABLE_OFFSET + y)


typedef struct {
	coord_t coord;
	char sprite;
	char color_table; 
	// This sprite's address in the sprite attribute table.
	int addr;
} attr_table_entry_t;

// one sprite in the sprite table
typedef struct {
	int addr; // address offset from beginning of sprite table.
	unsigned int sprite[SPRITE_SIZE];
} sprite_data_t;

// Writes the sprite attr table to FPGA memory using ioctl calls. Returns 1 if table written succesfully. Returns 0 otherwise.
int write_sprite_attr_table(int fd);

// populates a attr_table_entry_t array with all of the attr table entries.
int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries);

// Writes the sprite table to FPGA memory using ioctl calls.
int write_sprite_table(int fd);

int build_sprite_table(sprite_data_t* sprites, int *num_actual_sprites);

// Takes the duck in the game and pulls the info that is needed for the attr table for it. Writes that info to the attribution table with an ioctl call.
int update_duck_attr(int fd, duck_t * duck, int num_ducks);


#endif
