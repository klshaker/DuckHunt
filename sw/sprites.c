#include "sprites.h"
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

const int kBulletSpriteXLoc = 5;
const int kScoreSpriteXLoc = 500;
const int kLowerGraphicYLoc = 400;
const int kBulletSpaceApart = 2;
const int kScoreSpaceApart = 0;
const int kSmallGraphicWidth = 16;
const int kSmallGraphicHeight = 16;

attr_table_entry_t attr_table[NUM_SPRITES] = {};

int build_sprite_attr_table(attr_table_entry_t * entries){

	int num_entries = 0;
	int i = 0;
	for(;i < NUM_DUCKS * NUM_SPRITES_PER_DUCK; ++i){
		attr_table_entry_t duck = {
			.coord = { .x = 0, .y = 0 },
			// duck starts off screen;
			.sprite = 0x0,
			.id = num_entries,
			.color_table = DUCK_COLOR_TABLE_OFFSET,
		};
		entries[num_entries] = duck;
		++(num_entries);
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
			.id = num_entries,
			.color_table = SHADED_BULLET_COLOR_TABLE_OFFSET
		};
		entries[num_entries] = bullet;
		++(num_entries);
	}

	i = 0;
	for(;i< NUM_SCORE_DIGITS; ++i){
		attr_table_entry_t score = {
			.coord = { .x = kScoreSpriteXLoc + i * kSmallGraphicWidth+ i* kScoreSpaceApart, .y = kLowerGraphicYLoc },
			// score starts off 0 0
			.sprite = NUMBER_SPRITE_OFFSET,
			.id = num_entries,
			//TODO(WHY WON"T THIS WORK WITH THE COLOR TABLE OFFSET OF 4?)
			// this should be SHADED_BULLET_COLOR_TABLE_OFFSET
			.color_table = NUMBER_LETTER_COLOR_TABLE_OFFSET
		};
		entries[num_entries] = score;
		++(num_entries);
	}

	attr_table_entry_t round = {
		// Round sprite is right above bullets.  
		.coord = {.x = kBulletSpriteXLoc, .y = kLowerGraphicYLoc - kSmallGraphicHeight - 10 },
		// round starts at 0
		.sprite = NUMBER_SPRITE_OFFSET,
		.id = num_entries,
		.color_table = NUMBER_LETTER_COLOR_TABLE_OFFSET
	};

	entries[num_entries] = round;
	++(num_entries);

	attr_table_entry_t crosshair;
	// TODO(kristenshaker): change these coords
	printf("Crosshair at: %d \n", num_entries);
	crosshair.coord.x = 600;
	crosshair.coord.y = 10;
	crosshair.sprite = CROSSHAIR_SPRITE_OFFSET;
	crosshair.id = num_entries;
	crosshair.color_table = 0x1;

	entries[num_entries]=crosshair;

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
		// Duck Flap Down Top Left
		[1] = {
			.id  = 0x1,
			.line = {
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x15000000,
				0x55550000,
				0x55555400,
				0x55555554,
				0x55555555,
				0x55555558,
				0x55555560,
				0x55555580,
				0x55565a80,
				0x5556aa00,
				0x555aa800,
			},
		},
		// Duck Flap Down Top Right
		[2] = {
			.id  = 2,
			.line = {
				0x555ac000,
				0x5553ff00,
				0x5560ff00,
				0x55603f00,
				0x55800c00,
				0x59800000,
				0x9a000000,
				0xa0000000,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Flap Down Bottom Left
		[3] = {
			.id  = 3,
			.line = {
				0x0,
				0x3bc000,
				0xeaf000,
				0xdafc00,
				0x3daff00,
				0x3feaff90,
				0x3ffbff95,
				0x3fffff95,
				0x3ffe95,
				0xe55,
				0x55,
				0x5,
				0x2,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Flap Down Bottom Right
		[4] = {
			.id  = 4,
			.line = {
				0x1,
				0x1,
				0x1,
				0x1,
				0x5,
				0x5,
				0x5,
				0x15,
				0x16,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Flap Up Top Left
		[5] = {
			.id  = 5,
			.line = {
				0x0,
				0x50000000,
				0x64000000,
				0xa9800000,
				0xaa900000,
				0xaa900000,
				0xaaa00000,
				0xaaa00000,
				0xaaa00000,
				0xaaa80000,
				0x6aa80000,
				0x2aa80000,
				0x2aa80000,
				0x6aa94000,
				0x5aa95500,
				0x5aa95554,
			},
		},
		// Duck Flap Up Top Right
		[6] = {
			.id  = 6,
			.line = {
				0x5aa95555,
				0xaaa95558,
				0xaaa95560,
				0xaaaa5680,
				0x2aaaaa80,
				0x2aaaa00,
				0x2aa800,
				0x2c000,
				0xff00,
				0x3f00,
				0xf00,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Flap Up Bottom Left
		[7] = {
			.id  = 7,
			.line = {
				0x14,
				0x19,
				0x1a,
				0x6,
				0x6,
				0x2,
				0x1,
				0x0,
				0xbc000,
				0x2af000,
				0x1afc00,
				0xdaff00,
				0x3feaff90,
				0x3ffbff95,
				0x3fffff95,
				0xffe95,
			},
		},
		// Duck Flap Up Bottom Right
		[8] = {
			.id  = 8,
			.line = {
				0x255,
				0x15,
				0x2,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Dead Top
		[9] = {
			.id  = 9,
			.line = {
				0x0,
				0x110000,
				0x150000,
				0x58000,
				0x6a300,
				0x2896af20,
				0x2896bf2c,
				0x2656bf7f,
				0x1596bfaf,
				0x1565afaf,
				0x1565aaaf,
				0x1559aaac,
				0x1555aa00,
				0x15556a00,
				0x5556a00,
				0x1556a00,
			},
		},
		// Duck Dead Bottom
		[10] = {
			.id  = 10,
			.line = {
				0x556800,
				0x556800,
				0x156400,
				0x155000,
				0x55000,
				0x54000,
				0x54000,
				0xa8000,
				0xfc000,
				0x3ffc00,
				0x3fff30,
				0xffaff0,
				0xfe6bc0,
				0xfd57fc,
				0x3d54ff,
				0x0,
			},
		},
		// Duck Dead Empty
		[11] = {
			.id  = 11,
			.line = {
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Dead Empty 2
		[12] = {
			.id  = 12,
			.line = {
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
				0x0,
			},
		},
		// Duck Flying Away TODO
		[13] = {
			.id  = 13,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Duck Flying Away TODO
		[14] = {
			.id  = 14,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Duck Flying Away TODO
		[15] = {
			.id  = 15,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Duck Flying Away TODO
		[16] = {
			.id  = 16,
			.line = {
				0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
				0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
				0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
				0x55555555, 0x55555555, 0x55555555, 0x55555555,
			},

		},
		// Bullet Shaded & Non Shaded
		[17] = {
			.id  = 17,
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
		[18] = {
			.id  = 18,
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
		[19] = {
			.id  = 19,
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
		[20] = {
			.id = 20,
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
		[21] = {
			.id = 21,
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
		[22] = {
			.id = 22,
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
		[23] = {
			.id = 23,
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
		[24] = {
			.id = 24,
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
		[25] = {
			.id = 25,
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
		[26] = {
			.id = 26,
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
		[27] = {
			.id = 27,
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
		// Crosshair
		[28] = {
			.id = 28,
			.line = {
				0x0,
				0x0,
				0x0,
				0x0,
				0xfc3f00,
				0xffff00,
				0xffff00,
				0x3ffc00,
				0x3ffc00,
				0xffff00,
				0xffff00,
				0xfc3f00,
				0x0,
				0x0,
				0x0,
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
				[0] = {.r = 0, .g = 0, .b = 0},
				[1] = {.r = 0, .g = 0, .b = 168 },
				[2] = {.r = 252, .g = 252, .b = 252 },
				[3] = {.r = 188, .g = 0, .b = 188 },
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
	for(;i< NUM_COLOR_TABLE_ENTRIES; ++i){
		if (ioctl(fd, COLOR_TABLE_WRITE_DATA, &color_tables[i])) {
			perror("ioctl(COLOR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}
}

int write_sprite_attr_table(int fd){
	if(!build_sprite_attr_table(attr_table)){

		return 0;
	}
	int i = 0;
	for(; i < NUM_ATTR_TABLE_ENTRIES; ++i){
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

int update_duck_attr(int fd, int x_coord, int y_coord, int duck_state, int duck_id, int visible) {

	if(!visible){
		return 1;
	}	
	int i = 0;
	for(; i < NUM_SPRITES_PER_DUCK; ++i){

		int attr_table_entry = DUCK_ATTR_TABLE_OFFSET + duck_id * NUM_SPRITES_PER_DUCK + i;
		attr_table[attr_table_entry].coord.x = x_coord + SPRITE_TABLE_ENTRY_SIZE * (i / 2);
		attr_table[attr_table_entry].coord.y = y_coord + SPRITE_TABLE_ENTRY_SIZE * (i % 2) ;
		attr_table[attr_table_entry].sprite  = DUCK_DOWN_SPRITE_OFFSET + duck_state * NUM_SPRITES_PER_DUCK + i ;
		
		printf("printing for duck %d at attr entry %d sprite number %d :\n", duck_id, attr_table_entry, attr_table[attr_table_entry].sprite);
		if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[attr_table_entry])) {
			perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
			return 0;
		}
	}


	return 1;
}

int update_crosshair_attr(int fd, int x_coord, int y_coord) {
	int attr_table_entry = CROSSHAIR_ATTR_TABLE_OFFSET;
	attr_table[attr_table_entry].coord.x = x_coord;
	attr_table[attr_table_entry].coord.y = y_coord;

	if (ioctl(fd, ATTR_TABLE_WRITE_DATA, &attr_table[attr_table_entry])) {
		perror("ioctl(ATTR_TABLE_WRITE_DATA) failed");
		return 0;
	}
	return 1;
}
