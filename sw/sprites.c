#include "sprites.h"
#include <string.h>
#include <stdlib.h>
#include "ppu.h"
#include <sys/ioctl.h>

// second entry in the color table for the entire sprite.
#define second  0xAAAAAAAA
#define black 0x000FFFFFF

//TODO(kristenshaker) update the number of sprites
const int sprites[2][SPRITE_SIZE] = { 
//duckUp
{
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
},
{
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
	second,
}
};

const int kColors[2][4] ={

{black, black, black, black},
{black, black, black, black},

};

int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries){

	*num_entries = 0;

	int i = 0;
	for(;i < NUM_DUCKS; i++){
		attr_table_entry_t duck;
		duck.coord.x = 0;
		duck.coord.y = 0;
		duck.sprite = DUCK_SPRITE_OFFSET;
		duck.addr = *num_entries;

		entries[*num_entries] = duck;
		++(*num_entries);

	}

	i = 0;
	for(;i < NUM_BULLETS; ++i){
		attr_table_entry_t bullet;

		// space for each sprite and 10 pixels between the sprites. Note that the bullets might be small enough to not need the 10 pixels of space.
		bullet.coord.x = BULLET_SPRITE_X_LOC + i*SPRITE_SIZE + i *10;
		bullet.coord.y = BULLET_SPRITE_Y_LOC;
		// all bullets start off shaded.
		bullet.sprite = BULLET_SPRITE_OFFSET;
		bullet.addr = *num_entries;

		entries[*num_entries] = bullet;
		++(*num_entries);
	}

	i = 0;
	for(;i< NUM_SCORE_DIGITS; ++i){
		attr_table_entry_t score;
		// these numbers were chosen arbitrarily
		score.coord.x = 600;
		score.coord.y = 10;
		// score starts off 00
		score.sprite = NUMBER_SPRITE_OFFSET;
		score.addr = *num_entries;
		entries[*num_entries] = score;

		++(*num_entries);
	}

	// round entry
	attr_table_entry_t round;
	// TODO(kristenshaker): change these coords
	round.coord.x = 600;
	round.coord.y = 10;
	// round starts at 0
	round.sprite = NUMBER_SPRITE_OFFSET;
	round.addr = *num_entries;

	entries[*num_entries] = round;

	++(*num_entries);
	attr_table_entry_t crosshair;
	// TODO(kristenshaker): change these coords
	crosshair.coord.x = 600;
	crosshair.coord.y = 10;
	// round starts at 0
	crosshair.sprite = CROSSHAIR_SPRITE_OFFSET;
	// after round
	crosshair.addr = *num_entries;

	entries[*num_entries]=crosshair;
	++(*num_entries);

	return 1;
}


int build_sprite_table(sprite_data_t* sprites, int *num_actual_sprites){

	*num_actual_sprites = 0;
	sprite_data_t duck_up;
	duck_up.addr = DUCK_SPRITE_OFFSET;
	memcpy(&sprites[*num_actual_sprites].sprite, &sprites[0], sizeof(int) * SPRITE_SIZE);
	memcpy(&sprites[*num_actual_sprites].addr, &duck_up.addr, sizeof(int));
	++(*num_actual_sprites);

	sprite_data_t duck_down;
	duck_down.addr = DUCK_SPRITE_OFFSET + SPRITE_SIZE;
	memcpy(&sprites[*num_actual_sprites].sprite, &sprites[0], sizeof(int)*SPRITE_SIZE);
	memcpy(&sprites[*num_actual_sprites].addr, &duck_down.addr, sizeof(int));
	++(*num_actual_sprites);

	return 1;
}

int write_sprite_table(int fd){

	sprite_data_t sprites[NUM_SPRITES];
	int num_actual_sprites =0;
	if(!build_sprite_table(sprites, &num_actual_sprites)){
		return 0;
	}
	int i =0;
	for(;i<num_actual_sprites; ++i){
		if (ioctl(fd, SPRITE_TABLE_WRITE_DATA, &sprites[i])) {
			perror("ioctl(SPRITE_TABLE_WRITE_DATA) failed");
			return 0;
		}

	}
}

int build_color_table(color_data_t* colors){
	int i = 0;
	for(;i< 2; ++i){
		memcpy(&colors[i], &kColors[i], sizeof(int) * NUM_COLORS_PER_TABLE);
		colors[i].addr = i * NUM_COLORS_PER_TABLE;
	}
}

int write_color_table(int fd){

	color_data_t colors[2];
	if(!build_color_table(colors)){
		return 0;
	}
	
	int i = 0;
	for(;i<2; ++i){
		if (ioctl(fd, COLOR_TABLE_WRITE_DATA, &colors[i])) {
			perror("ioctl(SPRITE_TABLE_WRITE_DATA) failed");
			return 0;
		}

	}
}


int write_sprite_attr_table(int fd){
	// number of possible sprites
	attr_table_entry_t entries[NUM_SPRITES];
	// number of actual data table entries.
	int num_entries_actual = 0;
	if(!build_sprite_attr_table(entries, &num_entries_actual)){

		return 0;
	}
	int i = 0;
	for(; i < num_entries_actual; ++i){
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &entries[i])) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}

	}
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
