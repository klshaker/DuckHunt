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
	int data = 0x00000000;
	data = data | (attr->coord.x	 << OBJ_X_COORD_OFFSET);
	data = data | (attr->coord.y	 << OBJ_Y_COORD_OFFSET);
	data = data | (attr->sprite	 << OBJ_SPRITE_OFFSET );
	data = data | (attr->color_table << OBJ_COLOR_OFFSET  );
	return data;
}

int32_t color_to_int( color_t *color)
{
	int data = 0x00000000;
	data = data | (color->r << RED_OFFSET);
	data = data | (color->b << BLUE_OFFSET);
	data = data | (color->g << GREEN_OFFSET);
	return data;
}

int main(int argc, const char ** argv, const char ** env) {

	Verilated::commandArgs(argc, argv);

	Vppu * dut = new Vppu;
	Verilated::traceEverOn(true);
	VerilatedVcdC * tfp = new VerilatedVcdC;
	dut->trace(tfp, 99);
	tfp->open("ppu.vcd");

	//PPU Inputs:
	dut->clk	= 0;
	dut->reset 	= 0;
	dut->writedata 	= 0;
	dut->write	= 0;
	dut->chipselect = 0;
	dut->address	= 0;

	//To write:
	dut->write	= 1; 
	dut->chipselect = 1;

	//Attr Table Entry
	attr_table_entry_t attr_table[NUM_SPRITES] = {
		{
			.coord = {
				.x = 50,
				.y = 1,
			},
			.sprite         = 0x0,
			.color_table    = 0x0,
			.id             = 0x0,
		},
		{
			.coord = {
				.x = 100,
				.y = 100,
			},
			.sprite         = 0x01,
			.color_table    = 0x02,
			.id             = 0x01,
		},
		{
			.coord = {
				.x = 50,
				.y = 1,
			},
			.sprite         = 0x0,
			.color_table    = 0x0,
			.id             = 0x0,
		},
		{
			.coord = {
				.x = 100,
				.y = 100,
			},
			.sprite         = 0x01,
			.color_table    = 0x02,
			.id             = 0x01,
		}
	};

	//Sprite Table Entry
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

	int time = 0;
	int clock = 0;

	// Write all of the sprites to the Sprite Attribute Table. Will take NUM_SPRITES clock cycles.
	for(int i = 0; i < NUM_SPRITES; i++) {
		//CLOCK HIGH
		dut->clk = 1;
		clock++;
		time += 10;

		std::cout << "Writing sprite attr table data" << std::endl;
		std::cout << std::bitset<32> (attr_to_int(&attr_table[i])) << std::endl;
		dut->writedata = attr_to_int(&attr_table[i]);
		dut->address = ATTR_TABLE_MEMORY_OFFSET + i;

		dut->eval();
		tfp->dump( time );

		//CLOCK LOW
		dut->clk = 0;
		time += 10;

		dut->eval();
		tfp->dump( time );

	}

	// Read all of the sprites attribute entries from the table. Will take 16 clock cycles. 
	// Compare them to what was input 
	for(int i = 0; i < NUM_SPRITES; ++i){
		dut->clk = 1;
		dut->ppu__DOT__taddr = ATTR_TABLE_MEMORY_OFFSET + i;
		dut->ppu__DOT__state = 3;
		dut->chipselect = 0;
		dut->write = 0;
		dut->eval();

		std::cout << "Reading sprite attr table data" << std::endl;
		std::cout << std::bitset<32> ( dut->ppu__DOT__sprite_attr ) << std::endl;
		//assert(dut->ppu__DOT__sprite_attr == attr_to_int(&attr_table[i]));

		dut->clk = 0;
		dut->eval();
	}


	for(int i = 0; i < 16; i++) {
		for (int c = 0; c < 4; c++) {
			//CLOCK HIGH
			dut->clk = 1;
			clock++;
			time += 10;

			//std::cout << attr_to_int(&attr) << std::endl;
			dut->writedata = sprite.line[i];
			dut->address = SPRITE_TABLE_MEMORY_OFFSET + i;

			dut->eval();
			tfp->dump( time );


			//CLOCK LOW
			dut->clk = 0;
			time += 10;

			dut->eval();
			tfp->dump( time );
		}
	}

	for(int i = 0; i < 16; i++) {
		for (int c = 0; c < 16; c++) {
			//CLOCK HIGH
			dut->clk = 1;
			clock++;
			time += 10;

			//std::cout << attr_to_int(&attr) << std::endl;
			dut->writedata = color_to_int(&color_palette.color[i]);
			dut->address = COLOR_TABLE_MEMORY_OFFSET + i;

			dut->eval();
			tfp->dump( time );


			//CLOCK LOW
			dut->clk = 0;
			time += 10;

			dut->eval();
			tfp->dump( time );
		}
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

