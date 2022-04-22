#include <stdint.h>
#include <iostream>
#include "Vppu.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "../../sw/sprites.h"
#include <bitset>


   // CData/*2:0*/ shift__DOT__mem[16];
int main(int argc, const char ** argv, const char ** env) {

  
  Verilated::commandArgs(argc, argv);
  Vppu * dut = new Vppu;
  dut->write = 1;   
  dut->chipselect = 1;

  // Write all of the sprites. Will take NUM_SPRITES clock cycles.
  for(int i = 0; i < NUM_SPRITES; ++i){

    clk->1;
    dut->write_data = kSpriteTableData[i].sprite;
    dut->address = SPRITE_TABLE_MEMORY_OFFSET + SPRITE_TABLE_ENTRY_SIZE * kSpriteTableData[i].id;
    dut->eval();
    // TODO(kristenshaker): verify that this entry in the memory table was set correctly.
    clk->0;

    dut->eval();
  }
  for(int i = 0; i < NUM_SPRITES; ++i){
    clk->1;
    dut->write_data = kColorTableData[i].colors;
    
    dut->address = COLOR_TABLE_MEMORY_OFFSET + COLOR_TABLE_ENTRY_SIZE * kColorTableData[i].id;
    dut->eval();
    // TODO(kristenshaker): verify that this entry in the memory table was set correctly.
    clk->0;
    dut->eval();
  }



}
 
