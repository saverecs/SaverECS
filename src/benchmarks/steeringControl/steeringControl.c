#include "steeringControl.h"

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
    double pid_op = 0;
    double K      = 29.4889;
    double Nbar   = 425690 / 425690;
    double KP     = 56260;
    double KI     = 40;
    double ref    = 10;
    
    double error, error_i;

    double v = input->state_v;

    // get the previous error
    double prev_error_i = input->state_prev_error_i;

    ret_val->next_u = -KP * (v - ref) + Nbar * ref;

    return (void*)0;
}
