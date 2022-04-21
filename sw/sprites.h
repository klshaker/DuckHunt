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

// An entry in the sprite table.
typedef struct {
	// Unique id associated with a sprite. Offsets sprite table
	// will be computed by multiplying id * SPRITE_TABLE_ENTRY_SIZE.
	int id; 
	// Actual sprite data. Each entry in the array is a 32 bit integer that is compromised of 16 two bit 
	// pieces of data representing entries in a color table.
	unsigned int sprite[SPRITE_TABLE_ENTRY_SIZE];
} sprite_data_t;

// An entry in the color table.
typedef struct {
	// Unique id associated with each color table. Offsets for writing to memory will be computed by 
	// multiplying id * COLOR_TABLE_ENTRY_SIZE.
	int id;
	// RGB values.
	int colors[COLOR_TABLE_ENTRY_SIZE];
} color_data_t;

// Array containing all the sprite data we will need to read into FPGA memory on program startup.
extern const sprite_data_t  const kSpriteTableData[NUM_SPRITES];
// Array containing all the color data we will need to read into FPGA memory on program startup.
// At most we will have the maximum number of sprite allowed and each sprite will have its own color table. 
// In practice, the same color table will be re-used by many sprites. Because this array lives in static storage, all values that are not explicitly initialized are guarunteed to be zeroed out.
extern const color_data_t  const kColorTableData[NUM_SPRITES];


// Populates attr_table_entry_t array with all of the attr table entries. Because of the number of entries in this table and how much data is stored in each entry, it is more readible to populate the entries programtically than by initializing a global array.
int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries);

// Writes all entries in the attribution table to FPGA memory using ioctl calls.
int write_sprite_attr_table(int fd);

// Writes the all data in kSpriteTableData to FPGA memory using ioctl calls. 
int write_sprite_table(int fd);

// Write the color table to FPGA memory using ioctl calls.
int write_color_table(int fd);

// Takes the duck in the game and pulls the info that is needed for the attr table for it. Writes that info to the attribution table with an ioctl call.
int update_duck_attr(int fd, duck_t * ducks);

#endif
