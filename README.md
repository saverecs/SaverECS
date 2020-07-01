
*****************************************************************************************************************************************************
*****************************************************************************************************************************************************
	Indian Institute of Technology Kharagpur, India,
	Formal Methods Lab,
	Project Title: "FMSAFE: A Networked Centre for Formal Methods in Validation and Certification Procedures for Safety Critical ICT Systems"

	Funded by IMPRINT, a MHRD supported Pan-IIT + IISc joint initiative for addressing major science and engineering challenges that are relevant in the national context.


	Copyright (c) 2018 Formal Methods Lab, Indian Institute of Technology Kharagpur, India.

	Tool Developer:

               Jay Thakkar, 
               Amit Gurung,
               Sunandan Adhikary,
               Antonio Bruto da Costa 

*****************************************************************************************************************************************************
*****************************************************************************************************************************************************


How to build: 
================
	To generate the executable, type the following command in the terminal:

		$ cd fmsafe/src
		$ ./compile-cpp

  If the source code is modified, or a new file.cpp is added, it must also be added in the compile-cpp file before executing it.

How to Run:
================
	To execute the project with a sample test inputs, type the below command in the terminal:

		$ ./run

   where the script file 'run' includes sample test cases commands. The details of the commands with examples are shown below.

Prerequisite (for running the tool):
================
	1) clang and llvm 
	$ sudo apt-get install clang
	$ sudo apt-get install llvm
	2) boost library for c++
	$ sudo apt-get install libboost-all-dev


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

	2) To run the tool with the plant model as "benchmarks/thermostat.ha" and controller program as "benchmarks/thermostat.c" having the header file "thermostat.h" in the same "benchmarks", with the sampling time of the controller as "0.2", for the time-horizon of "3" units, type the command as given below. The output is generated in the file "test.smt2" using the -o flag. The number of depth for unrolling is specified by -u and -l, where u is the upper-bound and l the lower-bound. The flag -m is to supply a maximum bounds for all variables (both plant and controller) within which the variables always lies. The flag -d is used to input the sensing time. For simple goal/property to test use the --goal flag.

		$ ./SaVerECS -m 100 -t 0.2 -d 0.001 -u 10 -l 5 --time-horizon 3 --goal "x>=5 & y>=3" --plant-file "benchmarks/thermostat.ha" --controller-file "benchmarks/thermostat.c" -o test.smt2



Note:
================
The files with the extensions .l and .y are the lex and yacc files. They are use to parse the input plant model file having the extension .ha (The language use to model the input plant is referred as HASLAC).
If the .l and .y (present in the project src folder) files are modified, then execute the script file "build" before execute the above commands.

Input Format:
================
The input format of the plant model is taken using the HASLAC specification (for the language HASLAC please refer to http://cse.iitkgp.ac.in/~bdcaa/ForFET/ref.pdf).
However, for the contorller program, we lay down the following program structure:
		
		1) The input and the output argument variables are declare in a structure within a header file (controller.h) which is included in the controller program (controller.c). The names of the structure should be INPUT_VAL and RETURN_VAL as shown below:

				typedef struct{
					datatype outputVarName;

				}RETURN_VAL;

				typedef struct{
					datatype plantVarName; //The value sensed from the plant (remember to follow the same naming convension in the plant model as well. In addition, we use the key word "state_" as a prefix before the sensed variables of the plant and prefix by the key word "next_" to the output variables that is returned from the controller program.)

					datatype otherControllerVarName;   

				}INPUT_VAL;

		2)	The header file (for eg controller.h) should also include the declaration of the controller function as shown below:

				datatype controller(INPUT_VAL* iv, RETURN_VAL* rv);	//here the return datatype can be void, e.t.c.
			Note that we assume all controller program begin with the function name as "controller()" just like a C/C++ program begin with the function main().


		3) We also assume that the definition of the function follows the following usual pattern as reflected below. Note that we pass the arguments as reference variables, so we do not use the return statement to return the paramter.

				
				#include "controller.h"	//contains the structure declaration as shown in 1) and 2) above.
				
				void controller(INPUT_VAL* input, RETURN_VAL* ret_val) {

					local varaible declaration 
					============================
						datatype v1,v2, ...., vn;
					
					retrieving values from the input varaibles onto the local variables
					====================================================================
					v1 = input->plantVarName;
					v2 = input->otherControllerVarName

					performing the logic of the controller program
					====================================================================
					actual calculation and taking logical decisions, etc

					....
					
					Finally, update the computed values to the output variable and changing the current state of the controller(input variables) in the data structures
					==============================================================================================================================================
					ret_val->outputVarName = vn;
					input->otherControllerVarName = vj;	//e.t.c.,

				}

##Benchmarks
=========================

Benchmarks Run using our Tool-chain is in [this repository](https://github.com/saverecs/Benchmark_SaverECS.git). You can also visit [this link](https://sites.google.com/view/benchmarkssafeemc/home) for details.

