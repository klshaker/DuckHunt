/*
 * Picture Processing Unit
 *
 * Bryce Natter
 * Columbia University
 */

`include "down_counter.sv"
`include "shift.sv"
`include "memory.sv"
`include "hex7seg.sv"

/* verilator lint_off DECLFILENAME */
/* verilator lint_off WIDTH */
/* verilator lint_off UNUSED */
module ppu
	#(parameter
	SPRITE_ATTS = 16)
	(input logic        	clk,
	input logic 	   	reset,
	input logic [31:0]  	writedata,
	input logic 	   	write,
	input 			chipselect,
	input logic [15:0]  	address,

	output logic [6:0]	HEX0, HEX1, HEX2, HEX3, HEX4, HEX5,
	output logic [7:0] 	VGA_R, VGA_G, VGA_B,
	output logic 		VGA_CLK, VGA_HS, VGA_VS, VGA_BLANK_n,
	output logic 	   	VGA_SYNC_n);


	logic [2:0]		mem_write;
	logic [10:0]		hcount;
	logic [9:0]		vcount;
	logic [31:0]		sprite_attr, sprite;

	logic [SPRITE_ATTS-1:0] dc_en, dc_ld, dc_done;
	logic [SPRITE_ATTS-1:0]	sh_en, sh_ld;

	logic [31:0]		w_data;
	logic [15:0]		w_addr;

	logic [7:0]		s_addr;
       	logic [3:0]		a_addr;
       	logic [3:0]		c_addr;
	logic [31:0]		color_out;

	logic [7:0]		background_r, background_g, background_b;

	logic [1:0]		sh_out [SPRITE_ATTS - 1: 0];
	logic [3:0]		color [SPRITE_ATTS - 1: 0];
	logic [3:0]		scount;
	logic [9:0]		tx;// ty;
	logic [7:0]		taddr;
	logic [3:0]		tcolor;



	assign a_addr = mem_write[0] ? w_addr[3:0]: taddr[3:0];
	assign s_addr = mem_write[1] ? w_addr[7:0]: taddr;
	assign c_addr = mem_write[2] ? w_addr[3:0]: tcolor;

	vga_counters 		counters(.clk50(clk), .*);
	memory #(32,  16, 4) 	attr_table  (clk, mem_write[0], a_addr[3:0], w_data, sprite_attr);
	memory #(32, 256, 8)  	sprite_table(clk, mem_write[1], s_addr[7:0], w_data, sprite);
	memory #(32,  16, 4)  	color_table (clk, mem_write[2], c_addr[3:0], w_data, color_out);

	genvar k;
	generate
	for(k = 0; k <= SPRITE_ATTS - 1; k = k+1) begin : pixelgen
		down_counter dc(clk, dc_en[k], dc_ld[k], tx, dc_done[k]);
		shift sh(clk, sh_en[k], sh_ld[k], sprite, sh_out[k]);
	end
	endgenerate
	assign sh_en = dc_done;


	always_ff @(posedge clk) begin
		mem_write <= 3'b0;
		if (chipselect && write) begin
			case(address[9:8])
				2'b00: mem_write[0] <= 1'b1;
				2'b01: mem_write[1] <= 1'b1;
				2'b10: mem_write[2] <= 1'b1;
				default: mem_write  <= 3'b0;
			endcase
			w_addr <= address;
			w_data <= writedata;

		end
	end


			
	enum logic [3:0] {CHECK, SET, IDLE, OUTPUT} state;
	always_ff @(posedge clk) begin
		dc_en <= 16'b0; dc_ld <= 16'b0; sh_ld <= 16'b0;
		case (state)
			CHECK: begin
				//ty	<= sprite_attr[9:0];
				if (scount == 15 || hcount == 11'd1598) state <= IDLE;
				else if (vcount <= sprite_attr[9:0] + 15 && vcount >= sprite_attr[9:0]) begin
					tx	<= sprite_attr[19:10];
					tcolor	<= sprite_attr[31:28];
					taddr	<= sprite_attr[27:20];

					color[scount]	<= sprite_attr[31:28];
					dc_ld[scount]	<= 1'b1;
					sh_ld[scount]	<= 1'b1;

					state		<= SET;
				end else taddr 	<= {4'b0, scount + 4'b1};

			end
			SET: begin
				if (scount == 15 || hcount == 11'd1598) state <= IDLE;
				else state  <= CHECK;
				taddr <= {4'b0, scount + 4'b1};
				scount <= scount +1;
			end
			IDLE: begin
				if (hcount == 11'd1599) begin
					state <= OUTPUT;
					dc_en <= {16{1'b1}};
				end
			end
			OUTPUT: begin
				dc_en <= {16{1'b1}};
				if (hcount == 11'd1279) begin 
					state <= CHECK;
					scount <= 4'b0; 
				end
				tcolor <= 4'b0;
				for (int j = 0; j < scount; j++) begin
				
					if (sh_out[j] != 2'b0) begin
						tcolor <= color[j] + {2'b0, sh_out[j]};
						break;
					end
				end
				background_r <= color_out[7:0];
				background_g <= color_out[15:8];
				background_b <= color_out[23:16];
			end
			default: state <= CHECK;

		endcase //case
	end //always_ff



	//Write background color to VGA
	always_comb begin
		if (VGA_BLANK_n )
			{VGA_R, VGA_G, VGA_B} = {8'h0, 8'h0, 8'h0};
		//if (hcount[10:6] == 5'd3 && vcount[9:5] == 5'd3)
			//{VGA_R, VGA_G, VGA_B} = {8'hff, 8'hff, 8'hff};
		else
			{VGA_R, VGA_G, VGA_B} = {background_r, background_g, background_b};
	end


	hex7seg h0(address[3:0],	HEX0);
	hex7seg h1(address[7:4],	HEX1);

	hex7seg h2(address[11:8],	HEX2);
	hex7seg h3(address[15:12],	HEX3);

	hex7seg h4(scount[3:0],		HEX4);
	hex7seg h5(state[3:0],		HEX5);

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
