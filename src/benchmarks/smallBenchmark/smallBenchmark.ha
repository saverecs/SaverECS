module smallTest(x,y,u)
	output x,u;

	mode loc
		begin
   		ddt x = (2*y) + 1 + u;
   		ddt y = x + u;
		end

	initial begin 
		set begin
			mode == loc;
			x == 1;
			y == 1;
			u == 0.5;
		end
	end

endmodule	
