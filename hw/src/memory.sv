
module memory
	#(parameter
	WORD_SIZE = 32,					// Size of RAM words
	NUM_WORDS = 16,					// Number of words to store in RAM
	ADDR_BITS = 4)					// Number of RAM address bits
	(input logic			clk,    	// Clock
	 input logic			we,		// Write enable
	 input logic [ADDR_BITS-1:0]	addr,		// Address to read/write
	 input logic [WORD_SIZE-1:0] 	data_in,	// Data to write
	 output logic [WORD_SIZE-1:0] 	data_out);	// Data to read


	 logic [ADDR_BITS-1:0] 	mem[WORD_SIZE - 1:0];

	 always_ff @(posedge clk) begin
		 if (we) mem[addr] <= data_in;
		 data_out <= mem[addr];
	 end

endmodule
