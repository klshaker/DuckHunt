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
				.x = kBulletSpriteXLoc + i * kGraphicSize + i * kBulletSpaceApart, 
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
			.coord = { .x = kScoreSpriteXLoc + i * kGraphicSize+ i* kScoreSpaceApart, .y = kLowerGraphicYLoc },
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
		.coord = {.x = kBulletSpriteXLoc, .y = kLowerGraphicYLoc - kGraphicSize - 10 },
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
				0x0,
				0x0,
				0x155400,
				0x555500,
				0x5aa500,
				0x5aa500,
				0x5eb500,
				0x5eb500,
				0x5eb500,
				0x5eb500,
				0x5aa500,
				0x5aa500,
				0x555500,
				0x155400,
				0x0,
				0x0,
			},

		},
		// Number Sprites
		// 0 
		[6] = {
			.id  = 0x6,
			.line = {
				0x0,
				0x555500,
				0x1555540,
				0x56aa950,
				0x5aaaa50,
				0x5a55a50,
				0x5a55a50,
				0x5a55a50,
				0x5a55a50,
				0x5a55a50,
				0x5a55a50,
				0x5aaaa50,
				0x56aa950,
				0x1555540,
				0x555500,
				0x0,
			},

		},
		// 1 
		[7] = {
			.id  = 0x7,
			.line = {
				0x0,
				0x15540,
				0x55540,
				0x15a940,
				0x16a940,
				0x169540,
				0x169540,
				0x169400,
				0x169400,
				0x1569540,
				0x1569540,
				0x16aa940,
				0x16aa940,
				0x1555540,
				0x1555540,
				0x0,
			},

		},
		// 2
		[8] = {
			.id = 0x8,
			.line = {
				0x0,
				0x555550,
				0x1555550,
				0x56aaa50,
				0x5aaaa50,
				0x5a55550,
				0x5a55540,
				0x5aaa950,
				0x56aaa50,
				0x1555a50,
				0x5555a50,
				0x5aaaa50,
				0x5aaaa50,
				0x5555550,
				0x5555550,
				0x0,
			}
		},
		// 3
		[9] = {
			.id = 0x9,
			.line = {
				0x0,
				0x555550,
				0x1555550,
				0x56aaa50,
				0x5aaaa50,
				0x5a55550,
				0x5a55550,
				0x5aaaa50,
				0x5aaaa50,
				0x5a55550,
				0x5a55550,
				0x5aaaa50,
				0x56aaa50,
				0x1555550,
				0x555550,
				0x0,
			}
		},
		// 4
		[10] = {
			.id = 10,
			.line = {
				0x0,
				0x5555550,
				0x5555550,
				0x5a55a50,
				0x5a55a50,
				0x5a55a50,
				0x5a55a50,
				0x5aaaa50,
				0x5aaaa50,
				0x5a55550,
				0x5a55550,
				0x5a50000,
				0x5a50000,
				0x5550000,
				0x5550000,
				0x0,
			}
		},
		// 5
		[11] = {
			.id = 11,
			.line = {
				0x0,
				0x5555550,
				0x5555550,
				0x5aaaa50,
				0x5aaaa50,
				0x5555a50,
				0x1555a50,
				0x56aaa50,
				0x5aaa950,
				0x5a55540,
				0x5a55550,
				0x5aaaa50,
				0x56aaa50,
				0x1555550,
				0x555550,
				0x0,
			}
		},
		// 6
		[12] = {
			.id = 12,
			.line = {
				0x0,
				0x5550,
				0x5550,
				0x5a50,
				0x5a50,
				0x555a50,
				0x1555a50,
				0x56aaa50,
				0x5aaaa50,
				0x5a55a50,
				0x5a55a50,
				0x5aaaa50,
				0x56aa950,
				0x1555540,
				0x555500,
				0x0,
			}
		},
		// 7
		[13] = {
			.id = 13,
			.line = {
				0x0,
				0x555550,
				0x1555550,
				0x56aaa50,
				0x5aaaa50,
				0x5a55550,
				0x5a55550,
				0x5a50000,
				0x5a50000,
				0x5a50000,
				0x5a50000,
				0x5a50000,
				0x5a50000,
				0x5550000,
				0x5550000,
				0x0,
			}
		},
		// 8
		[14] = {
			.id = 14,
			.line = {
				0x0,
				0x555500,
				0x1555540,
				0x56aa950,
				0x5aaaa50,
				0x5a55a50,
				0x5a55a50,
				0x5aaaa50,
				0x5aaaa50,
				0x5a55a50,
				0x5a55a50,
				0x5aaaa50,
				0x56aa950,
				0x1555540,
				0x555500,
				0x0,
			}
		},
		// 9
		[15] = {
			.id = 15,
			.line = {
				0x0,
				0x555500,
				0x1555540,
				0x56aa950,
				0x5aaaa50,
				0x5a55a50,
				0x5a55a50,
				0x5aaaa50,
				0x5aaa950,
				0x5a55540,
				0x5a55500,
				0x5a50000,
				0x5a50000,
				0x5550000,
				0x5550000,
				0x0,
			}
		},
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
				[1] = {.r = 111, .g = 62, .b = 67 },
				[2] = {.r = 244, .g = 180, .b = 27 },
				[3] = {.r = 254, .g = 228, .b = 129 },
			},
		},
		// Unshaded Bullet
		[2] =
		{
			.id = 0x2,
			.color = {
				[0] = {.r = 0,  .g = 0,   .b = 0  },
				[1] = {.r = 67, .g = 74, .b = 95 },
				[2] = {.r = 223, .g = 246, .b = 245 },
				[3] = {.r = 223, .g = 246, .b = 245 },
			},
		},
		// Numbers and Letters 
		[3] =
		{
			.id = 0x3,
			.color = {
				[0] = {.r = 0, .g = 0, .b = 0},
				[1] = {.r = 67, .g = 74, .b = 95 },
				[2] = {.r = 223, .g = 246, .b = 245 },
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

attr_table_entry_t convert_duck_to_attr_entry(duck_t* duck){
	attr_table_entry_t entry = {	
		.coord = { .x = duck->coord.x, .y = duck->coord.y }, 
		.id =  DUCK_ATTR_TABLE_OFFSET + duck->id, 
		.sprite =  DUCK_SPRITE_OFFSET + duck->state,
		.color_table = DUCK_COLOR_TABLE_OFFSET
	};
	return entry;
}

int update_game_state_attrs(int fd, game_config_t * game_data ){

	int i = 0;
	for(; i < NUM_BULLETS; ++i){
		if(game_data->bullets > i ){
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

	int tmp_score = game_data->score;
	i = NUM_SCORE_DIGITS;
	// work from lowest significant digit to highest significant digit. 
	for(; i > 0; --i) {
		attr_table[SCORE_ATTR_TABLE_OFFSET + i - 1].sprite = NUMBER_SPRITE_OFFSET + tmp_score % 10; 
	 	tmp_score = tmp_score / 10;	
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[SCORE_ATTR_TABLE_OFFSET + i - 1])) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}	
return 1;
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
