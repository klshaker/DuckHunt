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
	input logic [11:0]  	address,

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
	sprite_attr_table	#(32,  16, 4)  memory(clk, mem_write[0], address[3:0], writedata, sprite_attr);
	sprite_table 		#(32, 256, 8)  memory(clk, mem_write[1], address[7:0], writedata, sprite);
	color_table 		#(32,  16, 4)  memory(clk, mem_write[2], address[3:0], writedata, sprite);

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
			mem_write[address[11:9]] = 1;

		end
	end


	logic [3:0]	scount;
	logic [9:0]	tx, ty;
	logic [12:0]	taddr;
	logic [3:0]	tcolor;
	logic [3:0] 	colors[3:0];
			
	enum logic [3:0] {CHECK, SET, IDLE, OUTPUT} state;
	always_ff @(posedge clk) begin
		scount = 3'b0;
		dc_en, dc_ld, sh_ld <= 15'b0;
		case (state)
			CHECK: begin
				ty	<= sprite_attr[9:0];
				tx	<= sprite_attr[19:10];
				tcolor	<= sprite_attr[31:28];
				if (scount == 15) state <= IDLE;
				else if (vcount <= attr.y + 15 && vcount >= attr.y) begin
					state 	<= SET;
					taddr	<= sprite_attr[27:20];
					dc_ld[scount] <= 1'b1;
					sh_ld[scount] <= 1'b1;
				end else taddr 	<= scount + 1;

			end
			SET: begin
				scount <= scount +1;
				taddr  <= scount + 1;
				state  <= CHECK;
			end
			IDLE: begin
				if (hcount == 1278) begin
					state <= OUTPUT;
					dc_en <= {15{1'b1}};
				end
			end
			OUTPUT: begin
				if (hcount == 1599) state <= CHECK;
				for (int i = 0; i < 15; i++)
				{
					if (sh_out[i] != 0)
						color_sel <= colors[i] + sh_out[i];
						break;
				}
				background_r <= color_table[color_sel][7:0];
				background_g <= color_table[color_sel][15:8];
				background_b <= color_table[color_sel][23:16];
			end;



	//Write background color to VGA
	always_comb begin
		if (VGA_BLANK_n )
			{VGA_R, VGA_G, VGA_B} = {8'h0, 8'h0, 8'h0};
		if (hcount[10:6] == 5'd3 && vcount[9:5] == 5'd3)
			{VGA_R, VGA_G, VGA_B} = {8'hff, 8'hff, 8'hff};
		else
			{VGA_R, VGA_G, VGA_B} = {background_r, background_g, background_b};
		end
	end

	function

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
