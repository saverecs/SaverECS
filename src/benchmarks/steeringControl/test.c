// Must include controller.h
#include "steeringControl.h"
#include <stdio.h>

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
  double pid_op = 0.0;
  double KP = 800;
  double KI = 40;
  double ref= 10;
  double error, error_i;

    double v = input->state_v;
// get the previous error
    double prev_error_i = input->state_prev_error_i;

// error computation is affected by bounded sensor noise
    error = ref - v;
    error_i = prev_error_i + error*KI;
// to illustrate: ei += e*Ki
    prev_error_i = error_i;
    pid_op = error * KP + error_i * KI;
    ret_val->next_u = pid_op;
    input->state_prev_error_i = prev_error_i;
  
    return (void*)0;
}

void main(){
    int i=0;
    INPUT_VAL* ip; RETURN_VAL* op;
    double v= ip->state_v;
    double err_i=ip->state_prev_error_i;
    double u= op->next_u;
    v=0;
    err_i=10;
    u=500;
    while (i<100){
        ip->state_prev_error_i=err_i;
        ip->state_v=v;
        op->next_u=u;
        op=controller(ip,op);
        v=(-50/1000)*v + (1/1000)*u;
        printf("velocity: %f",v);
        printf("Force: %f",u);
    }
}