#include <stdio.h>
#include <assert.h>
#include "game.h"

int test_calculate_hit(){

	duck_t duck;
	duck.coord.x = 10;
	duck.coord.y = 15;
	coord_t cross_hair;
	cross_hair.x = 0; 
	cross_hair.y = 0;

	// x and y are dead on
	cross_hair.x = 10; 
	cross_hair.y = 15;
	assert(calculate_hit(&duck, cross_hair) ==1);

	// y is in range but x is out of range.
	cross_hair.x = 35;
	assert(calculate_hit(&duck, cross_hair) ==0);

	// x is in range but y is out of range.
	cross_hair.x = 10;
	cross_hair.y = 35;
	assert(calculate_hit(&duck, cross_hair)== 0);

	// both x and y are out of range 
	cross_hair.x = 35;
	assert(calculate_hit(&duck, cross_hair) ==0);

	// x is just out of range
	cross_hair.x = 5 ;
	cross_hair.y = 15;
	assert(calculate_hit(&duck, cross_hair) == 0);

	// x is just in range
	cross_hair.x = 6;
	cross_hair.y = 15;
	assert(calculate_hit(&duck, cross_hair) == 1);

}
void test_move_duck(){
	duck_t duck; 
	duck.coord.x = 0;
	duck.x_direction = east;
	int success = move_duck(&duck);
	assert(success == 1);
	assert(duck.coord.x == 1);
	assert(duck.x_direction == east);

	duck.coord.x = 0;
	// gets duck to 639
	for(int i = 0; i < kHorizontalScreenSize-1; i++){
		assert(duck.coord.x == i);
		int success = move_duck(&duck);
		assert(success == 1);
		assert(duck.coord.x == i + 1 );
		assert(duck.x_direction == east);
	}

	// moves duck to 640, where we should set direction to west 
	success = move_duck(&duck);
	assert(success == 1);
	assert(duck.coord.x == kHorizontalScreenSize);
	assert(duck.x_direction == west);


	for(int i = kHorizontalScreenSize; i > 1; --i){
		assert(duck.coord.x == i);
		int success = move_duck(&duck);
		assert(success == 1);
		assert(duck.coord.x == i-1);
		assert(duck.x_direction == west);
	}

	assert(duck.coord.x == 1);
	success = move_duck(&duck);
	assert(success == 1);
	assert(duck.coord.x == 0);
	assert(duck.x_direction == east);

	success = move_duck(&duck);
	assert(success == 1);
	assert(duck.coord.x == 1);
	assert(duck.x_direction == east);


	// dead ducks don't move on the x plane and fall to the ground.
	duck_t dead_duck;
	dead_duck.state = dead;
	dead_duck.coord.x = 52;
	dead_duck.coord.y = 300;
	for(int i =0; i < 500; i++){
		move_duck(&dead_duck);
	}
	assert(dead_duck.coord.x==52);
	assert(dead_duck.coord.y ==0);
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

int main() {
	test_calculate_hit();
	test_move_duck();
	test_kill_duck_update_score();
}
