#ifndef _GAME_H
#define _GAME_H

extern const int kHorizontalScreenSize;

// Confer with Bryce about how big these sprites are.
extern const int kDuckXSize;
extern const int kMaxDucksPerGame;

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


// Checks to see if a given shot has hit any of the ducks.
int shoot_at_ducks(duck_t* ducks, int num_ducks, coord_t cross_hair, game_config_t* config);

// Caclulates hit square associated with x,y position of the duck. Returns 1 if cross_hair is in the hit square. Returns 0 if cross_hair is outside of the hit square.
int calculate_hit(duck_t * duck, coord_t cross_hair);

int set_up_config(game_config_t * game_config);

// Deducts from bullet count, adds ducks value to the total score.
void kill_duck_update_config(duck_t * duck, game_config_t* config);

// Moves ducks across the x plane. (y plane if the duck is dead).
int move_duck(duck_t * duck);

// moves all of the ducks.
int move_ducks(duck_t* ducks, int num_ducks);

// game is over if we are out of bullets or if we've seen a set number of ducks.
int is_game_over(game_config_t * config, int num_ducks_seen);

#endif
