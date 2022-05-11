#include "game.h"
#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

const int kVerticalScreenSize = 300;
const int kHorizontalScreenSize = 640;
const double kPI = 3.14159;
const int kMaxDuckTimeSeconds = 3;
const int kRoundsPerGame = 6;
const int kCrossHairSquareSize = 10;
const int kGraphicSize = 32;
const int kBulletsPerRound = 3;

coord_t get_center_of_graphic(coord_t* top_left) {
	return (coord_t){.x = top_left->x + kGraphicSize/2, .y = top_left->y + kGraphicSize/2};
}

int calculate_hit(duck_t * duck, coord_t cross_hair){
	coord_t cross_hair_center = get_center_of_graphic(&cross_hair);
	coord_t duck_center = get_center_of_graphic(&duck->coord);

	return duck->state != inactive && duck->state != flying_away && duck->state != dead && cross_hair_center.x < (duck_center.x + kCrossHairSquareSize) && cross_hair_center.x > (duck_center.x - kCrossHairSquareSize)
		&& cross_hair_center.y < (duck_center.y + kCrossHairSquareSize) && cross_hair_center.y > (duck_center.y - kCrossHairSquareSize);
}

int move_ducks(duck_t* ducks, int num_ducks, game_config_t * game_config){
	for(int i = 0; i < num_ducks; ++i){
		move_duck(&ducks[i], game_config);
	}
}

int move_duck(duck_t * duck, game_config_t * game_config){

	if(duck->state == inactive) return 1;
	// A dead duck should not move at all on the x plane. It should drop down where it was shot. Dropping in our coordinate system means adding to the y coord.
	if(duck->state == dead ){
		if(duck->coord.y < kVerticalScreenSize + kGraphicSize){
			++duck->coord.y;	
		}
		return 1;
	}
	// A flying away duck should not move on the x plane. It should leave the screen by flyinga directly upward. 
	if(duck->state == flying_away ){
		if(duck->coord.y > 0 - kGraphicSize){
			duck->coord.y--;
		}
		else {
			printf("flew off screen\n");
			duck->state = inactive;
			--game_config->visible_ducks;
			printf("visible ducks:%d\n", game_config->visible_ducks);
		}	
		return 1;
	}
	if(duck->coord.x <= 0 || (rand() % 256 == 0)) {
		duck->x_direction = east;
		duck->y_angle = rand() % 45;
	}
	// right edge of the graphic at the edge of the screen
	else if(duck->coord.x >= kHorizontalScreenSize - kGraphicSize - 1 || (rand() % 256 == 0)){
		duck->x_direction = west;
		duck->y_angle = rand() % 45;
	}
	// at the top of the screen
	if(duck->coord.y <= 0 || (rand() % 256 == 0)) {
		duck->y_direction = south;
		duck->state = flap_down;
		duck->y_angle = rand() % 45;
	}
	else if(duck->coord.y >= kVerticalScreenSize - kGraphicSize - 1 || (rand() % 256 == 0)) {
		duck->y_direction = north;
		duck->y_angle = rand() % 45;
	}
	// Otherwise a duck should continue moving in the x and y direction it was previously.
	if(duck->x_direction == east){
		duck->coord.x += ceil(duck->velocity * cos(duck->y_angle*kPI/180.0));
	}
	else if(duck->x_direction == west){
		duck->coord.x -= ceil(duck->velocity * cos(duck->y_angle*kPI/180.0));
	}
	if(duck->y_direction == north){
		// convert to radians and calculate the change in y given a change of 1 unit in the x direction.
		// calculations need to take place as doubles and then be ceiled so they will make sense as ints.
		duck->coord.y -= ceil(duck->velocity * sin(duck->y_angle*kPI/180.0));
		//printf("angle %f\n", duck->y_angle);
		//printf("tan: %f\n", tan(duck->y_angle*kPI/180.0));
	}
	else if(duck->y_direction == south){
		// convert to radians and calculate the change in y given a change of 1 unit in the x direction.
		duck->coord.y += ceil(duck->velocity * sin(duck->y_angle*kPI/180.0));
	}
	if(time(0) - duck->spawn_time  > kMaxDuckTimeSeconds){
		duck->state = flying_away;
	}
	if(duck->y_direction == north){
		duck->state = (time(0) % 2) ? flap_up : flap_down;
	}	
	return 1;
}

void kill_duck_update_config(duck_t * duck, game_config_t* config){
	duck->state = dead;
	config->score += duck->value;
	config->visible_ducks--;
}

int shoot_at_ducks(duck_t* ducks, int num_ducks, coord_t cross_hair, game_config_t* config){

	for(int i = 0; i < num_ducks; i++){
		int hit = calculate_hit(&ducks[i], cross_hair);
		if(hit){
			kill_duck_update_config(&ducks[i], config);
		}	
	}

	--config->bullets;

	return 1;
}

// The round is over only if we have seen all the allowed ducks per round
int is_round_over(game_config_t * config){
	return config->spawned_ducks == NUM_DUCKS_PER_ROUND && config->visible_ducks == 0;
}

int is_game_over(game_config_t * config){
	return config->round == kRoundsPerGame + 1; 
}

int start_new_round(game_config_t * config){
	++config->round;
	config->bullets = kBulletsPerRound;
	config->visible_ducks = 0;
	config->spawned_ducks = 0;
}

int spawn_duck(duck_t * duck, game_config_t * config){
	
	duck->coord.x = 250;
	duck->coord.y = kVerticalScreenSize;
	duck->spawn_time = time(0);
	duck->value = rand() % 10;
	duck->state = flap_up;
	duck->velocity = 2 + config->round/2;
	// Randomly pick whether the duck starts moving east or west.
	duck->x_direction = rand() % 2; 
	// Duck always starts moving upward since it is coming out of the grass.
	duck->y_direction = north;

	config->visible_ducks++;
	config->spawned_ducks++;

}
