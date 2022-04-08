
module down_counter(
	#(parameter
	N = 10);
	(input logic		clk,
	(input logic		en,
	 input logic		ld,
	 input logic [N-1:0] 	data_in,
	 output logic 		done);


	 logic [N-1:0] count;

	 always_ff @(posedge clk) begin
		 if (ld) begin
			 count <= data_in;
			 done 	<= 0;
		 end
		 if (clk) begin
			 if (count == 0) done <= 1;
			 else count <= count - 1'b1; 
		 end
	 end
 endmodule
