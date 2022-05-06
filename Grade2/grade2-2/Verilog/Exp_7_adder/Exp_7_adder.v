module ex7_1( input C0,  output C4, input[3:0] A,B, output[6:0]seg);
	wire[3:0]Sum;
	ripple_carry_4_bit_adder(Sum, C4, A, B, C0);
	seven(seg, Sum);
endmodule

module half_adder(output S, C, input x, y);
	xor(S, x, y);
	and(C, x, y);
endmodule
	
module full_adder(input x, y, z, output S, C);
	wire s;
	wire c[1:0];
	half_adder a(s,c[0],x,y);
	half_adder b(S,c[1],s,z);
	or(C, c[0], c[1]);
endmodule
	
module ripple_carry_4_bit_adder(output[3:0]Sum, output C4, input[3:0] A,input [3:0]B,input C0);
	wire c1, c2, c3;
	full_adder a(A[0], B[0], C0, Sum[0], c1);
	full_adder b(A[1], B[1], c1, Sum[1], c2);
	full_adder c(A[2], B[2], c2, Sum[2], c3);
	full_adder d(A[3], B[3], c3, Sum[3], C4);
endmodule

module seven(output reg[6:0]seg,input [3:0]sum);
	always @(sum)
	begin
	case (sum)
		4'b0000:seg=7'b1000000;
		4'b0001:seg=7'b1111001;
		4'b0010:seg=7'b0100100;
		4'b0011:seg=7'b0110000;
		4'b0100:seg=7'b0011001;
		4'b0101:seg=7'b0010010;
		4'b0110:seg=7'b0000010;
		4'b0111:seg=7'b1111000;
		4'b1000:seg=7'b0000000;
		4'b1001:seg=7'b0011000;
		4'b1010:seg=7'b0001000;
		4'b1011:seg=7'b0000011;
		4'b1100:seg=7'b1000110;
		4'b1101:seg=7'b0100001;
		4'b1110:seg=7'b0000110;
		4'b1111:seg=7'b0001110;
	endcase
	end
endmodule