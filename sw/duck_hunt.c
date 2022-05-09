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

int duck_hunt_fd;

void play_game(){

	time_t now = time(0);
	printf("TIME %ld\n", now);

	while(1){

		// Set inintial game state.
		game_config_t game_data = {
			.bullets = 3, 
			.score = 0, 
			.round = 0,
			.num_ducks_seen = 0
		};

		// Set initial duck state. As in original game. ducks come out of the grass.
		duck_t ducks[NUM_DUCKS] = {
			{ 
				.value =  1,
				.coord= { .x = 200, .y = kVerticalScreenSize },
				.x_direction = east,
				.id = 0x0,
				.state = flap_up,
			},
			{ .value = 5,
				.coord= { .x = 250, .y = kVerticalScreenSize },
				.x_direction = east,
				.id = 0x1,
				.state = flap_up,
			}
		};

		coord_t cross_hair = { .x = 0, .y = 0};

		while(!is_game_over(&game_data)){

			// poll wii controller.
			// if trigger pressed
			move_ducks(ducks, NUM_DUCKS, &game_data);
			int i = 0;
			for(; i < NUM_DUCKS; ++i){
				update_duck_attr(duck_hunt_fd, ducks[i].coord.x, ducks[i].coord.y, ducks[i].state, ducks[i].id);
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
