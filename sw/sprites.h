/* Converts game data to sprite attribute data.
   Populates data structures containing sprite attribute table, sprite table, and color tables.
*/

#ifndef _SPRITES_H
#define _SPRITES_H

#include "game/game.h"

#define NUM_SPRITES 32 // may add more later
#define NUM_BULLETS_POSSIBLE 3
#define SPRITE_SIZE 16
// assume the duck sprites are the first sprites in the sprite table.
#define DUCK_SPRITE_OFFSET 0
#define DUCK_SPRITE_ATTR_TABLE_OFFSET 0

#define BULLET_SPRITE_OFFSET 48
#define BULLET_SPRITE_ATTR_TABLE_OFFSET 2
#define BULLET_SPRITE_X_LOC 10
#define BULLET_SPRITE_Y_LOC 10

typedef struct {
	coord_t coord;
	char sprite;
	char color_table; 
	// This sprite's address in the sprite attribute table.
	int addr;
} attr_table_entry_t;

typedef struct {
	int addr; // address offset from beginning of sprite table.
	int sprite[SPRITE_SIZE];
} sprite_data_t;


// data tables

int attr_table[32] = {};
sprite_data_t sprites[NUM_SPRITES];
int color_table[NUM_SPRITES*4];


// Takes the duck in the game and pulls the info that is needed for the attr table for it.
attr_table_entry_t convert_duck_to_attr_entry(duck_t* duck);

// takes an entries array by reference and populates it with 
// bullet 1, bullet 2, bullet 3, score 1, score 2, round
void get_game_config_attr_entries(game_config_t * game_config, attr_table_entry_t* entries);




#endif
