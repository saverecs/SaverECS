module doubleIntegrator(x,v,a)
	output x,v;

	mode loc
		begin
   		ddt x = v;
   		ddt v = a;
		end 

	initial begin 
		set begin
			mode == loc;
			x==0;
			v==0;	
			a==0;		
		end
	end

endmodule	
