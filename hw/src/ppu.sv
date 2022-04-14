/*
 * Picture Processing Unit
 *
 * Bryce Natter
 * Columbia University
 */

`include "down_counter.sv"
`include "shift.sv"
`include "memory.sv"

module ppu
	#(parameter
	SPRITE_ATTS = 1)
	(input logic        	clk,
	input logic 	   	reset,
	input logic [31:0]  	writedata,
	input logic 	   	write,
	input 			chipselect,
	input logic [3:0]  	address,

	output logic [7:0] 	VGA_R, VGA_G, VGA_B,
	output logic 		VGA_CLK, VGA_HS, VGA_VS, VGA_BLANK_n,
	output logic 	   	VGA_SYNC_n);


	logic [1:0]	mem_write;
	logic [10:0]    hcount, sprite_x;
	logic [9:0]     vcount, sprite_y;
	logic [31:0]	sprite_attr, sprite;
	logic [15:0] 	dc_en, dc_ld, dc_done;
	logic [15:0] 	sh_en, sh_ld, sh_done;
	logic [3:0] 	sh_out [2:0];

	logic [7:0] 	background_r, background_g, background_b;

	vga_counters 		counters(.clk50(clk), .*);
	sprite_attr_table	memory(clk, mem_write[0], address, writedata, sprite_attr);
	sprite_table 		memory(clk, mem_write[1], address, writedata, sprite);

	genvar k;
	generate
	for(k = 0; k < SPRITE_ATTS; k = k+1)
		begin: down_counters
			down_counter(clk, dc_en[k], dc_ld[k], sprite_x, dc_done[k]);
		end
		begin: shifters
			shift(clk, sh_en[k], sh_ld[k], sprite, sh_out[k]);
		end
	endgenerate
	assign sh_en = dc_done;


	always_ff @(posedge clk)
		mem_write = 0;
		if (reset) begin
			background_r <= 8'h0;
			background_g <= 8'h0;
			background_b <= 8'h80;
		end else if (chipselect && write) begin
			mem_write[write[7:6]] = 1;

		end
	end


	enum logic [1:0] {A, S, O} state;
	logic [3:0] xfer_addr = 0;
	always_ff @(posedge clk)
	dc_ld = 15'b0;
		if (hcount == 1279) begin
			state <= O;
			dc_en = {15{1'b1}};
		end
		if (hcount == 1599) begin
			state <= S;
			dc_ld[addr] 
			xfer_addr <= xfer_addr + 1;

			

	always_comb begin
		if (VGA_BLANK_n )
			{VGA_R, VGA_G, VGA_B} = {8'h0, 8'h0, 8'h0};
		if (hcount[10:6] == 5'd3 && vcount[9:5] == 5'd3)
			{VGA_R, VGA_G, VGA_B} = {8'hff, 8'hff, 8'hff};
		else
			{VGA_R, VGA_G, VGA_B} = {background_r, background_g, background_b};
		end
	end

endmodule

module vga_counters(
 input logic 	     clk50, reset,
 output logic [10:0] hcount,  // hcount[10:1] is pixel column
 output logic [9:0]  vcount,  // vcount[9:0] is pixel row
 output logic 	     VGA_CLK, VGA_HS, VGA_VS, VGA_BLANK_n, VGA_SYNC_n);

/*
 * 640 X 480 VGA timing for a 50 MHz clock: one pixel every other cycle
 * 
 * HCOUNT 1599 0             1279       1599 0
 *             _______________              ________
 * ___________|    Video      |____________|  Video
 * 
 * 
 * |SYNC| BP |<-- HACTIVE -->|FP|SYNC| BP |<-- HACTIVE
 *       _______________________      _____________
 * |____|       VGA_HS          |____|
 */
   // Parameters for hcount
   parameter HACTIVE      = 11'd 1280,
             HFRONT_PORCH = 11'd 32,
             HSYNC        = 11'd 192,
             HBACK_PORCH  = 11'd 96,   
             HTOTAL       = HACTIVE + HFRONT_PORCH + HSYNC +
                            HBACK_PORCH; // 1600
   
   // Parameters for vcount
   parameter VACTIVE      = 10'd 480,
             VFRONT_PORCH = 10'd 10,
             VSYNC        = 10'd 2,
             VBACK_PORCH  = 10'd 33,
             VTOTAL       = VACTIVE + VFRONT_PORCH + VSYNC +
                            VBACK_PORCH; // 525

   logic endOfLine;
   
   always_ff @(posedge clk50 or posedge reset)
     if (reset)          hcount <= 0;
     else if (endOfLine) hcount <= 0;
     else  	         hcount <= hcount + 11'd 1;

   assign endOfLine = hcount == HTOTAL - 1;
       
   logic endOfField;
   
   always_ff @(posedge clk50 or posedge reset)
     if (reset)          vcount <= 0;
     else if (endOfLine)
       if (endOfField)   vcount <= 0;
       else              vcount <= vcount + 10'd 1;

   assign endOfField = vcount == VTOTAL - 1;

   // Horizontal sync: from 0x520 to 0x5DF (0x57F)
   // 101 0010 0000 to 101 1101 1111
   assign VGA_HS = !( (hcount[10:8] == 3'b101) &
		      !(hcount[7:5] == 3'b111));
   assign VGA_VS = !( vcount[9:1] == (VACTIVE + VFRONT_PORCH) / 2);

   assign VGA_SYNC_n = 1'b0; // For putting sync on the green signal; unused
   
   // Horizontal active: 0 to 1279     Vertical active: 0 to 479
   // 101 0000 0000  1280	       01 1110 0000  480
   // 110 0011 1111  1599	       10 0000 1100  524
   assign VGA_BLANK_n = !( hcount[10] & (hcount[9] | hcount[8]) ) &
			!( vcount[9] | (vcount[8:5] == 4'b1111) );

   /* VGA_CLK is 25 MHz
    *             __    __    __
    * clk50    __|  |__|  |__|
    *        
    *             _____       __
    * hcount[0]__|     |_____|
    */
   assign VGA_CLK = hcount[0]; // 25 MHz clock: rising edge sensitive
   
endmodule
