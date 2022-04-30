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
#include <stdlib.h>


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


void write_to_address(int *addr)
{
    if (ioctl(driver_fd, WRITE_TO_ADDRESS, addr)){
        perror("Failed to write to address - sad");
        return;
    }
}

int main(int argc, char **argv)
{
	static const char filename[] = "/dev/ppu";

	printf("Duck Hunt userspace program started\n");

	if ( (driver_fd = open(filename, O_RDWR)) == -1) {
		fprintf(stderr, "could not open %s\n", filename);
		return -1;
	}

    if (argc == 2) {
        int a = atoi(argv[1]);
        printf("Writing to address: %x\n", a);
        write_to_address(&a);
        return 0;
        
    }

	sprite_table_entry_t sprite = {
		.id  = 0x0,
		.line = {
			0xAAAAAAAA, 0x55555555, 0x55555555, 0x55555555,
			0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
			0x55555555, 0x55555555, 0x55555555, 0x55555555,
		},
	};

	//Color Table Entry:
	color_table_entry_t color_palette = {
		.id = 0x0,
		.color = {
			[0] = {.r = 0,    .g = 255,   .b = 0  },
			[1] = {.r = 255,    .g = 0, .b = 0},
			[2] = {.r = 0,  .g = 255, .b = 0  },
			[3] = {.r = 0,  .g = 0,   .b = 255},
		},
	};

	// Clear out the attribute table.
	for(int i = 0; i < 16; ++i){
		attr_table_entry_t zeros = {
			.coord = {
				.x = 0,
				.y = 0
			},
			.sprite         = 0x0,
			.color_table    = 0x0,
			.id             = i
		};
		insert_sprite_att(&zeros);
	}
	
	attr_table_entry_t attr = {
		.coord = {
			.x = 10,
			.y = 10
		},
		.sprite         = 0x0,
		.color_table    = 0x0,
		.id             = 0x0
	};

	insert_sprite_att(&attr);

	for (int i = 0; i < 16; i ++)
	{
		insert_sprite(&sprite);
		sprite.id++;
	}
	for (int i = 0; i < 4; i++)
	{
		insert_color(&color_palette);
		color_palette.id++;
	}



    attr.id = 1;
    for(int x = 0 ; x < 640; ++x){
        for (int i = 0; i < 16; i++) {
            attr.id = i;
            attr.coord.y = i * 20;
            attr.coord.x = x;
            //printf("X: %d\r", x);
            insert_sprite_att(&attr);
            usleep(1000);

        }

    }

	printf("Userspace program terminating\n");
	return 0;
}
