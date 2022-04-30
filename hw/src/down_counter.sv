
module down_counter
	#(parameter
	N = 10)
	(input logic		clk,
	 input logic		reset,
	 input logic		en,
	 input logic		ld,
	 input logic [N-1:0] 	data_in,
	 output logic 		done);


 	 // How many clock cycles we should wait.
	 logic [N-1:0] count;

	 always_ff @(posedge clk) begin
		 if (reset) begin
			 count <= 0;
			 done  <= 0;
		 end
		 else if (ld) begin
			 count <= data_in;
			 done 	<= 0;
		 end
		 else if (en) begin
			 if (count == 0) done <= 1;
			 else count <= count - 1'b1; 
		 end
	 end
 endmodule
