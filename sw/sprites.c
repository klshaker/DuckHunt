#include "sprites.h"
#include <string.h>
#include <stdlib.h>
#include "ppu.h"
#include <sys/ioctl.h>

// TODO(kristenshaker): remove these standin values once we have actual data.
#define second  0xAAAAAAAA
#define black 0x000FFFFFF

#define BULLET_SPRITE_X_LOC 10
#define BULLET_SPRITE_Y_LOC 10

int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries){

    *num_entries = 0;

    int i = 0;
    for(;i < NUM_DUCKS; i++){
	attr_table_entry_t duck;
	duck.coord.x = 0;
	duck.coord.y = 0;
	duck.sprite = DUCK_SPRITE_OFFSET;
	duck.id = *num_entries;

	entries[*num_entries] = duck;
	++(*num_entries);
    }

    i = 0;
    for(;i < NUM_BULLETS; ++i){
	attr_table_entry_t bullet;

	// space for each sprite and 10 pixels between the sprites. Note that the bullets might be small enough to not need the 10 pixels of space.
	bullet.coord.x = BULLET_SPRITE_X_LOC + i* SPRITE_TABLE_ENTRY_SIZE + i * 10;
	bullet.coord.y = BULLET_SPRITE_Y_LOC;
	// all bullets start off shaded.
	bullet.sprite = BULLET_SPRITE_OFFSET;
	bullet.id = *num_entries;

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
	score.id = *num_entries;
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
    round.id = *num_entries;

    entries[*num_entries] = round;

    ++(*num_entries);
    attr_table_entry_t crosshair;
    // TODO(kristenshaker): change these coords
    crosshair.coord.x = 600;
    crosshair.coord.y = 10;
    crosshair.sprite = CROSSHAIR_SPRITE_OFFSET;
    crosshair.id = *num_entries;

    entries[*num_entries]=crosshair;
    ++(*num_entries);

    return 1;
}


int write_sprite_table(int fd){
    // This data is read into FPGA memory once at start up time. It is not required 
    // anywhere else, so it will be kept a local variable.
    // TODO(kristenshaker): populate this table with the rest of the sprites and accurate sprite data.
    int sprite_table_data[NUM_SPRITES][SPRITE_TABLE_ENTRY_SIZE] = { 
	// Duck Wings Up.
	{
	    second, second, second, second,
	    second, second, second, second,
	    second, second, second, second,
	    second, second, second, second,

	},
	// Duck Wings Down.
	{
	    second, second, second, second,
	    second, second, second, second,
	    second, second, second, second,
	    second, second, second, second,
	},
	// Duck Dead.
	{
	    second, second, second, second,
	    second, second, second, second,
	    second, second, second, second,
	    second, second, second, second,
	}

    };

    int i = 0;
    for(; i < NUM_SPRITES; ++i){
	if (ioctl(fd, SPRITE_TABLE_WRITE_DATA, &sprite_table_data[i])) {
	    perror("ioctl(SPRITE_TABLE_WRITE_DATA) failed");
	    return 0;
	}
    }	
    return 1;
}

int write_color_table(int fd){

int color_table_data[NUM_SPRITES][COLOR_TABLE_ENTRY_SIZE] = {
     {black, black, black, black } 
};

    int i = 0;
    for(;i< NUM_SPRITES; ++i){
	if (ioctl(fd, COLOR_TABLE_WRITE_DATA, &color_table_data[i])) {
	    perror("ioctl(SPRITE_TABLE_WRITE_DATA) failed");
	    return 0;
	}
    }
}

int write_sprite_attr_table(int fd){
    // number of possible sprites. Zero initialize array.
    attr_table_entry_t entries[NUM_SPRITES] = {};
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
    entry.id = DUCK_SPRITE_ATTR_TABLE_OFFSET + duck->id; 
    entry.sprite = DUCK_SPRITE_OFFSET + duck->state; 
    entry.color_table = 0; 
    return entry;
}

int update_duck_attr(int fd, duck_t * ducks) {
    int i = 0;
    for(; i < NUM_DUCKS; ++i){
	attr_table_entry_t duck_attr = convert_duck_to_attr_entry(&ducks[i]);
	if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &duck_attr)) {
	    perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
	    return 0;
	}
    }	
    return 1;
}
