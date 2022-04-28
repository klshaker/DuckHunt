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
#include <stdint.h>

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

	sprite_table_entry_t sprite = {
		.id  = 0x0,
		.line = {
			0x55555555, 0x55555555, 0x55555555, 0x55555555,
			0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
			0x55555555, 0x55555555, 0x55555555, 0x55555555,
		},
	 };

	//Color Table Entry:
	color_table_entry_t color_palette = {
		.id = 0x0,
		.color = {
			[0] = {.r = 0,    .g = 0,   .b = 0  },
			[1] = {.r = 0,    .g = 100, .b = 100},
			[2] = {.r = 100,  .g = 100, .b = 0  },
			[3] = {.r = 100,  .g = 0,   .b = 100},
		},
	};

    insert_sprite_att(&attr);
    insert_sprite(&sprite);
    insert_color(&color_palette);

    for (int i = 0; i < 250; i ++)
    {
        sprite.id++;
        insert_sprite(&sprite);
    }
    for (int i = 0; i < 16; i++)
    {
        color_palette.id++;
        insert_color(&color_palette);
    }

//    for (int a = 0; a < 15; a ++) {
//
//        for (int i = 0; i < 1280; i += 10) {
//            for (int j = 0; j < 480; j += 10) {
//                attr.coord.x = i;
//                attr.coord.y = j;
//                attr.id      = a;
//                insert_sprite_att(&attr);
//            }
//        }
//    }




	printf("Userspace program terminating\n");
	return 0;
}
