module thermostat(temp,u)
	output temp,u;

 	parameter
		val = 0.5;

	mode loc
		begin
   		ddt temp = val*u - val*temp;
		end

	property inv loc
		mode == loc |=> u==70;
	endproperty

	initial begin 
		set begin
			mode == loc;
			temp == 65;
		end
	end

endmodule	
