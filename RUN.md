How to Run:

To execute the project with sample test inputs, 
- Add a folder in the benchmarks directory with the model name. Keep All the input files with the same name inside that folder (they will have different extensions),
- Add the system name in '.run' file as the value of ` $system` variable e.g.
		
		$ system = thermostat
		
- enter the `src/` directory and type the below command in the terminal:
		
		$ cd src
		$ ./run

   Where the script file 'run' includes the commands, details of which are explained as part of **CLI** section.
   
- output files:
 	>	
	
		.log files:	with execution time logs,
	
		.smt2 files:	containing tool generated smt formula in smt-lib 2.0 format,
		
 		.json files:	to visualize counter examples (instructions given in .log file)