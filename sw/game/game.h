/* This module contains all of the game specific logic for Duck Hunt. 
*/

#ifndef _GAME_H
#define _GAME_H
#include <time.h>


// Constants exposed for testing purposes.
extern const int kHorizontalScreenSize;
// how much vertical room the ducks have to move around ( how much sky there is on the screen ).
extern const int kVerticalScreenSize;
// Used to caluclate the bounding box for a cross hair. Essentially, how much 
// leeway to give users in the x and way directions when computing if they successfully shot a duck.
extern const int kCrossHairSquareSize;
// How big the ducks and the crosshair are.
extern const int kGraphicSize;
// Number of moves a duck can make on screen before it flies away.
extern const int kMaxNumDuckMoves;
// How many ducks to give the player an opportunity to shoot before we end the game.
extern const int kMaxDucksPerGame;

enum duck_state { flap_down, flap_up,  dead, flying_away };
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
	// Direction on x plane.
	enum direction x_direction;
	// Direction on y plane.
	enum direction y_direction;
	// Angle in degrees that ducks will move at an angle on the y plane to make game_play more interesting. 
	// an angle of 45 degrees denotes 1 unit of movement in the y plane for every one unit of movement in the x plane.
	double y_angle;
	// unique_id associated with each duck.
	int id; 
	enum duck_state state;
	// when the duck was created.
	time_t spawn_time; 
	int is_visible;
} duck_t;

typedef struct {
	unsigned char bullets, score, round;
	int num_ducks_seen;
	int visible_ducks;
} game_config_t;


// Checks to see if a given shot has hit any of the ducks.
int shoot_at_ducks(duck_t* ducks, int num_ducks, coord_t cross_hair, game_config_t* config);

// Caclulates hit square associated with x,y position of the duck. Returns 1 if cross_hair is in the hit square. Returns 0 if cross_hair is outside of the hit square.
int calculate_hit(duck_t * duck, coord_t cross_hair);

// Deducts from bullet count, adds ducks value to the total score.
void kill_duck_update_config(duck_t * duck, game_config_t* config);

// Moves a single duck across the x plane. (y plane if the duck is dead). Increments the num_ducks_seen in the game 
// config if the duck enters the flying away state.
int move_duck(duck_t * duck, game_config_t * game_config);

// moves all of the ducks.
int move_ducks(duck_t* ducks, int num_ducks, game_config_t * game_config);

// game is over if we are out of bullets or if we've seen a set number of ducks.
int is_game_over(game_config_t * config);
int spawn_duck(duck_t * duck, game_config_t * config);

#endif
