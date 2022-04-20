#include "sprites.h"
#include <assert.h>
#include <stdio.h>

void test_build_sprite_table(){
	sprite_data_t sprites[NUM_SPRITES];
	int num_sprites = 0;
	int success = build_sprite_table(sprites, &num_sprites);
	assert(success == 1);
	assert(num_sprites == 2);
	int i = 0;
	for(; i < num_sprites; ++i){
		assert(sprites[i].addr ==  SPRITE_SIZE * i);
		int j =0;
		for(; j < SPRITE_SIZE; ++j){
		assert(sprites[i].sprite[j] == 0xAAAAAAAA);
		}
	}

}

void test_build_attr_table(){
	// value initialize everything (should zero it all out).
	attr_table_entry_t entries[NUM_SPRITES] = {};
	int num_entries = 0;

	int success = build_sprite_attr_table(entries, &num_entries);
	assert(success == 1);

	// right now we should have 9 sprites.
	assert(num_entries == 9);
	/* Sprite attr table should contain the following entries
	   Duck 1
	   Duck 2
	   Bullet 1
	   Bullet 2
	   Bullet 3
	   Score 1
	   Score 2
	   Round 
	   Crosshair 
	 */

	// test that addresses are incremental. Currently we have 9 entries. Each should come after the other in the attr table. 

	int i=0;
	for(; i < num_entries; ++i){
		assert(entries[i].addr ==  i);
	}

	assert(entries[0].sprite == DUCK_SPRITE_OFFSET);
	assert(entries[1].sprite == DUCK_SPRITE_OFFSET);
	assert(entries[2].sprite == BULLET_SPRITE_OFFSET);
	assert(entries[3].sprite == BULLET_SPRITE_OFFSET);
	assert(entries[4].sprite == BULLET_SPRITE_OFFSET);
	assert(entries[5].sprite == NUMBER_SPRITE_OFFSET);
	assert(entries[6].sprite == NUMBER_SPRITE_OFFSET);
	assert(entries[7].sprite == NUMBER_SPRITE_OFFSET);
	assert(entries[8].sprite == CROSSHAIR_SPRITE_OFFSET);
}



int main(){
	test_build_attr_table();
	test_build_sprite_table();
}
