/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Firmware_types.h
 *
 * Code generated for Simulink model 'Firmware'.
 *
 * Model version                  : 1.24
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Nov 28 15:01:03 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Firmware_types_h_
#define Firmware_types_h_
#include "rtwtypes.h"
#ifndef struct_tag_um27AmhtbslH2i5VSgy0RG
#define struct_tag_um27AmhtbslH2i5VSgy0RG

struct tag_um27AmhtbslH2i5VSgy0RG
{
  int32_T __dummy;
};

#endif                                 /* struct_tag_um27AmhtbslH2i5VSgy0RG */

#ifndef typedef_b_arduinodriver_ArduinoDigita_T
#define typedef_b_arduinodriver_ArduinoDigita_T

typedef struct tag_um27AmhtbslH2i5VSgy0RG b_arduinodriver_ArduinoDigita_T;

#endif                             /* typedef_b_arduinodriver_ArduinoDigita_T */

#ifndef struct_tag_lLXm9RMdC1wJGOFiPwVXeD
#define struct_tag_lLXm9RMdC1wJGOFiPwVXeD

struct tag_lLXm9RMdC1wJGOFiPwVXeD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  b_arduinodriver_ArduinoDigita_T DigitalIODriverObj;
};

#endif                                 /* struct_tag_lLXm9RMdC1wJGOFiPwVXeD */

#ifndef typedef_codertarget_arduinobase_block_T
#define typedef_codertarget_arduinobase_block_T

typedef struct tag_lLXm9RMdC1wJGOFiPwVXeD codertarget_arduinobase_block_T;

#endif                             /* typedef_codertarget_arduinobase_block_T */

/* Parameters (default storage) */
typedef struct P_Firmware_T_ P_Firmware_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Firmware_T RT_MODEL_Firmware_T;

#endif                                 /* Firmware_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
