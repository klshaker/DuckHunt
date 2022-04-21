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

typedef struct {
	// location of this attr table on the VGA monitor 
	coord_t coord;
	// sprite table offset with data for each pixel of the sprite.
	char sprite;
	// color table offset with RBG values for whichever sprite this attr table entry represents.
	char color_table; 
	// unique id associated with an attr table entry. Offset in the attr table will 
	// be computed by multiplying id * ATTR_TABLE_SIZE
	int id;
} attr_table_entry_t;

// one sprite in the sprite table
typedef struct {
	// unique id associated with a sprite. Offsets sprite table
	// will be computed by multiplying id * SPRITE_SIZE
	int id; 
	// actual sprite data. Each entry in the array is a 32 bit integer that is compromised of 16 two bit 
	// pieces of data representing entries in a color table.
	unsigned int sprite[SPRITE_TABLE_ENTRY_SIZE];
} sprite_data_t;

typedef struct {
	// unique id associated with each color table. Offsets for writing to memory will be computed by 
	// multiplying id * COLOR_TABLE_SIZE
	int id;
	// RGB values.
	int colors[COLOR_TABLE_ENTRY_SIZE];
} color_data_t;

// At most we will have the maximum number of sprite allowed and each sprite will have its own color table. 
// In practice, the same color table will be re-used by many sprites.
extern const sprite_data_t  const kSpriteTableData[NUM_SPRITES];
extern const color_data_t  const kColorTableData[NUM_SPRITES];

// Writes the sprite attr table to FPGA memory using ioctl calls. 
int write_sprite_attr_table(int fd);

// Populates attr_table_entry_t array with all of the attr table entries.
int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries);

// Writes the sprite table to FPGA memory using ioctl calls.
int write_sprite_table(int fd);

// Write the color table to FPGA memory using ioctl calls.
int write_color_table(int fd);

// Takes the duck in the game and pulls the info that is needed for the attr table for it. Writes that info to the attribution table with an ioctl call.
int update_duck_attr(int fd, duck_t * duck, int num_ducks);

#endif
