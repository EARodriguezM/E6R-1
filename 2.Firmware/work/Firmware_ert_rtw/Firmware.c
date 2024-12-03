/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Firmware.c
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

#include "Firmware.h"
#include "Firmware_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block states (default storage) */
DW_Firmware_T Firmware_DW;

/* Real-time model */
static RT_MODEL_Firmware_T Firmware_M_;
RT_MODEL_Firmware_T *const Firmware_M = &Firmware_M_;
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void Firmware_step(void)
{
  real_T rtb_PulseGenerator;
  uint8_T tmp;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (Firmware_DW.clockTickCounter <
                        Firmware_P.PulseGenerator_Duty) &&
    (Firmware_DW.clockTickCounter >= 0) ? Firmware_P.PulseGenerator_Amp : 0.0;
  if (Firmware_DW.clockTickCounter >= Firmware_P.PulseGenerator_Period - 1.0) {
    Firmware_DW.clockTickCounter = 0;
  } else {
    Firmware_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* MATLABSystem: '<Root>/Digital Output' */
  rtb_PulseGenerator = rt_roundd_snf(rtb_PulseGenerator);
  if (rtb_PulseGenerator < 256.0) {
    if (rtb_PulseGenerator >= 0.0) {
      tmp = (uint8_T)rtb_PulseGenerator;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(26, tmp);

  /* End of MATLABSystem: '<Root>/Digital Output' */
}

/* Model initialize function */
void Firmware_initialize(void)
{
  /* Start for MATLABSystem: '<Root>/Digital Output' */
  Firmware_DW.obj.matlabCodegenIsDeleted = false;
  Firmware_DW.obj.isInitialized = 1;
  digitalIOSetup(26, 1);
  Firmware_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void Firmware_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Digital Output' */
  if (!Firmware_DW.obj.matlabCodegenIsDeleted) {
    Firmware_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Output' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
