/*
 * Userspace program that communicates with the vga_ball device driver
 * through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 */

#include <stdio.h>
#include "ppu.h"
#include "sprites.h"
//#include "game/game.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int driver_fd;

void insert_sprite_att(attr_table_entry_t *att)
{
    if (ioctl(driver_fd, ATTR_TABLE_WRITE_DATA, att)) {
        perror("Failed to write attr");
        return;
    }

}

void insert_sprite(sprite_table_entry_t *sprite)
{
    if (ioctl(driver_fd, SPRITE_TABLE_WRITE_DATA, sprite)) {
        perror("Failed to write sprite");
        return;
    }

}

void insert_color(color_table_entry_t *color_palette)
{
    if (ioctl(driver_fd, COLOR_TABLE_WRITE_DATA, color_palette)) {
        perror("Failed to write color_palette");
        return;
    }

}


int main()
{
	static const char filename[] = "/dev/ppu";

	printf("Duck Hunt userspace program started\n");

	if ( (driver_fd = open(filename, O_RDWR)) == -1) {
		fprintf(stderr, "could not open %s\n", filename);
		return -1;
	}

    attr_table_entry_t attr = {
        .coord = {
            .x = 250,
            .y = 400
        },
        .sprite         = 0x0,
        .color_table    = 0x0,
        .id             = 0x0
    };

    color_table_entry_t color_palette = {
        .color0 = {.r = 0,    .g = 0,   .b = 0  },
        .color1 = {.r = 0,    .g = 100, .b = 100},
        .color2 = {.r = 100,  .g = 100, .b = 0  },
        .color3 = {.r = 100,  .g = 0,   .b = 100}
    };

    sprite_table_entry_t sprite;
    sprite.line[0]  = 0x55555555;
    sprite.line[1]  = 0x55555555;
    sprite.line[2]  = 0x55555555;
    sprite.line[3]  = 0x55555555;
    sprite.line[4]  = 0xAAAAAAAA;
    sprite.line[5]  = 0xAAAAAAAA;
    sprite.line[6]  = 0xAAAAAAAA;
    sprite.line[7]  = 0xAAAAAAAA;
    sprite.line[8]  = 0xFFFFFFFF;
    sprite.line[9]  = 0xFFFFFFFF;
    sprite.line[10] = 0xFFFFFFFF;
    sprite.line[11] = 0xFFFFFFFF;
    sprite.line[12] = 0x55555555;
    sprite.line[13] = 0x55555555;
    sprite.line[14] = 0x55555555;
    sprite.line[15] = 0x55555555;

    insert_sprite_att(&attr);
    insert_sprite(&sprite);
    insert_color(&color_palette);




	printf("Userspace program terminating\n");
	return 0;
}
