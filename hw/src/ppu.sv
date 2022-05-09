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
	VISIBLE_SPRITES = 8,
	SPRITE_ATTRS = 64
	)
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


        // which table in memroy to write to (if any).
	logic [2:0]		mem_write;
	// which horizontal pixel we are currently on. 
	logic [10:0]		hcount;
	// which vertical pixel we are currently on.
	logic [9:0]		vcount;
	logic [31:0]		sprite_attr, sprite;

	// down counter enable and load variables.
	logic [VISIBLE_SPRITES-1:0]	dc_en, dc_ld, dc_done, dc_r;
	// shifter enable and load variables.
	logic [VISIBLE_SPRITES-1:0]	sh_en, sh_ld, sh_r;

	logic [31:0]		w_data;
	logic [15:0]		w_addr;

	logic [9:0]		s_addr;
       	logic [5:0]		a_addr;
       	logic [5:0]		c_addr;
	logic [31:0]		color_out;

	logic [7:0]		background_r, background_g, background_b;

	logic [1:0]		sh_out [VISIBLE_SPRITES - 1: 0];
	logic [3:0]		color [VISIBLE_SPRITES - 1: 0];
	// attribute count variable to loop through attribute table entries. 
	// vc variable to keep track of how many attributes are actually
	// visible on screen.
	logic [5:0]		ac, vc;
	logic [9:0]		tx; // ty;
	logic [7:0]		sr_addr, ar_addr;
	logic [5:0]		tcolor;
	logic [15:0]		haddr;


	assign a_addr = mem_write[0] ? w_addr[5:0]: ar_addr[5:0];
	assign c_addr = mem_write[1] ? w_addr[5:0]: tcolor;
	assign s_addr = mem_write[2] ? w_addr[7:0]: sr_addr;

	vga_counters 		counters(.clk50(clk), .*);
	memory #(32,  64, 6) 	attr_table  (.clk(clk), .we(mem_write[0]), .addr(a_addr[5:0]), .data_in(w_data), .data_out(sprite_attr));
	memory #(32,  64, 6)  	color_table (.clk(clk), .we(mem_write[1]), .addr(c_addr[5:0]), .data_in(w_data), .data_out(color_out));
	memory #(32, 1024, 10) 	sprite_table(.clk(clk), .we(mem_write[2]), .addr(s_addr[9:0]), .data_in(w_data), .data_out(sprite));

	genvar k;
	generate
	for(k = 0; k <= VISIBLE_SPRITES - 1; k = k+1) begin : pixelgen
		down_counter dc(.clk(clk), .en(dc_en[k]), .ld(dc_ld[k]), .reset(dc_r[k]), .data_in(tx), .done(dc_done[k]));
		shift sh(.clk(clk), .en(sh_en[k]), .ld(sh_ld[k]), .reset(sh_r[k]), .data_in(sprite), .data_out(sh_out[k]));
	end
	endgenerate
	assign sh_en = dc_done;

	always_ff @(posedge clk) begin
		if (address) haddr <= address;
	end


	always_ff @(posedge clk) begin
		mem_write <= 3'b0;
		if (chipselect && write) begin
			// The first two bits of the address tell us which
			// table we are writing to. 
			// 0X0000 Sprite Attribute Table 
			// 0x0100 Sprite Table 
			// 0x0200 Color Table
			case(address[9:8])
				2'b00: mem_write[0]	<= 1'b1;
				2'b01: mem_write[1]	<= 1'b1;
				default: mem_write[2]	<= 1'b1;
			endcase
			w_addr <= address;
			w_data <= writedata;
		end
	end
			
	enum logic [3:0] {A_INDEX, CHECK, S_INDEX, SET, IDLE, OUTPUT} state;
	always_ff @(posedge clk) begin
		dc_en <= {VISIBLE_SPRITES{1'b0}}; dc_ld <={VISIBLE_SPRITES{1'b0}}; dc_r <= {VISIBLE_SPRITES{1'b0}};
		sh_ld <= {VISIBLE_SPRITES{1'b0}}; sh_r <= {VISIBLE_SPRITES{1'b0}};
		case (state)
			A_INDEX: begin //Attr table index set, data available next cycle
				state <= CHECK;
			end
			CHECK: begin //Attr table output ready, check y
				if (ac == SPRITE_ATTRS - 1'b1 || vc == VISIBLE_SPRITES - 1'b1 || hcount == 11'd1598) state <= IDLE;
				else if (vcount <= sprite_attr[9:0] + 15 && vcount >= sprite_attr[9:0]) begin
					tx	<= sprite_attr[19:10];
					sr_addr	<= (sprite_attr[27:20] << 4) + (vcount - sprite_attr[9:0]);
					color[vc]	<= sprite_attr[31:28];
					state		<= S_INDEX;

				end else begin
					ar_addr	<= {2'b0, ac + 4'b1};
					ac 	<= ac + 1'b1;
					state	<= A_INDEX;
				end

			end
			S_INDEX: begin //Sprite table index set, data available next cycle
				//Prep pixel_gen modules
				dc_ld[vc]	<= 1'b1;
				sh_ld[vc]	<= 1'b1;

				//We can use SET state to skip A_INDEX state 
				ar_addr		<= {2'b0, ac + 4'b1};
				ac		<= ac + 1'b1;
				state		<= SET;
			end
			SET: begin //Sprite table output ready, just wait
				if (ac == SPRITE_ATTRS - 1'b1 || hcount == 11'd1598) state <= IDLE;
				else state  <= CHECK;
				vc	<= vc + 1'b1;
			end
			IDLE: begin
				if (hcount == 11'd1599) begin
					state <= OUTPUT;
					dc_en <= {VISIBLE_SPRITES{1'b1}};
				end
			end
			OUTPUT: begin
				dc_en <= hcount[0] ? {VISIBLE_SPRITES{1'b0}} : {VISIBLE_SPRITES{1'b1}};
				if (hcount == 11'd1279) begin 
					dc_r	<= {VISIBLE_SPRITES{1'b1}};
					sh_r	<= {VISIBLE_SPRITES{1'b1}};
					state	<= A_INDEX;
					ar_addr	<= 8'b0;
					ac	<= 4'b0; 
					vc	<= 4'b0; 
				end
				tcolor <= 6'b0;
				if(sh_out[0] != 2'b0)	   tcolor <= color[0] + {3'b0, sh_out[0]};
				else if(sh_out[1] != 2'b0) tcolor <= color[1] + {3'b0, sh_out[1]};
				else if(sh_out[2] != 2'b0) tcolor <= color[2] + {3'b0, sh_out[2]};
				else if(sh_out[3] != 2'b0) tcolor <= color[3] + {3'b0, sh_out[3]};
				else if(sh_out[4] != 2'b0) tcolor <= color[4] + {3'b0, sh_out[4]};
				else if(sh_out[5] != 2'b0) tcolor <= color[5] + {3'b0, sh_out[5]};
				else if(sh_out[6] != 2'b0) tcolor <= color[6] + {3'b0, sh_out[6]};
				else if(sh_out[7] != 2'b0) tcolor <= color[7] + {3'b0, sh_out[7]};

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
			{VGA_R, VGA_G, VGA_B} = {background_r, background_g, background_b};
		else
			{VGA_R, VGA_G, VGA_B} = {8'h0, 8'h0, 8'h0};
	end


	hex7seg h0(haddr[3:0],	HEX0);
	hex7seg h1(haddr[7:4],	HEX1);

	hex7seg h2(haddr[11:8],	HEX2);
	hex7seg h3(haddr[15:12],	HEX3);

	hex7seg h4(ac[3:0],		HEX4);
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
