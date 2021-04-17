/* Zutshi et al., “Symbolic-numeric reachability analysis of 
 * closed-loopcontrol software,” in HSCC, ACM, 2016
 * https://dl.acm.org/doi/10.1145/2883817.2883819
 */
#include "dcmotor.h"

#define SAT (20.0)
#define UPPER_SAT (SAT)
#define LOWER_SAT (-SAT)

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
    double pid_op = 0.0;
    double KP     = 40.0;
    double KI     = 1.0;

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

    if (pid_op > UPPER_SAT) {
    
        pid_op = UPPER_SAT;
    
    } else if (pid_op < LOWER_SAT) {
    
        pid_op = LOWER_SAT;
    
    } else {
        
        pid_op = pid_op;
    
    }

    ret_val->next_voltage = pid_op;
    input->state_error_i_previous = error_i_prev;

    return (void*)0;
}
