#include <stdio.h>
#include <assert.h>
#include "game.h"

int test_calculate_hit(){

	duck_t duck = {
		.coord = { 
			.x = 10, 
			.y = 16
		}
	};
	coord_t cross_hair = { .x = 0, .y = 0};

	// x and y are dead on
	cross_hair.x = 10; 
	cross_hair.y = 16;
	assert(calculate_hit(&duck, cross_hair) == 1);

	// y is in range but x is out of range in either direction
	cross_hair.x = duck.coord.x + kCrossHairSquareSize; 
	assert(calculate_hit(&duck, cross_hair) == 0);

	cross_hair.x = duck.coord.x - kCrossHairSquareSize;
	assert(calculate_hit(&duck, cross_hair) == 0);

	// x is just in range in either direction. Should hit.
	cross_hair.x = duck.coord.x + kCrossHairSquareSize -1;
	assert(calculate_hit(&duck, cross_hair) == 1);
	
	cross_hair.x = duck.coord.x - kCrossHairSquareSize +1;
	assert(calculate_hit(&duck, cross_hair) == 1);

	// x is in range but y is out of range.
	cross_hair.x = 10;
	cross_hair.y = duck.coord.y + kCrossHairSquareSize;
	assert(calculate_hit(&duck, cross_hair) == 0);

	cross_hair.y = duck.coord.y - kCrossHairSquareSize;
	assert(calculate_hit(&duck, cross_hair) == 0);
	
	// y is just in range in either direction. should hit 
	cross_hair.y = duck.coord.y + kCrossHairSquareSize -1;
	assert(calculate_hit(&duck, cross_hair) == 1);
	
	cross_hair.y = duck.coord.y - kCrossHairSquareSize + 1;
	assert(calculate_hit(&duck, cross_hair) == 1);

	// both x and y are wildly out of range 
	cross_hair.x = 100;
	cross_hair.y = 100;
	assert(calculate_hit(&duck, cross_hair) == 0);

	// ducks that are dead or flying away cannot be hit.
	duck.state = flying_away;
	assert(calculate_hit(&duck, cross_hair) == 0);

	duck.state = dead;
	assert(calculate_hit(&duck, cross_hair) == 0);

}

void test_move_duck(){
	
	duck_t duck = {
		.coord = { .x = 200, .y = 200},
		.x_direction = east,
		.y_direction = north,
		.y_angle = 45
	};

	game_config_t config = {
		.num_ducks_seen = 0
	};
	// Basic test. assert that moving the duck starting at 0, 0 with a 45 degree angle moves the duck 1 unit in the 
	// x direction and 1 unit in the y direction.
	int success = move_duck(&duck, &config);
	assert(success == 1);
	assert(duck.coord.x == 201);
	assert(duck.x_direction == east);
	//printf("%d\n", duck.coord.y);
	assert(duck.coord.y == 199);
	assert(duck.y_direction == north);

	duck.coord.x = 1;
	duck.y_angle = 0;

	// Should move duck all the way to the edge of the screen.
	// Starting at 1 since 0 is a special case.
	for(int i = 1; i < kHorizontalScreenSize - kGraphicSize - 1; ++i){
		assert(duck.coord.x == i);
		int success = move_duck(&duck, &config);
		assert(success == 1);
		assert(duck.coord.x == i + 1 );
		assert(duck.coord.y == 199);
		assert(duck.x_direction == east);
	}

	assert(duck.coord.x == kHorizontalScreenSize - kGraphicSize - 1);

	duck.coord.x = kHorizontalScreenSize - kGraphicSize;
	for(int i = duck.coord.x ; i > 0; --i){
		assert(duck.coord.x == i);
		int success = move_duck(&duck, &config);
		assert(success == 1);
		assert(duck.coord.x == i-1);
		assert(duck.x_direction == west);
	}

	assert(duck.coord.x == 0);

	success = move_duck(&duck, &config);
	assert(success == 1);
	assert(duck.coord.x == 1);
	assert(duck.x_direction == east);

	// dead ducks don't move on the x plane and fall to the ground.
	duck_t dead_duck;
	dead_duck.state = dead;
	dead_duck.coord.x = 52;
	dead_duck.coord.y = 20;
	for(int i = 0; i < 300; i++){
		move_duck(&dead_duck, &config);
	}

	printf("%d\n", dead_duck.coord.x);
	printf("%d\n", dead_duck.coord.y);
	assert(dead_duck.coord.x == 52);
	assert(dead_duck.coord.y == kVerticalScreenSize + kGraphicSize );

	duck_t flies_away = {
		.coord = {
			.x = 200,
			.y = 200
		},
	};

	for(int i = 0; i <= kMaxNumDuckMoves; ++i){
		move_duck(&flies_away, &config);
	}

	assert(flies_away.state == flying_away);
	assert(config.num_ducks_seen == 1); 
}


void test_kill_duck_update_score(){
	game_config_t config;
	config.bullets = 3;
	config.score = 0;
	config.round = 0;

	duck_t ducks[2] = {};
	ducks[0].coord.x = 5;
	ducks[0].coord.y = 10;
	ducks[0].value = 5;

	ducks[1].coord.x = 200;
	ducks[1].coord.y = 200;
	ducks[1].value = 5;

	// We should hit duck one 
	coord_t cross_hair;
	cross_hair.x = 5;
	cross_hair.y = 10;

	shoot_at_ducks(ducks, 2, cross_hair, &config);
	assert(config.score == 5);
	assert(ducks[0].state == dead);
	assert(ducks[1].state !=dead);
	assert(config.bullets == 2);
}

void test_game_over(){
	game_config_t config;
	config.bullets = 3;
	config.score = 0;
	config.round = 0;
	int num_ducks_seen = 0;

	assert(is_game_over(&config, num_ducks_seen) == 0);
	config.bullets = 0;
	assert(is_game_over(&config, num_ducks_seen) == 1);
	config.bullets = 3;
	num_ducks_seen = 8;
	assert(is_game_over(&config, num_ducks_seen) == 1);
}


int main() {
	test_calculate_hit();
	test_move_duck();
	test_kill_duck_update_score();
	test_game_over();
}
