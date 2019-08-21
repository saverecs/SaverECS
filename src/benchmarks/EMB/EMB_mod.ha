module doubleIntegrator(I, X, Xe, Xc)

	output X, Xe;

	mode loc
		begin
   		ddt I = ( (1/0.001)*( (10000*Xe + 1000*Xc)) ) - ( (0.5 + ((0.02*0.02)/0.1))*I ) ;
   		ddt X = (0.02/(113.1167 * 0.1))*I;
		end 

	initial begin 
		set begin
			mode == loc;
			I==0;
			X==0;	
			Xe==0;
			Xc==0;				
		end
	end

endmodule	
