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
			.bullets = 3, 
			.score = 0, 
			.round = 0,
			.num_ducks_seen = 0,
			.visible_ducks = 0
		};

		// Set initial duck state. As in original game. ducks come out of the grass.
		duck_t ducks[NUM_DUCKS] = {
			{ 
				.value =  1,
				.coord= { .x = 200, .y = kVerticalScreenSize },
				.x_direction = east,
				.id = 0x0,
				.state = flap_up,
				.is_visible = 0
			},
			{ .value = 5,
				.coord= { .x = 250, .y = kVerticalScreenSize },
				.x_direction = east,
				.id = 0x1,
				.state = flap_up,
				.is_visible = 0
			}
		};

		coord_t cross_hair = { .x = 0, .y = 0};

		time_t last_spawned_time = time(0);
		printf("TIME %ld\n", last_spawned_time);

		while(!is_game_over(&game_data)){

			// Introduce a duck every 5 seconds if there are fewer than 2 ducks on the screen.
			time_t now = time(0);
			//printf("TIME %ld\n", now - last_spawned_time);
			
			if(now - last_spawned_time > SECONDS_BETWEEN_SPAWNS && game_data.visible_ducks < NUM_DUCKS ) {
				last_spawned_time = now;
				if(game_data.visible_ducks == 0){ 
					ducks[0].is_visible = 1;
					ducks[0].spawn_time = now;
				} 
				else {
				 	ducks[1].is_visible = 1; 
					ducks[1].spawn_time = now;
				}
				++game_data.visible_ducks;
			}
			// poll wii controller.
			// if trigger pressed
			move_ducks(ducks, NUM_DUCKS, &game_data);
			int i = 0;
			for(; i < NUM_DUCKS; ++i){
				update_duck_attr(duck_hunt_fd, ducks[i].coord.x, ducks[i].coord.y, ducks[i].state, ducks[i].id, ducks[i].is_visible);
			}
			update_game_state_attrs(duck_hunt_fd, game_data.bullets, game_data.score);
			usleep(10000);	
		}

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
