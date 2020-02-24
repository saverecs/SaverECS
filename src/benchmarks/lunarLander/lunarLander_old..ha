module lunarLander(position, velocity, mass, FuelCommand, tempM, tempF)
	output position, velocity;

	mode loc
		begin
   		ddt position =  velocity ;
   		ddt velocity = FuelCommand/mass - 1.622;
		ddt mass = -FuelCommand/2800 ; 
		ddt FuelCommand = 0 ;
		ddt tempM = 0 ;
		ddt tempF = 0 ;
		end 

	initial begin 
		set begin
			mode == loc;
			position == 30;
			velocity == -2;
			mass == 1250 ;
			FuelCommand == 2027.5;
			tempM == 0 ;
			tempF == 0 ;
		end

	end

endmodule
