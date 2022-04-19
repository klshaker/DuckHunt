#include "sprites.h"
#include <string.h>
#include <stdlib.h>
#include "ppu.h"
#include <sys/ioctl.h>

// Returns 1 if table all written succesfully. Returns 0 otehrwise.
int write_sprite_attr_table(int fd){

	int i = 0;
	for(;i < NUM_DUCKS; i++){
		attr_table_entry_t duck;
		duck.coord.x = 0;
		duck.coord.y = 0;
		duck.sprite = DUCK_SPRITE_OFFSET;
		duck.addr = DUCK_SPRITE_ATTR_TABLE_OFFSET + i;
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &duck)) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}

	i = 0;
	for(;i < NUM_BULLETS; ++i){
		attr_table_entry_t bullet;

		// space for each sprite and 10 pixels between the sprites. Note that the bullets might be small enough to not need the 10 pixels of space.
		bullet.coord.x = BULLET_SPRITE_X_LOC + i*SPRITE_SIZE + i *10;
		bullet.coord.y = BULLET_SPRITE_Y_LOC;
		// all bullets start off shaded.
		bullet.sprite = BULLET_SPRITE_OFFSET;
		bullet.addr = BULLET_SPRITE_ATTR_TABLE_OFFSET +i;
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &bullet)) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}

	}

	i = 0;
	for(;i< NUM_SCORE_DIGITS; ++i){
		attr_table_entry_t score;
		// these numbers were chosen arbitrarily
		score.coord.x = 600;
		score.coord.y = 10;
		// score starts off 00
		score.sprite = NUMBER_SPRITE_OFFSET;
		score.addr = SCORE_SPRITE_ATTR_TABLE_OFFSET;
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &score)) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}

	return 1;
}

attr_table_entry_t convert_duck_to_attr_entry(duck_t* duck){
	attr_table_entry_t entry;
	entry.coord = duck->coord;
	entry.addr = DUCK_SPRITE_ATTR_TABLE_OFFSET + duck->id; // ducks can be the beginning of the sprite attribute table and therefore indexible by ID. 
	entry.sprite = DUCK_SPRITE_OFFSET + duck->state * 16; 
	entry.color_table = 0; // ducks can have the first entry in the color table.
	return entry;
}

