module thermostat(temp,u,lt)
	output temp,u;

 	parameter
		h = 0.2;

	mode loc
		begin
   		ddt temp = 0.5*u - 0.5*temp;
   		ddt lt = 1;
		end

	property inv loc
		mode == loc |=> lt <= h;
	endproperty

	initial begin 
		set begin
			mode == loc;
			temp == 65;
			lt == 0;
			u == 70;
		end
	end

endmodule	
