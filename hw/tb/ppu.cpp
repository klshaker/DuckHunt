#include <stdint.h>
#include <iostream>
#include "Vppu.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "../../sw/sprites.h"
#include <bitset>

#define OBJ_SPRITE_OFFSET 20
#define OBJ_X_COORD_OFFSET 10
#define OBJ_Y_COORD_OFFSET 0
#define OBJ_COLOR_OFFSET 28

#define ATTR_TABLE_MEMORY_OFFSET 0x000
#define SPRITE_TABLE_MEMORY_OFFSET 0x100 
#define COLOR_TABLE_MEMORY_OFFSET 0x200 

int32_t attr_to_int(attr_table_entry_t *attr)
{	
	int32_t data = 0;// 0xFFFFFFFF;
	std::cout << "data:  " 	<< std::bitset<32>(data) 			<< std::endl;

	data = data | (attr->coord.x 		<< OBJ_X_COORD_OFFSET);
	std::cout << "x:     "		<< std::bitset<32>(attr->coord.x) 	<< std::endl;
	std::cout << "data:  " 	<< std::bitset<32>(data) 			<< std::endl;

	data = data | (attr->coord.y 		<< OBJ_Y_COORD_OFFSET);
	std::cout << "y:     " 		<< std::bitset<32>(attr->coord.y) 	<< std::endl;
	std::cout << "data:  " 	<< std::bitset<32>(data) 			<< std::endl;

	data = data | (attr->sprite  		<< OBJ_SPRITE_OFFSET );
	std::cout << "sprite:" << std::bitset<32>(attr->sprite)  	<< std::endl;
	std::cout << "data:  " 	<< std::bitset<32>(data) 			<< std::endl;
	
	data = data | (attr->color_table   << OBJ_COLOR_OFFSET	 );
	std::cout << "color: " 	<< std::bitset<32>(attr->color_table) << std::endl;
	std::cout << "data:  " 	<< std::bitset<32>(data) 			  << std::endl;

	return data;

}

// CData/*2:0*/ shift__DOT__mem[16];
int main(int argc, const char ** argv, const char ** env) {

	Verilated::commandArgs(argc, argv);

	Vppu * dut = new Vppu;
	Verilated::traceEverOn(true);
	VerilatedVcdC * tfp = new VerilatedVcdC;
	dut->trace(tfp, 99);
	tfp->open("ppu.vcd");

	//PPU Inputs:
	dut->clk 		= 0;
	dut->reset 		= 0;
	dut->writedata 	= 0;
	dut->write		= 0;
	dut->chipselect = 0;
	dut->address	= 0;

	//To write:
	dut->write 		= 1; 
	dut->chipselect = 1;


	//Attr Table Entry
    attr_table_entry_t attr = {
		.coord = {
			.x = 250,
			.y = 100
		},
		.sprite         = 0x0,
		.color_table    = 0x0,
		.id             = 0x0,
	};

	//Sprite Table Entry
    sprite_table_entry_t sprite;
    sprite.id       = 0x0;
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

	//Color Table Entry:
    color_table_entry_t color_palette = {
        .id = 0,
        .color0 = {.r = 0,    .g = 0,   .b = 0  },
        .color1 = {.r = 0,    .g = 100, .b = 100},
        .color2 = {.r = 100,  .g = 100, .b = 0  },
        .color3 = {.r = 100,  .g = 0,   .b = 100},
    };

	int time = 0;
	int clock = 0;

	// Write all of the sprites. Will take NUM_SPRITES clock cycles.
	for(int i = 0; i < 16; ++i){
		attr.coord.x = attr.coord.x + i;

		//CLOCK HIGH
		dut->clk = 1;
		clock++;
		time += 10;
		
		std::cout << attr_to_int(&attr) << std::endl;
		dut->writedata = attr_to_int(&attr);
		dut->address = ATTR_TABLE_MEMORY_OFFSET + i;

		dut->eval();
		tfp->dump( time );

		
		//CLOCK LOW
		dut->clk = 0;
		time += 10;

		dut->eval();
		tfp->dump( time );
		
		// TODO(kristenshaker): verify that this entry in the memory table was set correctly.
	}

	dut->chipselect = 0;
	dut->write = 0;
	while (clock < 512000) {
		//CLOCK HIGH
		dut->clk = 1;
		clock++;
		time += 10;
		dut->eval();
		tfp->dump( time );

		
		//CLOCK LOW
		dut->clk = 0;
		time += 10;

		dut->eval();
		tfp->dump( time );
	}



//
//	for(int i = 0; i < 16; ++i){
//		dut->clk = 1;
//		dut->write_data = kColorTableData[i].colors;
//
//		dut->address = COLOR_TABLE_MEMORY_OFFSET + COLOR_TABLE_ENTRY_SIZE * kColorTableData[i].id;
//		dut->eval();
//		// TODO(kristenshaker): verify that this entry in the memory table was set correctly.
//		dut->clk=0;
//		dut->eval();
//	}
//

	tfp->close();
	delete tfp;

	dut->final();
	delete dut;
	return 0;

}

