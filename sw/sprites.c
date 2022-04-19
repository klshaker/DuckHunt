#include "sprites.h"
#include <string.h>
#include <stdlib.h>
#include "ppu.h"
#include <sys/ioctl.h>

// zero initialized
const int kDuckUp[SPRITE_SIZE] = {};
const int kDuckDown[SPRITE_SIZE] = {};
const int kDuckDead[SPRITE_SIZE] = {};
const int kBulletShaded[SPRITE_SIZE] = {};
const int kBulletTransparent[SPRITE_SIZE] = {};
const int kOne[SPRITE_SIZE] = {};
const int kTwo[SPRITE_SIZE] = {};
const int kThree[SPRITE_SIZE] = {};
const int kFour[SPRITE_SIZE] = {};
const int kFive[SPRITE_SIZE] = {};
const int kSix[SPRITE_SIZE] = {};
const int kSeven[SPRITE_SIZE] = {};
const int kEight[SPRITE_SIZE] = {};
const int kNine[SPRITE_SIZE] = {};
const int kCrosshair[SPRITE_SIZE] = {};

int write_sprite_table_sprite_ioctl(int fd, sprite_data_t * sprite){
	if (ioctl(fd, SPRITE_TABLE_WRITE_DATA, sprite)) {
		perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
		return 0;
	}
	return 1;
}

int write_sprite_table(int fd){

	sprite_data_t duck_up;
	duck_up.addr = DUCK_SPRITE_OFFSET;
	memcpy(duck_up.sprite, kDuckUp, SPRITE_SIZE);
	write_sprite_table_sprite_ioctl(fd, &duck_up);

	sprite_data_t duck_down;
	duck_down.addr = DUCK_SPRITE_OFFSET + SPRITE_SIZE;
	memcpy(duck_down.sprite, kDuckDown, SPRITE_SIZE);
	write_sprite_table_sprite_ioctl(fd, &duck_down);

	sprite_data_t duck_dead;
	duck_down.addr = DUCK_SPRITE_OFFSET + 2 * SPRITE_SIZE;
	memcpy(duck_dead.sprite, kDuckDead, SPRITE_SIZE);
	write_sprite_table_sprite_ioctl(fd, &duck_dead);
}

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

int update_duck_attr(int fd, duck_t * ducks, int num_ducks) {
	int i =0;
	for(; i < NUM_DUCKS; ++i){
	attr_table_entry_t duck_attr = convert_duck_to_attr_entry(&ducks[i]);

	if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &duck_attr)) {
		perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
		return 0;
	}
}	
return 1;
}
