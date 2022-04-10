#include "game.h"

int calculate_hit(duck_t * duck, coord_t cross_hair){
	return cross_hair.x < (duck->coord.x + 5) && cross_hair.x > (duck->coord.x - 5)
			&& cross_hair.y < (duck->coord.y + 5) && cross_hair.y > (duck->coord.y - 5);
}

