/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Calibration.c
 *
 * Code generated for Simulink model 'Calibration'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Dec  2 15:33:45 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Calibration.h"
#include "Calibration_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block states (default storage) */
DW_Calibration_T Calibration_DW;

/* Real-time model */
static RT_MODEL_Calibration_T Calibration_M_;
RT_MODEL_Calibration_T *const Calibration_M = &Calibration_M_;
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
void Calibration_step(void)
{
  real_T tmp_0;
  uint8_T tmp;

  /* MATLABSystem: '<Root>/1' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Calibration_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (Calibration_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    tmp_0 = rt_roundd_snf(Calibration_P.Constant_Value);
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        tmp = (uint8_T)tmp_0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(0, tmp);

  /* End of MATLABSystem: '<Root>/1' */

  /* MATLABSystem: '<Root>/2' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Calibration_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (Calibration_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    tmp_0 = rt_roundd_snf(Calibration_P.Constant_Value);
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        tmp = (uint8_T)tmp_0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(1, tmp);

  /* End of MATLABSystem: '<Root>/2' */

  /* MATLABSystem: '<Root>/3' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Calibration_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (Calibration_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    tmp_0 = rt_roundd_snf(Calibration_P.Constant_Value);
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        tmp = (uint8_T)tmp_0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(2, tmp);

  /* End of MATLABSystem: '<Root>/3' */

  /* MATLABSystem: '<Root>/4' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Calibration_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (Calibration_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    tmp_0 = rt_roundd_snf(Calibration_P.Constant_Value);
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        tmp = (uint8_T)tmp_0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(3, tmp);

  /* End of MATLABSystem: '<Root>/4' */

  /* MATLABSystem: '<Root>/5' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Calibration_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (Calibration_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    tmp_0 = rt_roundd_snf(Calibration_P.Constant_Value);
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        tmp = (uint8_T)tmp_0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(4, tmp);

  /* End of MATLABSystem: '<Root>/5' */

  /* MATLABSystem: '<Root>/6' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Calibration_P.Constant_Value < 0.0) {
    tmp = 0U;
  } else if (Calibration_P.Constant_Value > 180.0) {
    tmp = 180U;
  } else {
    tmp_0 = rt_roundd_snf(Calibration_P.Constant_Value);
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        tmp = (uint8_T)tmp_0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }
  }

  MW_servoWrite(5, tmp);

  /* End of MATLABSystem: '<Root>/6' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  Calibration_M->Timing.taskTime0 =
    ((time_T)(++Calibration_M->Timing.clockTick0)) *
    Calibration_M->Timing.stepSize0;
}

/* Model initialize function */
void Calibration_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(Calibration_M, -1);
  Calibration_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  Calibration_M->Sizes.checksums[0] = (757580455U);
  Calibration_M->Sizes.checksums[1] = (669244709U);
  Calibration_M->Sizes.checksums[2] = (2378690988U);
  Calibration_M->Sizes.checksums[3] = (3250125359U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    Calibration_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Calibration_M->extModeInfo,
      &Calibration_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Calibration_M->extModeInfo,
                        Calibration_M->Sizes.checksums);
    rteiSetTPtr(Calibration_M->extModeInfo, rtmGetTPtr(Calibration_M));
  }

  /* Start for MATLABSystem: '<Root>/1' */
  Calibration_DW.obj_p.matlabCodegenIsDeleted = false;
  Calibration_DW.obj_p.isInitialized = 1;
  MW_servoAttach(0, 33);
  Calibration_DW.obj_p.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/2' */
  Calibration_DW.obj_l.matlabCodegenIsDeleted = false;
  Calibration_DW.obj_l.isInitialized = 1;
  MW_servoAttach(1, 25);
  Calibration_DW.obj_l.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/3' */
  Calibration_DW.obj_b.matlabCodegenIsDeleted = false;
  Calibration_DW.obj_b.isInitialized = 1;
  MW_servoAttach(2, 26);
  Calibration_DW.obj_b.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/4' */
  Calibration_DW.obj_jk.matlabCodegenIsDeleted = false;
  Calibration_DW.obj_jk.isInitialized = 1;
  MW_servoAttach(3, 27);
  Calibration_DW.obj_jk.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/5' */
  Calibration_DW.obj_j.matlabCodegenIsDeleted = false;
  Calibration_DW.obj_j.isInitialized = 1;
  MW_servoAttach(4, 14);
  Calibration_DW.obj_j.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/6' */
  Calibration_DW.obj.matlabCodegenIsDeleted = false;
  Calibration_DW.obj.isInitialized = 1;
  MW_servoAttach(5, 12);
  Calibration_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void Calibration_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/1' */
  if (!Calibration_DW.obj_p.matlabCodegenIsDeleted) {
    Calibration_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/1' */

  /* Terminate for MATLABSystem: '<Root>/2' */
  if (!Calibration_DW.obj_l.matlabCodegenIsDeleted) {
    Calibration_DW.obj_l.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/2' */

  /* Terminate for MATLABSystem: '<Root>/3' */
  if (!Calibration_DW.obj_b.matlabCodegenIsDeleted) {
    Calibration_DW.obj_b.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/3' */

  /* Terminate for MATLABSystem: '<Root>/4' */
  if (!Calibration_DW.obj_jk.matlabCodegenIsDeleted) {
    Calibration_DW.obj_jk.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/4' */

  /* Terminate for MATLABSystem: '<Root>/5' */
  if (!Calibration_DW.obj_j.matlabCodegenIsDeleted) {
    Calibration_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/5' */

  /* Terminate for MATLABSystem: '<Root>/6' */
  if (!Calibration_DW.obj.matlabCodegenIsDeleted) {
    Calibration_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/6' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
