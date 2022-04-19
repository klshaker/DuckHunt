#include "sprites.h"
#include <string.h>

attr_table_entry_t convert_duck_to_attr_entry(duck_t* duck){
	attr_table_entry_t entry;
	entry.coord = duck->coord;
	entry.addr = DUCK_SPRITE_ATTR_TABLE_OFFSET + duck->id; // ducks can be the beginning of the sprite attribute table and therefore indexible by ID. 
	entry.sprite = DUCK_SPRITE_OFFSET + duck->state * 16; 
	entry.color_table = 0; // ducks can have the first entry in the color table.
	return entry;
}

// takes an entries array by reference and populates it with 
// bullet 1, bullet 2, bullet 3, score 1, score 2, round
void get_game_config_attr_entries(game_config_t * game_config, attr_table_entry_t* entries){
	int i = 0;
	for(;i < NUM_BULLETS_POSSIBLE; i++){
		attr_table_entry_t bullet;
		bullet.addr = BULLET_SPRITE_ATTR_TABLE_OFFSET + i;
		bullet.sprite = game_config->bullets > i ? BULLET_SPRITE_OFFSET: BULLET_SPRITE_OFFSET + SPRITE_SIZE;	
		bullet.coord.x = BULLET_SPRITE_X_LOC + 20 * i;
		bullet.coord.y = BULLET_SPRITE_Y_LOC;
		bullet.color_table = 1;
		memcpy(&entries[i], &bullet, sizeof(attr_table_entry_t));
	}
}
