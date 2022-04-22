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
	SPRITE_ATTS = 16)
	(input logic        	clk,
	input logic 	   	reset,
	input logic [31:0]  	writedata,
	input logic 	   	write,
	input 			chipselect,
	input logic [11:0]  	address,

	output logic [7:0] 	VGA_R, VGA_G, VGA_B,
	output logic 		VGA_CLK, VGA_HS, VGA_VS, VGA_BLANK_n,
	output logic 	   	VGA_SYNC_n);


	logic [2:0]	mem_write;
	logic [10:0]    hcount;
	logic [9:0]     vcount;
	logic [31:0]	sprite_attr, sprite;
	logic [SPRITE_ATTS-1:0] 	dc_en, dc_ld, dc_done;
	logic [SPRITE_ATTS-1:0] 	sh_en, sh_ld;
	logic [7:0] 	m_address;
       	logic [3:0]	c_address;
	logic [31:0] 	color_out;
	//logic [3:0] 	sh_out [2:0];

	logic [7:0] 	background_r, background_g, background_b;

	logic [1:0] sh_out [SPRITE_ATTS - 1: 0];
	logic [3:0] color [SPRITE_ATTS - 1: 0];
	logic [3:0]	scount;
	logic [9:0]	tx;// ty;
	logic [7:0]	taddr;
	logic [3:0]	tcolor;
	assign m_address = write ? address[7:0]: taddr;
	assign c_address = write ? address[3:0]: tcolor;

	vga_counters 		counters(.clk50(clk), .*);
	memory #(32,  16, 4) 	sprite_attr_table(clk, mem_write[0], m_address[3:0], writedata, sprite_attr);
	memory #(32, 256, 8)  	sprite_table(clk, mem_write[1], m_address[7:0], writedata, sprite);
	memory #(32,  16, 4)  	color_table(clk, mem_write[2], c_address[3:0], writedata, color_out);



	genvar k;
	generate
	for(k = 0; k < SPRITE_ATTS - 1; k = k+1)
		begin: down_counters
			down_counter dc(clk, dc_en[k], dc_ld[k], tx, dc_done[k]);
		end
		begin: shifters
			shift sh(clk, sh_en[k], sh_ld[k], sprite, sh_out[k]);
		end
	endgenerate
	assign sh_en = dc_done;


	always_ff @(posedge clk) begin
		mem_write <= 0;
		if (chipselect && write) begin
			mem_write[address[11:10]] <= 1;

		end
	end


			
	enum logic [3:0] {CHECK, SET, IDLE, OUTPUT} state;
	always_ff @(posedge clk) begin
		scount <= 4'b0; 
		dc_en <= 16'b0; dc_ld <= 16'b0; sh_ld <= 16'b0;
		case (state)
			CHECK: begin
				//ty	<= sprite_attr[9:0];
				tx	<= sprite_attr[19:10];
				tcolor	<= sprite_attr[31:28];
				if (scount == 15) state <= IDLE;
				else if (vcount <= sprite_attr[9:0] + 15 && vcount >= sprite_attr[9:0]) begin
					state 	<= SET;
					color[scount] <= sprite_attr[31:28];
					taddr	<= sprite_attr[27:20];
					dc_ld[scount] <= 1'b1;
					sh_ld[scount] <= 1'b1;
				end else taddr 	<= {4'b0, scount + 4'b1};

			end
			SET: begin
				scount <= scount +1;
				taddr <= {4'b0, scount + 4'b1};
				state  <= CHECK;
			end
			IDLE: begin
				if (hcount == 1278) begin
					state <= OUTPUT;
					dc_en <= {16{1'b1}};
				end
			end
			OUTPUT: begin
				if (hcount == 1599) state <= CHECK;
				for (int j = 0; j < SPRITE_ATTS; j++) begin
				
					if (sh_out[j] != 2'b0) begin
						tcolor <= color[j] + {2'b0, sh_out[j]};
						break;
					end
				end
				background_r <= color_out[7:0];
				background_g <= color_out[15:8];
				background_b <= color_out[23:16];
			end
			default: state <= state;

		endcase //case
	end //always_ff



	//Write background color to VGA
	always_comb begin
		if (VGA_BLANK_n )
			{VGA_R, VGA_G, VGA_B} = {8'h0, 8'h0, 8'h0};
		if (hcount[10:6] == 5'd3 && vcount[9:5] == 5'd3)
			{VGA_R, VGA_G, VGA_B} = {8'hff, 8'hff, 8'hff};
		else
			{VGA_R, VGA_G, VGA_B} = {background_r, background_g, background_b};
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
