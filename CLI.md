Detailed Command Line Interface (CLI):

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

	1)  For example, to get help on using the tool's CLI commands, type the following:

		$ ./SaVerECS  --help

	2) To run the tool with the plant model as "benchmarks/thermostat/thermostat.ha" and controller program as "benchmarks/thermostat/thermostat.c" having the header file "thermostat.h" in the same "benchmarks/thermostat/," with the sampling time of the controller as "0.2", for the time-horizon of "3" units, type the command as given below. The output is generated in the file "test.smt2" using the -o flag. The number of depth for unrolling is specified by -u and -l, where u is the upper-bound and l the lower-bound. The flag -m is to supply a maximum bound for all variables (both plant and controller) within which the variables always lie. The flag -d is used to input the sensing time. For simple goal/property to test, use the --goal flag.

		$ ./SaVerECS -m 100 -t 0.2 -d 0.001 -u 10 -l 5 --time-horizon 3 --goal "x>=5 & y>=3" --plant-file "benchmarks/thermostat.ha" --controller-file "benchmarks/thermostat.c" -o test.smt2
		
	3) Else one can simply input all these values in configuration file as ` benchmarks/thermostat/thermostat.cfg ` and run the following to verify the goal property,
	
		$ ./SaVerECS -g "benchmarks/thermostat/thermostat.cfg" --plant-file "benchmarks/thermostat/thermostat.ha" --controller-file "benchmarks/thermostat/thermostat.c" -o benchmarks/thermostat/outputs/thermostat

