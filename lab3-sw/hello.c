/*
 * Userspace program that communicates with the vga_ball device driver
 * through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 */

#include <stdio.h>
#include "duck_hunt.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int duck_hunt_fd;

/* Read and print the background color */
/*void print_background_color() {
  vga_ball_arg_t vla;
  
  if (ioctl(vga_ball_fd, VGA_BALL_READ_BACKGROUND, &vla)) {
      perror("ioctl(VGA_BALL_READ_BACKGROUND) failed");
      return;
  }
  printf("%02x %02x %02x\n",
	 vla.background.red, vla.background.green, vla.background.blue);
}*/

/* Set the background color */
void set_background_color(const all_game_data_t *c)
{
  all_game_data_t game;
  if (ioctl(duck_hunt_fd, DUCK_HUNT_WRITE_GAME_DATA, &game)) {
      perror("ioctl(DUCK_HUNT_WRITE_GAME_DATA) failed");
      return;
  }
}

int main()
{
  all_game_data_t game;
  int i;
  static const char filename[] = "/dev/duck_hunt";

  printf("Duck Hunt userspace program started\n");

  if ( (duck_hunt_fd = open(filename, O_RDWR)) == -1) {
    fprintf(stderr, "could not open %s\n", filename);
    return -1;
  }

  printf("initial state: ");
  //print_background_color();

/*
  for (i = 0 ; i < 24 ; i++) {
    set_background_color(&colors[i % COLORS ]);
    print_background_color();
    usleep(400000);
  }*/
  
  printf("VGA BALL Userspace program terminating\n");
  return 0;
}
