/*
 * Userspace program that communicates with the vga_ball device driver
 * through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
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

int duck_hunt_fd;

void play_game(){

	while(1){

		// Set inintial game state.
		game_config_t config = {
			.bullets = 3, 
			.score = 0, 
			.round = 0
		};

		// Set initial duck state.
		duck_t ducks[NUM_DUCKS] = {
			{ 
				.value =  1,
				.coord= { .x = 0, .y = 0 },
				.x_direction = east,
				.id = 0,
				.state = flap_up,
			},
			{ .value = 5,
				.coord= { .x = 0, .y = 0 },
				.x_direction = east,
				.id = 0,
				.state = flap_up,
			}
		};

		coord_t cross_hair = { .x = 0, .y =0};
		all_game_data_t game_data;

		game_data.game_conf = config;
		int num_ducks_seen = 0;

		while(!is_game_over(&game_data.game_conf, num_ducks_seen)){

			// poll wii controller.
			// if trigger pressed

			move_ducks(ducks, NUM_DUCKS);
			update_duck_attr(duck_hunt_fd, ducks);
			//update_game_data(&game_data);
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
