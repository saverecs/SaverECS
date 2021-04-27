#include "PIDSSsteeringControl.h"

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
    double pid_op = 0;
    double K      = 29.4889;
    double Nbar   = 1;
    double KP     = 84101;
    double KI     = 40;
    double ref    = 10;
    
    double error, error_i;

    double v        = input->state_v;
    double z        = input->state_z;
    error           = ref - v;
    pid_op          = error * KP + z * KI;
    ret_val->next_u = - pid_op + Nbar*ref;

    return (void*)0;
}
