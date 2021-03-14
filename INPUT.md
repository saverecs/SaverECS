# Input Format:
-----------------------------------
- Configuration File
Parameters are: 
	1) Comments line begin with # or // 
	2) MinMax-bounds of variables (plant and controller)
	3) max-value 
	4) sampling-time 
	5) release-time 
	6) sensing-time or sampling jitter 
	7) upper-bound  
	8) lower-bound  
	9) time-horizon 
	10) goal   
	11) noise-params 
	12) disturbance
	
- Plant Description
> This input format of the plant model is taken using the HASLAC specification. For more details, refer [ForFET: A Formal Feature Evaluation Tool for Hybrid Systems](https://link.springer.com/chapter/10.1007/978-3-319-68167-2_28) or http://cse.iitkgp.ac.in/~bdcaa/ForFET/ref.pdf .

	module modelname(state,control variables...)
	output output variables...;
	%location details
	    mode loc
		begin
		ddt x1  = (-50/1000)*v + (1/1000)*u;% flow equation
		.
		.
		% other flow equations
		end
	% initial states
	    initial begin
		set begin
		    mode == loc;
		    x1 <= 80;
		    x1 >= 50;
		    .
		    .
		% other state,control input initializations
		end
	    end
	endmodule
	


- Controller program
		
1) 	The input and the output argument variables are declare in a structure within a header file (controller.h) which is included in the controller program (controller.c). The names of the structure should be INPUT_VAL and RETURN_VAL as shown below:

				typedef struct{
					datatype outputVarName;

				}RETURN_VAL;

				typedef struct{
					datatype plantVarName; //The value sensed from the plant (remember to follow the same naming convention in the plant model). In addition, we use the keyword "state_" as a prefix before the sensed variables of the plant and prefix by the keyword "next_" to the output variables that are returned from the controller program.

					datatype otherControllerVarName;   

				}INPUT_VAL;

2)	The header file (for eg controller.h) should also include the declaration of the controller function as shown below:

				datatype controller(INPUT_VAL* iv, RETURN_VAL* rv);	//here the return datatype can be void, etc.
			Note that we assume all controller programs begin with the function name as "controller()," just like a C/C++ program begins with the function main().


3) 	We also assume that the definition of the function follows the following usual pattern, as reflected below. Note that we pass the arguments as reference variables, so we do not use the return statement to return the parameter.

				
				#include "controller.h"	//contains the structure declaration as shown in 1) and 2) above.
				
				void controller(INPUT_VAL* input, RETURN_VAL* ret_val) {

					local variable declaration 
					============================
						datatype v1,v2, ...., vn;
					
					retrieving values from the input variables onto the local variables
					====================================================================
					v1 = input->plantVarName;
					v2 = input->otherControllerVarName

					performing the logic of the controller program
					====================================================================
					actual calculation and taking logical decisions, etc.

					....
					
					Finally, update the computed values to the output variable and change the controller's current state (input variables) in the data structures.
					==============================================================================================================================================
					ret_val->outputVarName = vn;
					input->otherControllerVarName = vj;	//etc.,
