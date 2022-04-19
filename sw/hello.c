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

/* Read and print the game state */
/*void print_background_color() {
  all_game_data_t game_data;

  if (ioctl(vga_ball_fd, VGA_BALL_READ_BACKGROUND, &game_data)) {
  perror("ioctl(VGA_BALL_READ_BACKGROUND) failed");
  return;
  }
  printf("%02x %02x %02x\n",
  vla.background.red, vla.background.green, vla.background.blue);
  }*/

/* Set the background color */
/*void update_game_data(const all_game_data_t *g)
{
	all_game_data_t game = *g;
	// does this write to the file and copy_from user accesses that same file?
	if (ioctl(duck_hunt_fd, DUCK_HUNT_WRITE_GAME_DATA, &game)) {
		perror("ioctl(DUCK_HUNT_WRITE_GAME_DATA) failed");
		return;
	}
}*/

void play_game(){

	while(1){
		game_config_t config;
		config.bullets = 3;
		config.score = 0;
		config.round = 0;

		duck_t ducks[2];
		ducks[0].coord.x = 0;
		ducks[0].coord.y = 200;
		ducks[0].value = 5;

		ducks[0].coord.x = 0;
		ducks[0].coord.y = 400;
		ducks[0].value = 10;
		coord_t cross_hair = { 0, 0};
		all_game_data_t game_data;

		game_data.game_conf = config;
		int num_ducks_seen =0;

		while(!is_game_over(&game_data.game_conf, num_ducks_seen)){

			// poll wii controller.
			// if trigger pressed

			move_ducks(ducks, 2);
			update_duck_attr(duck_hunt_fd, ducks, 2);
			
			// call kernel driver APIs.
			//update_game_data(&game_data);
		}

	}
}

int main()
{
	static const char filename[] = "/dev/duck_hunt";

	printf("Duck Hunt userspace program started\n");

	if ( (duck_hunt_fd = open(filename, O_RDWR)) == -1) {
		fprintf(stderr, "could not open %s\n", filename);
		return -1;
	}
	write_sprite_attr_table(duck_hunt_fd);
	write_sprite_table(duck_hunt_fd);


	printf("initial state: ");
	play_game();

	printf("VGA BALL Userspace program terminating\n");
	return 0;
}
