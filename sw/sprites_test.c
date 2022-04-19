#include "sprites.h"
#include <assert.h>
#include <stdio.h>


void test_build_attr_table(){
attr_table_entry_t entries[NUM_SPRITES];
int num_entries;

int success = build_sprite_attr_table(entries, &num_entries);
assert(success == 1);
int i=0;

printf("%d:", num_entries);

// right now we should have 9 sprites.
assert(num_entries == 9);
// test that addresses are correct.
for(; i < num_entries; ++i){

	assert(entries[i].addr == ATTR_TABLE_OFFSET + i);
}


}

int main(){
test_build_attr_table();
}
