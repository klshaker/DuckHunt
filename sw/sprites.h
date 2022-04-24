/* 
   Handles all sprite related data. 
*/

#ifndef _SPRITES_H
#define _SPRITES_H

#include "game/game.h"

// sizes of each entry in various tables in memory
#define SPRITE_TABLE_ENTRY_SIZE 16
#define COLOR_TABLE_ENTRY_SIZE 4
#define ATTR_TABLE_ENTRY_SIZE 1

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

#define NUM_SPRITES 16 

#define NUM_BULLETS 3
#define NUM_DUCKS 2
#define NUM_SCORE_DIGITS 2 

// An entry in the sprite attribution table.
typedef struct {
	// Location of this attr table entry on the VGA monitor.
	coord_t coord;
	// Sprite table offset.
	char sprite;
	// Color table offset with RBG values for whichever sprite this attr table entry represents.
	char color_table; 
	// Unique id associated with an attr table entry. Offset in the attr table will 
	// be computed by multiplying id * ATTR_TABLE_ENTRY_SIZE.
	int id;
} attr_table_entry_t;

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
