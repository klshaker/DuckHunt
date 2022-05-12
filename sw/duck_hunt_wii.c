#include <stdio.h>
#include "ppu.h"
#include "sprites.h"
#include "game/game.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wiiuse.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAX_WIIMOTES 2
#define SECONDS_BETWEEN_SPAWNS 1

enum game_progress { ROUND_START, IN_PROGRESS, ROUND_OVER };

int duck_hunt_fd;

// GLOBAL WII REMOTES
wiimote** wiimotes;

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

void play_game(){

	while(1) {

		// Set inintial game state.
		game_config_t game_data = {
			.bullets = kBulletsPerRound, 
			.score = 0, 
			.round = 0,
			.spawned_ducks = 0,
			.visible_ducks = 0
		};

		// Set initial duck state. Value initialize array to all member variables are zero initialized. There will only ever be ducksperround ducks on the screen.
		duck_t ducks[NUM_DUCKS_PER_ROUND] = {};
		for(int i = 0; i < NUM_DUCKS_PER_ROUND; ++i){
			ducks[i].id = i;
			ducks[i].state = inactive;
		}
		
		coord_t cross_hair = { .x = 300, .y = 300};

		time_t last_spawned_time = time(0);
		printf("TIME %ld\n", last_spawned_time);

		enum game_progress progress = ROUND_START;

		// START SCREEN
		while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
			// poll wii controller.
			if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
				int i = 0;
				for (; i < MAX_WIIMOTES; ++i) {
					switch (wiimotes[i]->event) {
						case WIIUSE_EVENT:;
							/* a generic event occurred */
							// handle_event(wiimotes[i]);
							struct wiimote_t* wm = wiimotes[i];
							printf("\n\n--- EVENT [id %i] ---\n", wm->unid);
							if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
								printf("UP pressed\n");
								wiiuse_set_ir(wm, 1);
							}
							if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
								printf("A pressed\n");
								goto loop_out;
							}
					}
				}
			}
		}

		loop_out:;
		// GAME LOOP
		int muzzle_flash = 0;
		time_t last_round_time = time(0);
		while(!is_game_over(&game_data) && 
				any_wiimote_connected(wiimotes, MAX_WIIMOTES)){
			usleep(8000);	
			// printf("ROUND STATE: %d\n", progress);

			time_t now = time(0);
			if (progress == ROUND_START && (now - last_round_time > 1)) {
				last_spawned_time = now;
				printf("STARTING NEW ROUND\n");
			   	start_new_round(&game_data);
				update_game_state_attrs(duck_hunt_fd, game_data.bullets, game_data.score, game_data.round);
				progress = IN_PROGRESS;
			}
			// Introduce a duck every 5 seconds if there are fewer than 2 ducks on the screen.
			// if(progress == IN_PROGRESS && now - last_spawned_time > SECONDS_BETWEEN_SPAWNS 
			// 	&& game_data.visible_ducks < NUM_DUCKS_PER_ROUND && game_data.spawned_ducks < NUM_DUCKS_PER_ROUND) {

			// 	//printf("trying to spawn duck\n");
			// 	// spawn the first duck that is currently not visible.
			// 	for(int i = 0; i < NUM_DUCKS_PER_ROUND; ++i){
			// 		if(ducks[i].state == inactive){
			// 			spawn_duck(&ducks[i], &game_data);
			// 			break;
			// 		}
			// 	}

			// }
			if (progress == IN_PROGRESS && game_data.spawned_ducks < NUM_DUCKS_PER_ROUND) {
				game_data.spawned_ducks = NUM_DUCKS_PER_ROUND;
				game_data.visible_ducks = NUM_DUCKS_PER_ROUND;
			 	for(int i = 0; i < NUM_DUCKS_PER_ROUND; ++i){
					spawn_duck(&ducks[i], &game_data);
			 	}

			}

			// Stop muzzle flash after 5 ticks
			if (muzzle_flash > 0) {
				if (muzzle_flash == 1) {
					write_pattern_table(duck_hunt_fd, 5);
					wiiuse_rumble(wiimotes[0], 0);
				}
				muzzle_flash -= 1;
			}
			
			// poll wii controller.
			if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
				/*
				 *	This happens if something happened on any wiimote.
				 *	So go through each one and check if anything happened.
				 */
				int i = 0;
				for (; i < MAX_WIIMOTES; ++i) {
					switch (wiimotes[i]->event) {
						case WIIUSE_EVENT:;
							struct wiimote_t* wm = wiimotes[i];
							// printf("\n\n--- EVENT [id %i] ---\n", wm->unid);
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
									cross_hair.x = scaled_x;
									cross_hair.y = scaled_y;
								}

								// printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
								// printf("IR z distance: %f\n", wm->ir.z);
							}
							
							// If trigger just pressed, check if killed duck
							if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) {
								if (progress == IN_PROGRESS) {
									write_pattern_table(duck_hunt_fd, 6);
									muzzle_flash = 15;
									shoot_at_ducks(ducks, NUM_DUCKS_PER_ROUND, cross_hair, &game_data);
									printf("B pressed\n");
									wiiuse_rumble(wm, 1);
								}
							} 

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

						default:
							break;
					}
				}
			}

			update_crosshair_attr(duck_hunt_fd, cross_hair.x, cross_hair.y); 
			move_ducks(ducks, NUM_DUCKS_PER_ROUND, &game_data);
			for(int i = 0; i < NUM_DUCKS_PER_ROUND; ++i){
				if(ducks[i].state != inactive){
					update_duck_attr(duck_hunt_fd, &ducks[i]);
				}
			}
			if(progress == IN_PROGRESS && is_round_over(&game_data)){
				progress = ROUND_OVER;
				last_round_time = time(0);
			}
			// Wait 2 seconds for ducks to leave, then reset state
			else if (progress == ROUND_OVER && now - last_round_time > 4) {
				printf("ROUND OVER!!~!!!\n");
				for (int i = 0; i < NUM_DUCKS_PER_ROUND; ++i) {
					if (ducks[i].state != inactive) {
						ducks[i].state = flying_away;
					}	
				}
				progress = ROUND_START;
				last_round_time = time(0);
				if (game_data.round == 8) goto game_over;
			}
			
			update_game_state_attrs(duck_hunt_fd, game_data.bullets, game_data.score, game_data.round);
		}
		game_over:
		printf("GAME_OVER");
		// END SCREEN
		while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
			// poll wii controller.
			if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
				int i = 0;
				for (; i < MAX_WIIMOTES; ++i) {
					switch (wiimotes[i]->event) {
						case WIIUSE_EVENT:;
							struct wiimote_t* wm = wiimotes[i];
							if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
								printf("A pressed\n");
								goto end_game;
							}
					}
				}
			}
		}
		end_game:;

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
	write_pattern_table(duck_hunt_fd, 5);

	// Wii stuff
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

	printf("\n To begin motion tracking, press + \n");
	printf("\n\n");

	play_game();

	printf("Duck Hunt Userspace program terminating\n");
	wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
	return 0;
}

