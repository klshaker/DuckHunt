
module shift
	(input logic 		      clk,
	 input logic 		      en,
	 input logic 		      ld,
	 input logic [47:0] 	      data_in,
	 output logic [2:0] data_out);

	 logic [2:0] mem[15:0];
	 
	always_ff @(posedge clk) begin
		if (en) begin
			mem[0] 	<= 3'b0;
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
		if (ld) begin
			mem[0] 	<= data_in[47:45];
			mem[1] 	<= data_in[44:42]; 
			mem[2] 	<= data_in[41:39]; 
			mem[3] 	<= data_in[38:36]; 
			mem[4] 	<= data_in[35:33]; 
			mem[5] 	<= data_in[32:30]; 
			mem[6] 	<= data_in[29:27]; 
			mem[7] 	<= data_in[26:24]; 
			mem[8] 	<= data_in[23:21]; 
			mem[9] 	<= data_in[20:18]; 
			mem[10] <= data_in[17:15]; 
			mem[11] <= data_in[14:12]; 
			mem[12] <= data_in[11:9]; 
			mem[13] <= data_in[8:6]; 
			mem[14] <= data_in[5:3]; 
			mem[15] <= data_in[2:0]; 
		//	mem[0] 	<= data_in[63:60];
		//	mem[1] 	<= data_in[59:56]; 
		//	mem[2] 	<= data_in[55:52]; 
		//	mem[3] 	<= data_in[51:48]; 
		//	mem[4] 	<= data_in[47:44]; 
		//	mem[5] 	<= data_in[43:40]; 
		//	mem[6] 	<= data_in[39:36]; 
		//	mem[7] 	<= data_in[35:32]; 
		//	mem[8] 	<= data_in[31:28]; 
		//	mem[9] 	<= data_in[27:24]; 
		//	mem[10] <= data_in[23:20]; 
		//	mem[11] <= data_in[19:16]; 
		//	mem[12] <= data_in[15:12]; 
		//	mem[13] <= data_in[11:8]; 
		//	mem[14] <= data_in[7:3]; 
		//	mem[15] <= data_in[2:0]; 
		end
	end
	//assign data_out = mem[15];
 endmodule
