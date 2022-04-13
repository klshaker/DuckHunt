#include "game.h"
#include "stdio.h"

const int kHorizontalScreenSize = 640;

// Confer with Bryce about how big these sprites are.
const int kDuckXSize = 10;


int calculate_hit(duck_t * duck, coord_t cross_hair){
	return cross_hair.x < (duck->coord.x + 5) && cross_hair.x > (duck->coord.x - 5)
		&& cross_hair.y < (duck->coord.y + 5) && cross_hair.y > (duck->coord.y - 5);
}

int move_duck(duck_t * duck){

	// a dead duck should not move at all on the x plane. It should drop down where it was shot.
	if(duck->state == dead && duck->coord.y !=0){
		duck->coord.y--;	
		return 1;
	}
	if(duck->x_direction == east){
		duck->coord.x++;
	}
	if(duck->x_direction == west){
		duck->coord.x--;
	}
	// can't check for below 0 with unsigned ints. Have to make sure we switch directions here.
	if(duck->coord.x == 0){  
		duck->x_direction = east;
	}
	if(duck->coord.x == kHorizontalScreenSize){
		duck->x_direction = west;
	}
	return 1;
}

void kill_duck_update_config(duck_t * duck, game_config_t* config){
	duck->state = dead;
	config->score += duck->value;
	config->bullets--;
}

int shoot_at_ducks(duck_t* ducks, int num_ducks, coord_t cross_hair, game_config_t* config){

	for(int i = 0; i < num_ducks; i++){
		int hit = calculate_hit(&ducks[i], cross_hair);
		if(hit){
			kill_duck_update_config(&ducks[i], config);
		}	

	}

	return 1;
}
