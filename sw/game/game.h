#ifndef _GAME_H
#define _GAME_H

// Constants exposed for testing purposes.
extern const int kHorizontalScreenSize;
extern const int kCrossHairSquareSize;
extern const int kGraphicSize;
extern const int kVerticalScreenSize;

enum duck_state { flap_up, flap_down, dead, inactive, flying_away };
// east and west denote movement on the x plane. north and south denote movement
// on the y plane.
enum direction { east, west, north, south };

typedef struct {
	// signed so that we can go negative when sprite is partially on the screen.
	int x,y;
} coord_t;

typedef struct {
	// How many points the duck is worth in the game.
	int value;
	// Where the duck currently is on the screen.
	coord_t coord;
	enum direction x_direction;
	enum direction y_direction;
	// Angle in degrees that ducks will move at an angle on the y plane to make game_play more interesting. 
	// an angle of 45 degrees denotes 1 unit of movement in the y plane for every one unit of movement in the x plane.
	double y_angle;
	// unique_id associated with each duck.
	int id; 
	enum duck_state state;
	// The number of times the duck has moved on screen used to approximate time the user has to shoot the duck.
	int num_moves; 
} duck_t;

typedef struct {
	unsigned char bullets, score, round;
	int num_ducks_seen;
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
