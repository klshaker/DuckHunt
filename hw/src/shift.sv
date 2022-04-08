
module shift_reg(
	#(parameter
	WORD_SIZE = 4,
	NUM_WORDS = 16)
	(input logic 					clk,
	 input logic 					en,
	 input logic 					ld,
	 input logic [(WORD_SIZE * NUM_WORDS)-1:0] 	data_in,
	 output logic [WORD_SIZE-1:0] 			data_out);

	 logic [WORD_SIZE-1:0] regs[NUM_WORDS-1:0];
	 
	 initial begin
		 foreach (regs[i])
		 regs[i] = WORD_SIZE'0;
	 end

	 always_ff @(posedge clk) begin
		if (en) begin
			data_out <= regs[NUM_WORDS-1];
			for (int $size(regs); i == 1; i--)
				regs[i] <= regs[i-1];
			regs[0] <= WORD_SIZE'0;
		end
		if (ld) regs <= data_in;
	end
 endmodule
