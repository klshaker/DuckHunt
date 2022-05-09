#include <stdio.h>
#include "ppu.h"
#include "sprites.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wiiuse.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAX_WIIMOTES 2

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

/**
 *	@brief Callback that handles an event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *
 *	This function is called automatically by the wiiuse library when an
 *	event occurs on the specified wiimote.
 */
void handle_event(struct wiimote_t* wm) {
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	/* if a button is pressed, report it */
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
		printf("A pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		printf("B pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		printf("UP pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN))	{
		printf("DOWN pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
		printf("LEFT pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
		printf("RIGHT pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
		printf("MINUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
		printf("PLUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		printf("ONE pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		printf("TWO pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
		printf("HOME pressed\n");
	}

	/*
	 *	Pressing minus will tell the wiimote we are no longer interested in movement.
	 *	This is useful because it saves battery power.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) {
		wiiuse_motion_sensing(wm, 0);
	}

	/*
	 *	Pressing plus will tell the wiimote we are interested in movement.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) {
		wiiuse_motion_sensing(wm, 1);
	}

	/*
	 *	Pressing B will toggle the rumble
	 *
	 *	if B is pressed but is not held, toggle the rumble
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		wiiuse_toggle_rumble(wm);
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		wiiuse_set_ir(wm, 1);
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
		wiiuse_set_ir(wm, 0);
	}

	/*
	 * Motion+ support
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		if (WIIUSE_USING_EXP(wm)) {
			wiiuse_set_motion_plus(wm, 2);    // nunchuck pass-through
		} else {
			wiiuse_set_motion_plus(wm, 1);    // standalone
		}
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		wiiuse_set_motion_plus(wm, 0); // off
	}

	/* if the accelerometer is turned on then print angles */
	if (WIIUSE_USING_ACC(wm)) {
		printf("wiimote roll  = %f [%f]\n", wm->orient.roll, wm->orient.a_roll);
		printf("wiimote pitch = %f [%f]\n", wm->orient.pitch, wm->orient.a_pitch);
		printf("wiimote yaw   = %f\n", wm->orient.yaw);
	}

	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) {
		int i = 0;

		/* go through each of the 4 possible IR sources */
		for (; i < 4; ++i) {
			/* check if the source is visible */
			if (wm->ir.dot[i].visible) {
				// printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
			}
		}
		int scaled_x = wm->ir.x * 1.1;
		int scaled_y = wm->ir.y * 1.1;
		if (scaled_x <= 640 && scaled_x >= 0
				&& scaled_y <= 480 && scaled_y >= 0) {
			attr_table_entry_t attr = {
				.coord = {
					.x = scaled_x,
					.y = scaled_y
				},
				.sprite         = 0x0,
				.color_table    = 0x0,
				.id             = 0x0
			};

			insert_sprite_att(&attr);
		}

		printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
		// printf("IR z distance: %f\n", wm->ir.z);
	}

	/* show events specific to supported expansions */
	if (wm->exp.type == EXP_NUNCHUK || wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
		/* nunchuk */
		struct nunchuk_t* nc = (nunchuk_t*)&wm->exp.nunchuk;

		if (IS_PRESSED(nc, NUNCHUK_BUTTON_C)) {
			printf("Nunchuk: C pressed\n");
		}
		if (IS_PRESSED(nc, NUNCHUK_BUTTON_Z)) {
			printf("Nunchuk: Z pressed\n");
		}

		printf("nunchuk roll  = %f\n", nc->orient.roll);
		printf("nunchuk pitch = %f\n", nc->orient.pitch);
		printf("nunchuk yaw   = %f\n", nc->orient.yaw);

		printf("nunchuk joystick angle:     %f\n", nc->js.ang);
		printf("nunchuk joystick magnitude: %f\n", nc->js.mag);

		printf("nunchuk joystick vals:      %f, %f\n", nc->js.x, nc->js.y);
		printf("nunchuk joystick calibration (min, center, max): x: %i, %i, %i  y: %i, %i, %i\n",
				nc->js.min.x,
				nc->js.center.x,
				nc->js.max.x,
				nc->js.min.y,
				nc->js.center.y,
				nc->js.max.y);
	} else if (wm->exp.type == EXP_CLASSIC) {
		/* classic controller */
		struct classic_ctrl_t* cc = (classic_ctrl_t*)&wm->exp.classic;

		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZL)) {
			printf("Classic: ZL pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_B)) {
			printf("Classic: B pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_Y)) {
			printf("Classic: Y pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_A)) {
			printf("Classic: A pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_X)) {
			printf("Classic: X pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZR)) {
			printf("Classic: ZR pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_LEFT)) {
			printf("Classic: LEFT pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_UP)) {
			printf("Classic: UP pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_RIGHT)) {
			printf("Classic: RIGHT pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_DOWN)) {
			printf("Classic: DOWN pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_L)) {
			printf("Classic: FULL L pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_MINUS)) {
			printf("Classic: MINUS pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_HOME)) {
			printf("Classic: HOME pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_PLUS)) {
			printf("Classic: PLUS pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_R)) {
			printf("Classic: FULL R pressed\n");
		}

		printf("classic L button pressed:         %f\n", cc->l_shoulder);
		printf("classic R button pressed:         %f\n", cc->r_shoulder);
		printf("classic left joystick angle:      %f\n", cc->ljs.ang);
		printf("classic left joystick magnitude:  %f\n", cc->ljs.mag);
		printf("classic right joystick angle:     %f\n", cc->rjs.ang);
		printf("classic right joystick magnitude: %f\n", cc->rjs.mag);
	} else if (wm->exp.type == EXP_GUITAR_HERO_3) {
		/* guitar hero 3 guitar */
		struct guitar_hero_3_t* gh3 = (guitar_hero_3_t*)&wm->exp.gh3;

		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_UP)) {
			printf("Guitar: Strum Up pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_DOWN))	{
			printf("Guitar: Strum Down pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_YELLOW)) {
			printf("Guitar: Yellow pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_GREEN)) {
			printf("Guitar: Green pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_BLUE)) {
			printf("Guitar: Blue pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_RED)) {
			printf("Guitar: Red pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_ORANGE)) {
			printf("Guitar: Orange pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_PLUS)) {
			printf("Guitar: Plus pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_MINUS)) {
			printf("Guitar: Minus pressed\n");
		}

		printf("Guitar whammy bar:          %f\n", gh3->whammy_bar);
		printf("Guitar joystick angle:      %f\n", gh3->js.ang);
		printf("Guitar joystick magnitude:  %f\n", gh3->js.mag);
	} else if (wm->exp.type == EXP_WII_BOARD) {
		/* wii balance board */
		struct wii_board_t* wb = (wii_board_t*)&wm->exp.wb;
		float total = wb->tl + wb->tr + wb->bl + wb->br;
		float x = ((wb->tr + wb->br) / total) * 2 - 1;
		float y = ((wb->tl + wb->tr) / total) * 2 - 1;
		printf("Weight: %f kg @ (%f, %f)\n", total, x, y);
		printf("Interpolated weight: TL:%f  TR:%f  BL:%f  BR:%f\n", wb->tl, wb->tr, wb->bl, wb->br);
		printf("Raw: TL:%d  TR:%d  BL:%d  BR:%d\n", wb->rtl, wb->rtr, wb->rbl, wb->rbr); 
	}

	if (wm->exp.type == EXP_MOTION_PLUS ||
			wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
		printf("Motion+ angular rates (deg/sec): pitch:%03.2f roll:%03.2f yaw:%03.2f\n",
				wm->exp.mp.angle_rate_gyro.pitch,
				wm->exp.mp.angle_rate_gyro.roll,
				wm->exp.mp.angle_rate_gyro.yaw);
	}
}


/**
 *	@brief Callback that handles a read event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *	@param data		Pointer to the filled data block.
 *	@param len		Length in bytes of the data block.
 *
 *	This function is called automatically by the wiiuse library when
 *	the wiimote has returned the full data requested by a previous
 *	call to wiiuse_read_data().
 *
 *	You can read data on the wiimote, such as Mii data, if
 *	you know the offset address and the length.
 *
 *	The \a data pointer was specified on the call to wiiuse_read_data().
 *	At the time of this function being called, it is not safe to deallocate
 *	this buffer.
 */
void handle_read(struct wiimote_t* wm, byte* data, unsigned short len) {
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%x ", data[i]);
	}
	printf("\n\n");
}


/**
 *	@brief Callback that handles a controller status event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *	@param attachment		Is there an attachment? (1 for yes, 0 for no)
 *	@param speaker			Is the speaker enabled? (1 for yes, 0 for no)
 *	@param ir				Is the IR support enabled? (1 for yes, 0 for no)
 *	@param led				What LEDs are lit.
 *	@param battery_level	Battery level, between 0.0 (0%) and 1.0 (100%).
 *
 *	This occurs when either the controller status changed
 *	or the controller status was requested explicitly by
 *	wiiuse_status().
 *
 *	One reason the status can change is if the nunchuk was
 *	inserted or removed from the expansion port.
 */
void handle_ctrl_status(struct wiimote_t* wm) {
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}


/**
 *	@brief Callback that handles a disconnection event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *
 *	This can happen if the POWER button is pressed, or
 *	if the connection is interrupted.
 */
void handle_disconnect(wiimote* wm) {
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}


void test(struct wiimote_t* wm, byte* data, unsigned short len) {
	printf("test: %i [%x %x %x %x]\n", len, data[0], data[1], data[2], data[3]);
}

short any_wiimote_connected(wiimote** wm, int wiimotes) {
	int i;
	if (!wm) {
		return 0;
	}

	for (i = 0; i < wiimotes; i++) {
		if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
			return 1;
		}
	}

	return 0;
}

int main()
{
	int i;

	static const char filename[] = "/dev/ppu";

	printf("Duck Hunt userspace program started\n");

	if ( (driver_fd = open(filename, O_RDWR)) == -1) {
		fprintf(stderr, "could not open %s\n", filename);
		return -1;
	}

	sprite_table_entry_t sprite = {
		.id  = 0,
		.line = {
0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x54000000, 
 	0x55540000, 
 	0x55555000, 
 	0x55555551, 
 	0x55555554, 
 	0x55555560, 
 	0x55555580, 
 	0x55555600, 
 	0x55596a00, 
 	0x555aa800, 
 	0x556aa000,
		},
};

sprite_table_entry_t sprite_2 = {		
.id  = 1,
.line = {
0x556b0000, 
 	0x554ffc00, 
 	0x5583fc00, 
 	0x5580fc00, 
 	0x56003000, 
 	0x66000000, 
 	0x68000000, 
 	0x80000000, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0,
	},
};	

	sprite_table_entry_t sprite_3 = {		
	.id  = 2,
	.line = {
0x0, 
 	0xef0000, 
 	0x3abc000, 
 	0x36bf000, 
 	0xf6bfc00, 
 	0xffabfe40, 
 	0xffeffe55, 
 	0xfffffe55, 
 	0xfffa55, 
 	0x3955, 
 	0x155, 
 	0x15, 
 	0x9, 
 	0x1, 
 	0x1, 
 	0x1,
	},
};

	sprite_table_entry_t sprite_4 = {		
	.id  = 3,
	.line = {
0x5, 
 	0x5, 
 	0x5, 
 	0x5, 
 	0x15, 
 	0x15, 
 	0x16, 
 	0x56, 
 	0x58, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0,
	},
};

sprite_table_entry_t sprite_5 = {		
	.id  = 4,
	.line = {
0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x3, 
 	0xf, 
 	0xf, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0,
	},
};

sprite_table_entry_t sprite_6 =
{		
	.id  = 5,
	.line = {
0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0, 
 	0x0,
	},
};


	//Color Table Entry:

	color_table_entry_t color_palette = {		
		.id = 0,
		.color = {
			[0] = {.r = 0, .g = 0, .b = 0},
			[1] = {.r = 0, .g = 0, .b = 168 },
			[2] = {.r = 252, .g = 252, .b = 252 },
			[3] = {.r = 188, .g = 0, .b = 188 },
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

	// insert_sprite_att(&attr);
	
	insert_sprite(&sprite);	
	insert_sprite(&sprite_2);	
	insert_sprite(&sprite_3);	
	insert_sprite(&sprite_4);	
	insert_sprite(&sprite_5);	
	insert_sprite(&sprite_6);	

	// for (int i = 0; i < 16; i ++)
	// {
	// 	insert_sprite(&sprite);
	// 	sprite.id++;
	// }
	for (int i = 0; i < 4; i++)
	{
		insert_color(&color_palette);
		color_palette.id++;
	}



	attr.id = 1;
	for(int x = 0 ; x < 640; ++x){
		for (int i = 0; i < 6; i++) {
			attr.id = i;
			attr.coord.y = 100 + (16 * (i % 2));
			attr.coord.x = x + (16 * (i / 2));
			attr.sprite = i;
			//printf("X: %d\r", x);
			insert_sprite_att(&attr);
			usleep(1000);

		}

	}


	// Wii stuff
	wiimote** wiimotes;
	wiimotes = wiiuse_init(2);
	int found, connected;

	found = wiiuse_find(wiimotes, 2, 5);
	if (!found) {
		printf("Nothing found!!!");
		return 0;
	}

	connected = wiiuse_connect(wiimotes, 2);
	if (connected) {
		printf("Connected to %i wiimotes\n", connected);
	} else {
		return 0;
	}
	wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);

	wiiuse_rumble(wiimotes[0], 0);
	wiiuse_rumble(wiimotes[1], 0);

	printf("\nControls:\n");
	printf("\tB toggles rumble.\n");
	printf("\t+ to start Wiimote accelerometer reporting, - to stop\n");
	printf("\tUP to start IR camera (sensor bar mode), DOWN to stop.\n");
	printf("\t1 to start Motion+ reporting, 2 to stop.\n");
	printf("\n\n");

	/*
	 *	Maybe I'm interested in the battery power of the 0th
	 *	wiimote.  This should be WIIMOTE_ID_1 but to be sure
	 *	you can get the wiimote associated with WIIMOTE_ID_1
	 *	using the wiiuse_get_by_id() function.
	 *
	 *	A status request will return other things too, like
	 *	if any expansions are plugged into the wiimote or
	 *	what LEDs are lit.
	 */
	/* wiiuse_status(wiimotes[0]); */

	/*
	 *	This is the main loop
	 *
	 *	wiiuse_poll() needs to be called with the wiimote array
	 *	and the number of wiimote structures in that array
	 *	(it doesn't matter if some of those wiimotes are not used
	 *	or are not connected).
	 *
	 *	This function will set the event flag for each wiimote
	 *	when the wiimote has things to report.
	 */
	while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
		if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
			/*
			 *	This happens if something happened on any wiimote.
			 *	So go through each one and check if anything happened.
			 */
			int i = 0;
			for (; i < MAX_WIIMOTES; ++i) {
				switch (wiimotes[i]->event) {
					case WIIUSE_EVENT:
						/* a generic event occurred */
						handle_event(wiimotes[i]);
						break;

					case WIIUSE_STATUS:
						/* a status event occurred */
						handle_ctrl_status(wiimotes[i]);
						break;

					case WIIUSE_DISCONNECT:
					case WIIUSE_UNEXPECTED_DISCONNECT:
						/* the wiimote disconnected */
						handle_disconnect(wiimotes[i]);
						break;

					case WIIUSE_READ_DATA:
						/*
						 *	Data we requested to read was returned.
						 *	Take a look at wiimotes[i]->read_req
						 *	for the data.
						 */
						break;

					case WIIUSE_NUNCHUK_INSERTED:
						/*
						 *	a nunchuk was inserted
						 *	This is a good place to set any nunchuk specific
						 *	threshold values.  By default they are the same
						 *	as the wiimote.
						 */
						/* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
						/* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
						printf("Nunchuk inserted.\n");
						break;

					case WIIUSE_CLASSIC_CTRL_INSERTED:
						printf("Classic controller inserted.\n");
						break;

					case WIIUSE_WII_BOARD_CTRL_INSERTED:
						printf("Balance board controller inserted.\n");
						break;

					case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
						/* some expansion was inserted */
						handle_ctrl_status(wiimotes[i]);
						printf("Guitar Hero 3 controller inserted.\n");
						break;

					case WIIUSE_MOTION_PLUS_ACTIVATED:
						printf("Motion+ was activated\n");
						break;

					case WIIUSE_NUNCHUK_REMOVED:
					case WIIUSE_CLASSIC_CTRL_REMOVED:
					case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
					case WIIUSE_WII_BOARD_CTRL_REMOVED:
					case WIIUSE_MOTION_PLUS_REMOVED:
						/* some expansion was removed */
						handle_ctrl_status(wiimotes[i]);
						printf("An expansion was removed.\n");
						break;

					default:
						break;
				}
			}
		}
	}

	/*
	 *	Disconnect the wiimotes
	 */
	wiiuse_cleanup(wiimotes, MAX_WIIMOTES);

	printf("VGA BALL Userspace program terminating\n");
	return 0;
}
