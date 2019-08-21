module thermostat(temp,u)
	output temp,u;

 	parameter
		val = 0.5;

	mode loc
		begin
   		ddt temp = val*u - val*temp;
		end

	initial begin 
		set begin
			mode == loc;
			temp == 65;
			u == 70;
		end
	end

endmodule	
