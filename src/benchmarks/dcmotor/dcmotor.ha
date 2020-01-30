module dcmotor(angVal,i,voltage)
	output angVal, i;

 	parameter
		K= 0.01,
		J= 0.01,
		L= 0.5,
		R= 1,
		b= 0.1;

	mode loc
		begin
   		ddt angVal =  (-0.1/0.01)*angVal + (0.01/0.01)*i;
   		ddt i = ((0.01/0.5)*angVal - (1/0.5)*i) + (voltage/0.5);
		end 

	initial begin 
		set begin
			mode == loc;
			angVal==0;
			i==0;
			voltage==1.0;
		end
	end

endmodule	
