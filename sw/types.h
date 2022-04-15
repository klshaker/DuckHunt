#ifndef _TYPES_H_
#define _TYPES_H_

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

enum duck_state { flap_up, flap_down, dead, inactive };
// start with only being able to move on the x axis.
enum direction { east, west};

typedef struct {
	unsigned int x,y;
} coord_t;

typedef struct {
	// none of these values are larger than 16 bits
	unsigned int value;
	coord_t coord;
	enum direction x_direction;
	int id; // unique_id associated with each duck.
	enum duck_state state;
} duck_t;

typedef struct {
	// We should only need 8 bits for each of these
	unsigned char bullets, score, round;
} game_config_t;

typedef struct {
	duck_t ducks[1];
	coord_t cross_hair;
	game_config_t game_conf;
} all_game_data_t;

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

sprite_data_t sprites[NUM_SPRITES];

// Takes the duck in the game and pulls the info that is needed for the attr table for it.
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


#endif
