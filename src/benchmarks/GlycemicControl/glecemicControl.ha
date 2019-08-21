module lunarLander(Plasma_Glucose, Plasma_Insulin, Interstitial_Insulin, global_clock, Glucose_Infusion, Bloodstream_Insulin)
	output Plasma_Glucose, Plasma_Insulin;

	mode loc
		begin
   		ddt Plasma_Glucose =  -0.01*Plasma_Glucose - Interstitial_Insulin*(Plasma_Glucose+4.5) + Glucose_Infusion  ;
		ddt Interstitial_Insulin = -0.025*Interstitial_Insulin + 0.000013*Plasma_Insulin ;
   		ddt Plasma_Insulin = -0.093*(Interstitial_Insulin+15) + (1/12)*Bloodstream_Insulin; 
		ddt global_clock = 1 ;
		ddt Glucose_Infusion = 0 ;
		ddt Bloodstream_Insulin = 0 ;
		end 

	initial begin 
		set begin
			mode == loc;
			Plasma_Glucose == 0;
			Interstitial_Insulin == 0;
			Plasma_Insulin == 0 ;
			global_clock == 0;
			Glucose_Infusion == 0 ;
			Bloodstream_Insulin == 0 ;
		end

	end

endmodule	
