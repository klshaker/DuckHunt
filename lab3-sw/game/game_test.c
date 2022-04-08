#include <stdio.h>
#include <assert.h>
#include "game.h"

int main(){

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
