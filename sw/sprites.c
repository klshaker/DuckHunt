#include "sprites.h"
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>

const int kBulletSpriteXLoc = 5;
const int kScoreSpriteXLoc = 500;
const int kLowerGraphicYLoc = 400;
const int kBulletSpaceApart = 2;
const int kScoreSpaceApart = 0;
const int kSmallGraphicWidth = 16;
const int kSmallGraphicHeight = 16;

attr_table_entry_t attr_table[NUM_SPRITES] = {};

int build_sprite_attr_table(attr_table_entry_t * entries, int* num_entries){

	*num_entries = 0;
	int i = 0;
	for(;i < NUM_DUCKS; i++){
		attr_table_entry_t duck = {
			.coord = { .x = 0, .y = 0 },
			// duck starts off screen;
			.sprite = 0x0,
			.id = *num_entries,
			.color_table = DUCK_COLOR_TABLE_OFFSET,
		};
		entries[*num_entries] = duck;
		++(*num_entries);
	}

	i = 0;
	for(;i < NUM_BULLETS; ++i){
		attr_table_entry_t bullet = {
			.coord =  {
				.x = kBulletSpriteXLoc + i * kSmallGraphicWidth + i * kBulletSpaceApart, 
				.y = kLowerGraphicYLoc 
			},
			// all bullets start off shaded and on screen.
			.sprite = BULLET_SPRITE_OFFSET,
			.id = *num_entries,
			.color_table = SHADED_BULLET_COLOR_TABLE_OFFSET
		};
		entries[*num_entries] = bullet;
		++(*num_entries);
	}

	i = 0;
	for(;i< NUM_SCORE_DIGITS; ++i){
		attr_table_entry_t score = {
			.coord = { .x = kScoreSpriteXLoc + i * kSmallGraphicWidth+ i* kScoreSpaceApart, .y = kLowerGraphicYLoc },
			// score starts off 0 0
			.sprite = NUMBER_SPRITE_OFFSET,
			.id = *num_entries,
			//TODO(WHY WON"T THIS WORK WITH THE COLOR TABLE OFFSET OF 4?)
			// this should be SHADED_BULLET_COLOR_TABLE_OFFSET
			.color_table = SHADED_BULLET_COLOR_TABLE_OFFSET
		};
		entries[*num_entries] = score;
		++(*num_entries);
	}

	attr_table_entry_t round = {
		// Round sprite is right above bullets.  
		.coord = {.x = kBulletSpriteXLoc, .y = kLowerGraphicYLoc - kSmallGraphicHeight - 10 },
		// round starts at 0
		.sprite = NUMBER_SPRITE_OFFSET,
		.id = *num_entries,
		.color_table = SHADED_BULLET_COLOR_TABLE_OFFSET
	};

	entries[*num_entries] = round;
	++(*num_entries);

	attr_table_entry_t crosshair;
	// TODO(kristenshaker): change these coords
	crosshair.coord.x = 600;
	crosshair.coord.y = 10;
	crosshair.sprite = CROSSHAIR_SPRITE_OFFSET;
	crosshair.id = *num_entries;
	crosshair.color_table = 0x1;

	entries[*num_entries]=crosshair;
	++(*num_entries);

	return 1;
}


int write_sprite_table(int fd){

	// This data is read into FPGA memory once at start up time. It is not required 
	// anywhere else, so it will be kept a local variable.
	// TODO(kristenshaker): populate this table with the rest of the sprites and accurate sprite data.
	sprite_table_entry_t sprites[NUM_SPRITES] = {
		// Sprite not on the screen.
		[0] = {
			.id  = 0x0,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},
		},
		// Duck Flap Up
		[1] = {
			.id  = 0x1,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Duck Flap Down
		[2] = {
			.id  = 0x2,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},
		},
		// Duck Dead
		[3] = {
			.id  = 0x3,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Duck Flying Away
		[4] = {
			.id  = 0x4,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Bullet Shaded & Non Shaded
		[5] = {
			.id  = 0x5,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Number Sprites
		// 0 
		[6] = {
			.id  = 0x6,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// 1 
		[7] = {
			.id  = 0x7,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// 2 
		[8] = {
			.id  = 0x8,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// 3 
		[9] = {
			.id  = 0x9,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// 4 
		[10] = {
			.id  = 0xA,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// 5 
		[11] = {
			.id  = 0xB,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		}

	};

	int i = 0;
	for(; i < NUM_SPRITES; ++i){
		if (ioctl(fd, SPRITE_TABLE_WRITE_DATA, &sprites[i])) {
			perror("ioctl(SPRITE_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}	
	return 1;
}

int write_color_table(int fd){

	color_table_entry_t color_tables[NUM_SPRITES] = 
	{
		// Duck
		[0] = {
			.id = 0x0,
			.color = {
				[0] = {.r = 0,  .g = 0,   .b = 0  },
				[1] = {.r = 0,  .g = 101, .b = 0  },
				[2] = {.r = 0,  .g = 255, .b = 0  },
				[3] = {.r = 0,  .g = 0,   .b = 255},
			},
		},
		// Shaded Bullet
		[1] =
		{
			.id = 0x1,
			.color = {
				[0] = {.r = 0,  .g = 0,   .b = 0  },
				[1] = {.r = 0,  .g = 101, .b = 0  },
				[2] = {.r = 0,  .g = 255, .b = 0  },
				[3] = {.r = 0,  .g = 0,   .b = 255},
			},
		},
		// Unshaded Bullet
		[2] =
		{
			.id = 0x2,
			.color = {
				[0] = {.r = 0,  .g = 0,   .b = 0  },
				[1] = {.r = 0,  .g = 101, .b = 0  },
				[2] = {.r = 0,  .g = 255, .b = 0  },
				[3] = {.r = 0,  .g = 0,   .b = 255},
			},
		},
		// Numbers and Letters 
		[3] =
		{
			.id = 0x3,
			.color = {
				[0] = {.r = 0,  .g = 0,   .b = 0  },
				[1] = {.r = 0,  .g = 101, .b = 0  },
				[2] = {.r = 0,  .g = 255, .b = 0  },
				[3] = {.r = 0,  .g = 0,   .b = 255},
			},
		},
		// TODO( shouldn't need this but nothing shows up when we use color table 0 )
		[4] =
		{
			.id = 0x4,
			.color = {
				[0] = {.r = 0,  .g = 0,   .b = 0  },
				[1] = {.r = 0,  .g = 101, .b = 0  },
				[2] = {.r = 0,  .g = 255, .b = 0  },
				[3] = {.r = 0,  .g = 0,   .b = 255},
			},
		}

	};

	int i = 0;
	for(;i< NUM_SPRITES; ++i){
		if (ioctl(fd, COLOR_TABLE_WRITE_DATA, &color_tables[i])) {
			perror("ioctl(COLOR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}
}

int write_sprite_attr_table(int fd){
	int num_entries_actual = 0;
	if(!build_sprite_attr_table(attr_table, &num_entries_actual)){

		return 0;
	}
	int i = 0;
	for(; i < num_entries_actual; ++i){
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[i])) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		} 
	}
}


int update_game_state_attrs(int fd, int num_bullets, int score){

	int i = 0;
	for(; i < NUM_BULLETS; ++i){
		if(num_bullets > i ){
			attr_table[BULLET_ATTR_TABLE_OFFSET + i].color_table = SHADED_BULLET_COLOR_TABLE_OFFSET;
		}
		else {
			attr_table[BULLET_ATTR_TABLE_OFFSET + i].color_table = UNSHADED_BULLET_COLOR_TABLE_OFFSET;
		}	
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[BULLET_ATTR_TABLE_OFFSET +i])) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}

	i = NUM_SCORE_DIGITS;
	// work from lowest significant digit to highest significant digit. 
	for(; i > 0; --i) {
		attr_table[SCORE_ATTR_TABLE_OFFSET + i - 1].sprite = NUMBER_SPRITE_OFFSET + score % 10; 
		score = score / 10;	
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[SCORE_ATTR_TABLE_OFFSET + i - 1])) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}	
	return 1;
}

int update_duck_attr(int fd, int x_coord, int y_coord, int duck_state, int duck_id) {

	attr_table[DUCK_ATTR_TABLE_OFFSET + duck_id].coord.x = x_coord;
	attr_table[DUCK_ATTR_TABLE_OFFSET + duck_id].coord.y = y_coord;
	attr_table[DUCK_ATTR_TABLE_OFFSET + duck_id].sprite  =  DUCK_SPRITE_OFFSET + duck_state;

	if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[DUCK_ATTR_TABLE_OFFSET + duck_id])) {
		perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
		return 0;
	}

	return 1;
}
