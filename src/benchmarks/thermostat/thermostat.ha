module thermostat(temperature,u)
	output temperature,u;


	mode loc
		begin
   		ddt temperature = 0.5*u - 0.5*temperature;
		end

	initial begin 
		set begin
			mode == loc;
			temperature >= 55;
			temperature <= 75;
			u <= 100;
			u >= 20;
		end
	end

endmodule	
