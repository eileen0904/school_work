module ex8(input clk, sw_control, reset, output [3:0]leds);
	Johnson(clk, sw_control, reset, leds);
endmodule

module D_FF(Q, D, clk);
	output Q;
	input D, clk;
	reg Q;
	always @(posedge clk)
		Q <= D;
endmodule

module Johnson(CLK, sw_control, reset, leds);
	wire [3:0]q;
	reg [3:0]d; 
	input CLK;
	input sw_control;
	input reset;
	output [3:0]leds;
	
	always @(posedge CLK)
		begin
			if(sw_control)
				begin
					d[3]= 0;
					d[2]= 0;
					d[1]= 0;
					d[0]= 0;
				end
		end	
		
	D_FF FF_1(q[0], ~q[3], CLK);
	D_FF FF_2(q[1], q[0], CLK);
	D_FF FF_3(q[2], q[1], CLK);
	D_FF FF_4(q[3], q[2], CLK);
	assign leds = q;
	
endmodule
