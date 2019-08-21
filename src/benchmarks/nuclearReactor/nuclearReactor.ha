module atomic_reactor(temperature,c1,c2,r1,r2,shutdown)
	output temperature;

	mode loc
		begin
   		ddt temperature =  (0.1*temperature) - ( 50 + (r1*6) + (r2*10) );
   		ddt c1 = 1;
   		ddt c2 = 1;
		end 

	initial begin 
		set begin
			mode == loc;
			temperature==510;
			c1==20;
			c2==20;
			r1==0;
			r2==0;	
			shutdown==0;		
		end
	end

endmodule	
