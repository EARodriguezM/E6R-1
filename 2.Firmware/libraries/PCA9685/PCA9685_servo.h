/* Copyright 2023 The MathWorks, Inc. */
#ifndef EXAMPLE_H
#define EXAMPLE_H
#if !( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C" {
    #endif
    void stepFunctionPCA9685_servo(float * currentAngle,int size_vector_1,float desireAngle,int size_vector_a, uint8_T * boardAddress,int size_vector__1);
    void setupFunctionPCA9685_servo(uint8_T * boardAddress,int size_vector__1,float  pwmFrecuency,int size_vector__2,uint8_T  servoChannel,int size_vector__3,uint16_T  servoMin,int size_vector__4,uint16_T  servoMax,int size_vector__5);
    #ifdef __cplusplus
}
#endif
#else
#define loop(void) (0)
#define setup(void) (0)
#endif
#endif