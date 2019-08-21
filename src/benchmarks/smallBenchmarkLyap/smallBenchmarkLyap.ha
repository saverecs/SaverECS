module smallTest(x,y,v,u)
	output y,u;

	mode loc
		begin
   		ddt x = (2*y) + 1 + u;
   		ddt y = x + u;
		ddt v = 2*x*(2*y + 1 + u);
		end

	initial begin 
		set begin
			mode == loc;
			x == 1;
			y == 1;
			u == 0.5;
			v == 1;
		end
	end

endmodule
