/*
 * Userspace program that communicates with the ppu device driver
 * through ioctls
 *
 */

#include <stdio.h>
#include "sprites.h"
#include "game/game.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define SECONDS_BETWEEN_SPAWNS 5 

int duck_hunt_fd;

void play_game(){

	while(1){

		// Set inintial game state.
		game_config_t game_data = {
			.bullets = kBulletsPerRound, 
			.score = 0, 
			.round = 0,
			.num_ducks_seen = 0,
			.visible_ducks = 0
		};

		// Set initial duck state. Value initialize array to all member variables are zero initialized. There will only ever be ducksperround ducks on the screen.
		duck_t ducks[NUM_DUCKS] = {};
		for(int i = 0; i < NUM_DUCKS; ++i){
			ducks[i].id = i;
			ducks[i].state = inactive;
		}
		
		coord_t cross_hair = { .x = 0, .y = 0};

		time_t last_spawned_time = time(0);
		printf("TIME %ld\n", last_spawned_time);

		while(!is_game_over(&game_data)){

			// Introduce a duck every 5 seconds if there are fewer than 2 ducks on the screen.
			time_t now = time(0);
			if(now - last_spawned_time > SECONDS_BETWEEN_SPAWNS 
					&& game_data.visible_ducks < NUM_DUCKS ) {

				//printf("trying to spawn duck\n");
				last_spawned_time = now;
				// spawn the first duck that is currently not visible.
				for(int i = 0; i < NUM_DUCKS; ++i){
					if(ducks[i].state == inactive){
						spawn_duck(&ducks[i], &game_data);
						break;
					}
				}

			}
			move_ducks(ducks, NUM_DUCKS, &game_data);
			for(int i = 0; i < NUM_DUCKS; ++i){
				if(ducks[i].state != inactive){
					update_duck_attr(duck_hunt_fd, ducks[i].coord.x, ducks[i].coord.y, ducks[i].state, ducks[i].id);
				}
			}
			update_game_state_attrs(duck_hunt_fd, game_data.bullets, game_data.score);
			if(is_round_over(&game_data)){
			    start_new_round(&game_data);
			}
			usleep(10000);	
		}
		printf("GAME_OVER");

	}
}

int main()
{
	static const char filename[] = "/dev/ppu";

	printf("Duck Hunt userspace program started\n");

	if ( (duck_hunt_fd = open(filename, O_RDWR)) == -1) {
		fprintf(stderr, "could not open %s\n", filename);
		return -1;
	}

	write_sprite_table(duck_hunt_fd);
	write_color_table(duck_hunt_fd);
	write_sprite_attr_table(duck_hunt_fd);

	play_game();

	printf("VGA BALL Userspace program terminating\n");
	return 0;
}
