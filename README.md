# *Sa*fety *Ver*ification of *E*mbedded *C*ontrol *S*oftware Tool-chain
--------------------------------------------------------------------------------------------------------

Prerequisite (for running the tool):
================
	1) clang and llvm 
	$ sudo apt-get install clang
	$ sudo apt-get install llvm
	2) boost library for c++
	$ sudo apt-get install libboost-all-dev
	
How to build: 
================
	To generate the executable, type the following command in the terminal:

		$ cd fmsafe/src
		$ ./compile-cpp

  If the source code is modified, or a new file.cpp is added, it must also be added in the compile-cpp file before executing it.
  
*Note*:
================
- The files with the extensions .l and .y are the lex and yacc files. They are use to parse the input plant model file having the extension .ha (The language use to model the input plant is referred as HASLAC).
- If the .l and .y (present in the project src folder) files are modified, then execute the script file "build" before execute the above commands.
- If the llvm pass in our repository in `src/lib/` does not work/ throws an error while executing, please go to our [another repository](https://github.com/saverecs/CProgramToSMT.git), follow the instructions there and finally paste newly created llvm pass inside `src/lib/` folder.


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
> This input format of the plant model is taken using the HASLAC specification. For more details refer [ForFET: A Formal Feature Evaluation Tool for Hybrid Systems](https://link.springer.com/chapter/10.1007/978-3-319-68167-2_28) or http://cse.iitkgp.ac.in/~bdcaa/ForFET/ref.pdf .

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
		
		1) The input and the output argument variables are declare in a structure within a header file (controller.h) which is included in the controller program (controller.c). The names of the structure should be INPUT_VAL and RETURN_VAL as shown below:

				typedef struct{
					datatype outputVarName;

				}RETURN_VAL;

				typedef struct{
					datatype plantVarName; //The value sensed from the plant (remember to follow the same naming convention in the plant model as well. In addition, we use the key word "state_" as a prefix before the sensed variables of the plant and prefix by the key word "next_" to the output variables that is returned from the controller program.)

					datatype otherControllerVarName;   

				}INPUT_VAL;

		2)	The header file (for eg controller.h) should also include the declaration of the controller function as shown below:

				datatype controller(INPUT_VAL* iv, RETURN_VAL* rv);	//here the return datatype can be void, etc.
			Note that we assume all controller program begin with the function name as "controller()" just like a C/C++ program begin with the function main().


		3) We also assume that the definition of the function follows the following usual pattern as reflected below. Note that we pass the arguments as reference variables, so we do not use the return statement to return the parameter.

				
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
					
					Finally, update the computed values to the output variable and changing the current state of the controller(input variables) in the data structures
					==============================================================================================================================================
					ret_val->outputVarName = vn;
					input->otherControllerVarName = vj;	//etc.,

				}


Detailed Command Line Interface (CLI):
=========================================
		-h [ --help ]                produce help message
		-m [ --max-value ] arg       Assumed maximum [-m, +m] constant value that the plant and the controller can take
		-t [ --sampling-time ] arg   Sets the sampling time of the controller
		-r [ --release-time ] arg    Sets the release time of the controller
		-d [ --sensing-time ] arg    Sets the sensing time of the controller
		--precision arg              set precision for the SMT solver (default 0.001)
		-u [ --upper-bound ] arg     Set the depth or upper-bound of exploration for unrolling
		-l [ --lower-bound ] arg     Set the depth or lower-bound of exploration for unrolling
		-Z [ --time-horizon ] arg    Set the global time horizon of computation.
		-F [ --goal ] arg            Goal property to test, syntax: 'expr-1 & 
                                   expr-2'; For e.g. expr-1 is x>=2 expr-2 is x<=(-2)
		--noise-params arg           Sets the noise injecting parameters, syntax: 
                                   'var1:[t1,t2]=>[n1,n2] & ...'where t1 and t2 are start and end time duration of 
                                   the noise on var1 and the noise values can be fix [n1,n1] or range [n1,n2]
		--disturbance arg            Sets the disturbance parameters, syntax: 
                                   'var1:[t1,t2]=>[d1,d2] & ...'where t1 and t2 are start and end time duration of 
                                   the disturbance on var1 and the disturbance values can be fix [d1,d1] or range [d1,d2]
		-I [ --include-path ] arg    include file path
		-p [ --plant-file ] arg      include plant model file
		-c [ --controller-file ] arg include controller C program file
		-g [ --config-file ] arg     include configuration file (for future use)
		-o [ --output-file ] arg     output file name for redirecting the outputs (example .smt2 file)

	1) For example to get help on using the tool's CLI commands type the following:

		$ ./SaVerECS  --help

	2) To run the tool with the plant model as "benchmarks/thermostat/thermostat.ha" and controller program as "benchmarks/thermostat/thermostat.c" having the header file "thermostat.h" in the same "benchmarks/thermostat/", with the sampling time of the controller as "0.2", for the time-horizon of "3" units, type the command as given below. The output is generated in the file "test.smt2" using the -o flag. The number of depth for unrolling is specified by -u and -l, where u is the upper-bound and l the lower-bound. The flag -m is to supply a maximum bounds for all variables (both plant and controller) within which the variables always lies. The flag -d is used to input the sensing time. For simple goal/property to test use the --goal flag.

		$ ./SaVerECS -m 100 -t 0.2 -d 0.001 -u 10 -l 5 --time-horizon 3 --goal "x>=5 & y>=3" --plant-file "benchmarks/thermostat.ha" --controller-file "benchmarks/thermostat.c" -o test.smt2
		
	3) Else one can simply input all these values in configuration file as ` benchmarks/thermostat/thermostat.cfg ` and run the following to verify the goal property,
	
		$ ./SaVerECS -g "benchmarks/thermostat/thermostat.cfg" --plant-file "benchmarks/thermostat/thermostat.ha" --controller-file "benchmarks/thermostat/thermostat.c" -o benchmarks/thermostat/outputs/thermostat




How to Run:
================
To execute the project with a sample test inputs, 
- Add a folder in benchmarks directory with model name. Keep All the input files with same name inside that folder (they will have different extensions),
- Add the system name in '.run' file as the value of ` $system` variable e.g.
		
		$ system = thermostat
		
- enter the `src/` directory and type the below command in the terminal:
		
		$ cd src
		$ ./run

   where the script file 'run' includes the commands, details of which are explained as part of **CLI** section.
   
- output files:
 	>	
	
		.log files:	with execution time logs,
	
		.smt2 files:	containing tool generated smt formula in smt-lib 2.0 format,
		
 		.json files:	to visualize counter examples (instructions given in .log file)
		


*Note*:
================
To visualize the output counter example trace follow the on-screen instructions i.e. Copy the .json file content to `../ODE_Visualization/data.json` and run in terminal and view in `localhost:8000` url.
	
	$ ./run_websvr.sh 

Don't forget to run the following in the end.
	
	$ ./shut_websvr.sh
	

Benchmarks
=========================

Benchmarks Run using our Tool-chain is in [this repository](https://github.com/saverecs/Benchmark_SaverECS.git). You can also visit [this link](https://sites.google.com/view/benchmarkssafeemc/home) for details.

