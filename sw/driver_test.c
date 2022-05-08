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


void write_to_address(struct wta *addr)
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

	struct wta av= {0, 0};

	if (argc == 3) {
		av.addr = atoi(argv[1]);
		av.value = atoi(argv[2]);
		printf("Writing %x to address: %x\n", av.value, av.addr);
		write_to_address(&av);
		return 0;

	}

	//zero sprites
	//for (int i = 0; i < 15; i++)
	//{
	//    sprite_table_entry_t zero = {
	//        .id = i,
	//        .line = {
	//            0, 0, 0, 0, 
	//            0, 0, 0, 0, 
	//            0, 0, 0, 0,
	//            0, 0, 0, 0 
	//            },
	//    };
	//    insert_sprite(&zero);
	//}

	sprite_table_entry_t sprite = {
		.id  = 0x0,
		.line = {
			0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
			0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
			0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
			0x55555555, 0x55555555, 0x55555555, 0x55555555,
		},
	};

	sprite_table_entry_t sprite1 = {
		.id  = 0x1,
		.line = {
			0x55555555, 0x55555555, 0x55555555, 0x55555555,
			0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0,
			0xF00FF00F, 0xF00FF00F, 0xF00FF00F, 0xF00FF00F,
			0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
		},
	};
	//Color Table En:
	color_table_entry_t color_palette = {
		.id = 0x0,
		.color = {
			[0] = {.r = 0,    .g = 0,   .b = 0  },
			[1] = {.r = 0,  .g = 101, .b = 0  },
			[2] = {.r = 0,  .g = 255, .b = 0  },
			[3] = {.r = 0,  .g = 0,   .b = 255},
		},
	};

	color_table_entry_t color_palette2= {
		.id = 0x1,
		.color = {
			[0] = {.r = 0,    .g = 0,   .b = 0  },
			[1] = {.r = 255,  .g = 101, .b = 0  },
			[2] = {.r = 10,  .g = 255, .b = 78  },
			[3] = {.r = 255,  .g = 0,   .b = 255},
		},
	};


	attr_table_entry_t attr = {
		.coord = {
			.x = 10,
			.y = 10
		},
		.sprite         = 0x1,
		.color_table    = 0x1,
		.id             = 0x1
	};

	//    int x;
	//    printf("Enter attr.i: ");
	//    scanf("%d", &x);  
	//    attr.id = x;
	//
	//    printf("Enter attr.x: ");
	//    scanf("%d", &x);  
	//    attr.coord.x = x;
	//
	//    printf("Enter attr.y: ");
	//    scanf("%d", &x);  
	//    attr.coord.y = x;
	//
	//    printf("Enter attr.c: ");
	//    scanf("%d", &x);  
	//    attr.color_table = x;
	//
	//    printf("Enter attr.s: ");
	//    scanf("%d", &x);  
	//    attr.sprite = x;
	//
	//	insert_sprite_att(&attr);
	//
	//    printf("\nEnter colortable.id: ");
	//    scanf("%d", &x);  
	//    color_palette.id = x;


	//    printf("\nEnter sprite.id: ");
	//    scanf("%d", &x);  
	//    sprite.id = x;

	int x;
	insert_sprite_att(&attr);
	insert_color(&color_palette);
	insert_color(&color_palette2);
	insert_sprite(&sprite);
	insert_sprite(&sprite1);
	//scanf("%d", &x);  

	for(int x = 0 ; x < 630; ++x){
		for (int i = 0; i < 64; i++) {
			attr.id = i;
			attr.color_table = (i % 2);
			attr.sprite = (i % 2);
			attr.coord.y = (i * 15) % 480 + i * 2;
			attr.coord.x = (i + (15 * (i % 2 )));
			printf("X: %d\r", x);
			insert_sprite_att(&attr);
			usleep(1000);

		}

	}

	printf("Userspace program terminating\n");
	return 0;
}
