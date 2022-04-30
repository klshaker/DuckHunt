// Reads an entire sprite into memory. Outputs 2 bits of that sprite per clock
// cycle. Shifts all remaining bits over one memory location.
module shift
	(input logic 		 clk,
	 input logic		 reset, 
	 input logic 		 en,
	 input logic 		 ld,
	 input logic [31:0] 	 data_in,
	 output logic [1:0]  	 data_out);

 	 // 16 memory locations each 2 bits in size.
	 logic [1:0] mem[15:0];
	 
	always_ff @(posedge clk) begin
		if (reset) begin
			mem[0] 	 <= 2'b0;
			mem[1] 	 <= 2'b0; 
			mem[2] 	 <= 2'b0; 
			mem[3] 	 <= 2'b0; 
			mem[4] 	 <= 2'b0; 
			mem[5] 	 <= 2'b0; 
			mem[6] 	 <= 2'b0; 
			mem[7] 	 <= 2'b0; 
			mem[8] 	 <= 2'b0; 
			mem[9] 	 <= 2'b0; 
			mem[10]  <= 2'b0; 
			mem[11]  <= 2'b0; 
			mem[12]  <= 2'b0; 
			mem[13]  <= 2'b0; 
			mem[14]  <= 2'b0; 
			mem[15]  <= 2'b0; 
			data_out <= 2'b0;
		end
		else if (en) begin
			mem[0] 	<= 2'b0;
			mem[1] 	<= mem[0];
			mem[2] 	<= mem[1];
			mem[3] 	<= mem[2];
			mem[4] 	<= mem[3];
			mem[5] 	<= mem[4];
			mem[6] 	<= mem[5];
			mem[7] 	<= mem[6];
			mem[8] 	<= mem[7];
			mem[9] 	<= mem[8];
			mem[10] <= mem[9];
			mem[11] <= mem[10];
			mem[12] <= mem[11];
			mem[13] <= mem[12];
			mem[14] <= mem[13];
			mem[15] <= mem[14];
			data_out <= mem[15];
		end
		else if (ld) begin
			mem[0] 	<= data_in[31:30];
			mem[1] 	<= data_in[29:28]; 
			mem[2] 	<= data_in[27:26]; 
			mem[3] 	<= data_in[25:24]; 
			mem[4] 	<= data_in[23:22]; 
			mem[5] 	<= data_in[21:20]; 
			mem[6] 	<= data_in[19:18]; 
			mem[7] 	<= data_in[17:16]; 
			mem[8] 	<= data_in[15:14]; 
			mem[9] 	<= data_in[13:12]; 
			mem[10] <= data_in[11:10]; 
			mem[11] <= data_in[9:8]; 
			mem[12] <= data_in[7:6]; 
			mem[13] <= data_in[5:4]; 
			mem[14] <= data_in[3:2]; 
			mem[15] <= data_in[1:0]; 
		end
		else data_out <= 2'b0;
	end
	//assign data_out = mem[15];
 endmodule
