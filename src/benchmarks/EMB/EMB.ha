module doubleIntegrator(Motor_Current, Caliper_Position, Voltage, Xc)

	output Caliper_Position, Voltage;

	mode loc
		begin
		ddt Motor_Current = (1/0.001) * ( Voltage - ( Motor_Current*(0.3 + ((0.02*0.02)/0.1) ) )) ;
		ddt Caliper_Position = (0.02/(113.1167*0.1))*Motor_Current ;
		end 

	initial begin 
		set begin
			mode == loc;
			Motor_Current==0;
			Caliper_Position==0;	
			Voltage==0;
			Xc==0;				
		end
	end

endmodule	
