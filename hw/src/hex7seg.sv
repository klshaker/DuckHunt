module hex7seg(input logic  [3:0] a,
	       output logic [6:0] y);

   /* Replace this comment and the code below it with your solution */
	always_comb
		case (a)
		4'd0:		y = 7'h40;
		4'd1:		y = 7'h79;
		4'd2:		y = 7'h24;
		4'd3:		y = 7'h30;
		4'd4:		y = 7'h19;
		4'd5:		y = 7'h12;
		4'd6:		y = 7'h02;
		4'd7:		y = 7'h78;
		4'd8:		y = 7'h00;
		4'd9:		y = 7'h10;
		4'd10:		y = 7'h08;
		4'd11:		y = 7'h03;
		4'd12:		y = 7'h46;
		4'd13:		y = 7'h21;
		4'd14:		y = 7'h06;
		4'd15:		y = 7'h0e;
		default:	y = 7'h00;
		endcase
   
endmodule
