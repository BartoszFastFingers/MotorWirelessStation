/* MATLAB GENERATED  HEADER FILE: PID_pid.h */
#ifndef INC_PID_H_
#define INC_PID_H_

#include "arm_math.h"

// Controller gains
extern uint32_t PID_GAINS_UINT[3];
#define PID_KP  (((float32_t*)PID_GAINS_UINT)[0])
#define PID_KI  (((float32_t*)PID_GAINS_UINT)[1])
#define PID_KD  (((float32_t*)PID_GAINS_UINT)[2])
// Controller instance
extern arm_pid_instance_f32 PID;
#endif // INC_PID_H_
