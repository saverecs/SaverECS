// Must include controller.h
#include "steeringControl.h"

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
  double pid_op = 0;
  double K= 29.4889;
  double Nbar=425690/425690;
  //double KP = 22040;
  //double KP = 84101;
  double KP = 56260;
  double KI = 40;
  double ref= 10;
  double error, error_i;

  double v = input->state_v;
// get the previous error
    double prev_error_i = input->state_prev_error_i;

// error computation is affected by bounded sensor noise
//    error = ref - v;
//    error_i = prev_error_i + error*KI;
// to illustrate: ei += e*Ki
//    prev_error_i = error_i;
//    pid_op = error * KP + error_i * KI;
//    pid_op = K*v+15001;
//    ret_val->next_u = -K*v+Nbar*ref;
    ret_val->next_u = -KP*(v-ref)+Nbar*ref;
//    input->state_prev_error_i = prev_error_i;

    return (void*)0;
}
