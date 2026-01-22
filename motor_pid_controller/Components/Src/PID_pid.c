/* MATLAB GENERATED SOURCE FILE: PID_pid.c */
#include "PID_pid.h"
// Controller gains
uint32_t PID_GAINS_UINT[3] = 
{
  #include "PID_gains.csv"
};
// Controller instance
arm_pid_instance_f32 PID;
