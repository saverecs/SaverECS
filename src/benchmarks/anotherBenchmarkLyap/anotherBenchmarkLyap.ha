module aBenchmark(x,v,u)
	output x,u;

	mode loc
		begin
   		ddt x = -x + u;
		ddt v = -x*(x-u)-u*(u-x);
		end

	initial begin 
		set begin
			mode == loc;
			x == 1;
			u == 1;
			v == 2;
		end
	end

endmodule
