An Example of SMT Encoding
==============================
Mathematical formulae to represent a closed-loop system into SMT encoding is shown below. 
The process of generating the SMT formula for a **DC Motor** system [(refer to this work)](https://dl.acm.org/doi/10.1145/2883817.2883819) is presented as an example. 
This DC Motor system has two *states (x)*, i.e. **angular velocity (angVal)** and **armature current (i)**, being controlled by a PI controller using a *control variable (u)* i.e. **voltage**. The PI controller's goal is to reduce error in plant's output, caused by **bounded additive noise (w)** introduced during run-time.

__Note__: The presented SMT-LIB2 format of the formula contains ** plant** and **Controller** flow during the first sampling instance. `gt` and `lt` are two variables denoting **global time and local time** of the system. The *first suffix i.e., 0* introduced in each variable, corresponds to the *first iteration/sampling period*. The second suffix i.e., *0 or t* corresponds to *flow of the variables*, e.g., `angVal_0_0` and `angVal_0_t` are values of angular velocity at the start of the zeroth iteration and the end of the zeroth iteration respectively.]

1.	The Plant model (using the HASLAC format) is:

		module dcmotor(angVal, i, voltage)

			output angVal, i;
			
			mode loc
				begin
					ddt angVal =  (-0.1/0.01)*angVal + (0.01/0.01)*i;
					ddt i = ((0.01/0.5)*angVal - (1/0.5)*i) + (voltage/0.5);
				end
			initial begin
				set begin
					mode == loc;
					angVal>=0;
					angVal<=0.2;
					i==0;
					voltage==1.0;
				end
			end
		endmodule
	
	
	
-	Initial range of state variables :
	> 	0=< angVal <=0.2,
		i=0,
		voltage= 1.0
	
	
	The corresponding SMT formula is (*Init()* in overall equation):
	
	![init](https://github.com/saverecs/SaverECS/blob/master/images/init.png?raw=true)

	This part of the formula in SMT-LIB2 format:

		(and 	(= lt_0_0  0) 
			(= gt_0_0  0) 
			(= voltage_0_0  1.0)
			(= i_0_0  0)
			(>= angVal  0) (<= angVal  1)
			(= mode_0   1) 
			(= state_error_i_previous_0  0)
		)

-	The flow equations are as follows:
		
	>	d/dt (angVal) =  (-0.1/0.01)*angVal + (0.01/0.01)*i,
		d/dt (i) = ((0.01/0.5)*angVal - (1/0.5)*i) + (voltage/0.5),	
	
	The formula that defines the flow equations in SMT-LIB2 format along with its encoding:
	
		//Definition in the ODE in SMT-LIB2 format
		(define-ode 
			flow_1 (
				(= d/dt[gt] 1) 
				(= d/dt[lt] 1) 
				(= d/dt[angVal] (+(*(/(- 0.1) 0.01) angVal)(*(/ 0.01 0.01) i))) 
				(= d/dt[i] (+(-(*(/ 0.01 0.5) angVal)(*(/ 1 0.5) i))(/ voltage 0.5))) 
				(= d/dt[voltage] 0)
			       )
		)
		//SMT encoding in SMT-LIB2 format
		(= [gt_0_t lt_0_t angVal_0_t i_0_t voltage_0_t ] (integral 0. time_0 [gt_0_0 lt_0_0 angVal_0_0 i_0_0 voltage_0_0 ] flow_1))  
		
				
**Note that the SMT-LIB2 format is a prefix notation.**
	
2.	The PI Controller as a C-Program.

-	The C-Program:  [dcmotor.c](https://github.com/saverecs/SaverECS/blob/master/src/benchmarks/dcmotor/dcmotor.c)

``` C - Program
#include "dcmotor.h"

#define SAT (20.0)
#define UPPER_SAT (SAT)
#define LOWER_SAT (-SAT)

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
  double pid_op = 0.0;
  double KP = 40.0;
  double KI = 1.0;

  double error, error_i;

  double y = input->state_angVal;
  // get the previous error
  double error_i_prev = input->state_error_i_previous;
  double ref = 1.0;

  // error computation is affected by bounded sensor noise
 // error = ref - (y + input->state_angVal);
 error = ref - y;

  // to illustrate: ei += e*Ki
  error_i = error * KI + error_i_prev;
  error_i_prev = error_i;

  pid_op = error * KP + error_i * KI;

  if(pid_op > UPPER_SAT)
    pid_op = UPPER_SAT;
  else if(pid_op < LOWER_SAT)
    pid_op = LOWER_SAT;
  else
    pid_op = pid_op;

  ret_val->next_voltage = pid_op;
  input->state_error_i_previous = error_i_prev;

  return (void*)0;
}
```


-	The Header Program:  [dcmotor.h](https://github.com/saverecs/SaverECS/blob/master/src/benchmarks/dcmotor/dcmotor.h)

```C
// ***** The Header Program:  dcmotor.h *****
typedef struct{
    double next_voltage;
}RETURN_VAL;

typedef struct{
    double state_angVal;
    double state_error_i_previous;
}INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);

// ***** End of The Header Program: dcmotor.h *****
```

	
- 	The SMT formula generated from the PI controller of DC motor in SMT-LIB2 format for `k=0` is the following (in prefix format). We perform this conversion of the C-program into SMT encoding by using the Clang/LLVM library. Therefore, we see some extra variables introduced by the library to formulate an equivalent SSA of the input C-program.
	
		(ite (< (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) -20 )
			(= .add3_0 -20 )
			(= .add3_0 (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) ) 
		) 
		(ite (> (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) 20 ) 
			(= pid_op.0_0 20 )
			(= pid_op.0_0 .add3_0 )
		)
		(= next_voltage_1 pid_op.0_0 ) 
		(= state_error_i_previous_1 (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) 

3.	The Configuration file  :

		max-value = "1000"
		minmax-bounds = "i:[0,2] & angval:[1,30]"
		sampling-time = 0.02
		release-time = 0
		sensing-time = 0
		Noise-params = "angVal:[0.02,1]=>[0.1,0.5]"
		time-horizon = 3
		upper-bound = 50
		lower-bound = 1
		goal ="i<=1.2 & i>=1.0 & angVal>=10 & angVal<=11"


- 	The unsafe region for the system (and corresponding SMT formula) is:
	>
		(1.0<=i<=1.2) & (11=>angVal>=10)

	This part of the formula in SMT-LIB2 format is: 
		
		(and 	(>= i  1.0) 
			(<= i  1.2) 
			(>= angVal  10) (<= angVal  11)
		)

-	The Noise Parameters:
	>
		0.08<=environmental disturbance on output  angVal (w)<=0.1
	
	The corresponding SMT formula of system flow with noise, for `k-th` sampling instance considering the `sampling period=0.02` is:
	
	![flow](https://github.com/saverecs/SaverECS/blob/master/images/flow.png?raw=true)
	
	The SMT-LIB2 version of the formula for `k=0`:
		
		(assert (and 	(= lt_0_0  0) 
				(= gt_0_0  0) 
				(= voltage_0_0  1.0)
				(= i_0_0  0)
				(>= angVal  0) (<= angVal  1)
				(= mode_0   1) 
				(= state_error_i_previous_0  0)
				
				(= lt_0_t (+ lt_0_0 (* 1 0))) (= gt_0_t (+ gt_0_0 (* 1 0))) (= voltage_0_t (+ voltage_0_0 (* 0 0)))
				
				(= [gt_0_t lt_0_t angVal_0_t i_0_t voltage_0_t ] (integral 0. time_0 [gt_0_0 lt_0_0 angVal_0_0 i_0_0 voltage_0_0 ] flow_1))
				(= angVal_1_0 (+ angVal_0_t Noise_angVal_0 ) )
				(= i_1_0 i_0_t)
				(= state_angVal_0 angVal_0_t )
				
				(ite (< (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) -20 )
					(= .add3_0 -20 )
					(= .add3_0 (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) ) 
				) 
				(ite (> (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) 20 ) 
					(= pid_op.0_0 20 )
					(= pid_op.0_0 .add3_0 )
				)
				(= next_voltage_1 pid_op.0_0 ) 
				(= state_error_i_previous_1 (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) )
			)
		)
	
4.	For a verification bound` N=50  `the final SMT formula becomes:

	![overall](https://github.com/saverecs/SaverECS/blob/master/images/whole.png?raw=true)
	

- 	The overall SMT-LIB2 version of the dcmotor for 1st iteration can be found in this file [dcmotor_1.smt2](https://github.com/saverecs/SaverECS/blob/master/src/benchmarks/dcmotor/outputs-2020-05-15T180821/dcmotor_1.smt2):

		(set-logic QF_NRA_ODE)
		(declare-fun angVal () Real [-10000, 10000])
		(declare-fun i () Real [-10000, 10000])
		(declare-fun voltage () Real [-10000, 10000])
		(declare-fun lt () Real [0.000000, 0.02])
		(declare-fun gt () Real [0.000000, 3])
		(declare-fun .add3_0 () Real [-10000, 10000] )
		(declare-fun pid_op.0_0 () Real [-10000, 10000] )
		(declare-fun state_angVal_0 () Real [-10000, 10000] )
		(declare-fun state_error_i_previous_0 () Real [-10000, 10000] )
		(declare-fun next_voltage_0 () Real [-10000, 10000] )
		(declare-fun angVal_0_0 () Real [-10000, 10000])
		(declare-fun angVal_0_t () Real [-10000, 10000])
		(declare-fun i_0_0 () Real [-10000, 10000])
		(declare-fun i_0_t () Real [-10000, 10000])
		(declare-fun voltage_0_0 () Real [-10000, 10000])
		(declare-fun voltage_0_t () Real [-10000, 10000])
		(declare-fun lt_0_0 () Real [0.000000, 0.02])
		(declare-fun lt_0_t () Real [0.000000, 0.02])
		(declare-fun gt_0_0 () Real [0.000000, 3])
		(declare-fun gt_0_t () Real [0.000000, 3])
		(declare-fun time_0 () Real [0.000000, 0])
		(declare-fun mode_0 () Real [1.000000, 1.000000])
		(declare-fun .add3_1 () Real [-10000, 10000] )
		(declare-fun pid_op.0_1 () Real [-10000, 10000] )
		(declare-fun state_angVal_1 () Real [-10000, 10000] )
		(declare-fun state_error_i_previous_1 () Real [-10000, 10000] )
		(declare-fun next_voltage_1 () Real [-10000, 10000] )
		(declare-fun angVal_1_0 () Real [-10000, 10000])
		(declare-fun angVal_1_t () Real [-10000, 10000])
		(declare-fun i_1_0 () Real [-10000, 10000])
		(declare-fun i_1_t () Real [-10000, 10000])
		(declare-fun voltage_1_0 () Real [-10000, 10000])
		(declare-fun voltage_1_t () Real [-10000, 10000])
		(declare-fun lt_1_0 () Real [0.000000, 0.02])
		(declare-fun lt_1_t () Real [0.000000, 0.02])
		(declare-fun gt_1_0 () Real [0.000000, 3])
		(declare-fun gt_1_t () Real [0.000000, 3])
		(declare-fun time_1 () Real [0.000000, 0.02])
		(declare-fun mode_1 () Real [1.000000, 1.000000])
		(declare-fun Noise_angVal_0 () Real [0.1, 0.5])
		(define-ode flow_1 ((= d/dt[gt] 1) (= d/dt[lt] 1) (= d/dt[angVal] (+(*(/(- 0.1) 0.01) angVal)(*(/ 0.01 0.01) i))) (= d/dt[i] (+(-(*(/ 0.01 0.5) angVal)(*(/ 1 0.5) i))(/ voltage 0.5))) (= d/dt[voltage] 0)))
		(assert (and (= lt_0_0 0) (= gt_0_0 0) (= voltage_0_0 1.0 )(= i_0_0 0 )(= angVal_0_0 0 )(= mode_0 1) (= state_error_i_previous_0 0 )  
		 (= lt_0_t (+ lt_0_0 (* 1 0))) (= gt_0_t (+ gt_0_0 (* 1 0))) (= voltage_0_t (+ voltage_0_0 (* 0 0))) 
		 (= [gt_0_t lt_0_t angVal_0_t i_0_t voltage_0_t ] (integral 0. time_0 [gt_0_0 lt_0_0 angVal_0_0 i_0_0 voltage_0_0 ] flow_1))  
		 (= mode_1 1) (= lt_0_t 0) (= gt_1_0 gt_0_t) (= lt_1_0 0)  
		 (= angVal_1_0 (+ angVal_0_t Noise_angVal_0 ) )(= i_1_0 i_0_t)(= state_angVal_0 angVal_0_t )  
		 (ite (< (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) -20 ) (= .add3_0 -20 )(= .add3_0 (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) ) ) 
		(ite (> (+ (* (- 1 state_angVal_0 ) 40 ) (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) 20 ) (= pid_op.0_0 20 )(= pid_op.0_0 .add3_0 ) ) 
		(= next_voltage_1 pid_op.0_0 ) 
		(= state_error_i_previous_1 (+ (- 1 state_angVal_0 ) state_error_i_previous_0 ) ) 

		 (= next_voltage_1 voltage_1_0 )  
		 (= lt_1_t (+ lt_1_0 (* 1 time_1 ))) (= gt_1_t (+ gt_1_0 (* 1 time_1 ))) (= voltage_1_t (+ voltage_1_0 (* 0 time_1 ))) 
		 (= [gt_1_t lt_1_t angVal_1_t i_1_t voltage_1_t ] (integral 0. time_1 [gt_1_0 lt_1_0 angVal_1_0 i_1_0 voltage_1_0 ] flow_1))  
		 (forall_t 1 [0 time_1] (<= lt_1_t 0.02))   
		 (<= lt_1_t 0.02) (<= lt_1_0 0.02) (= mode_1 1)  
		 (> gt_1_t 0.8  ) ))
		 (check-sat)
		(exit)



5. 	This SMT constraint is input to the [dReal SMT solver](https://github.com/dreal/dreal3), which eventually solves the ODEs. dReal SMT solver uses [CAPD DynSys library](http://capd.sourceforge.net/capdDynSys/docs/html/index.html) to solve the ODEs over Reals.