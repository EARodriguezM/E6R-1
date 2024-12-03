/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pwm_test.c
 *
 * Code generated for Simulink model 'pwm_test'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Dec  2 09:06:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pwm_test.h"
#include "pwm_test_private.h"
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <float.h>

/* Block signals (default storage) */
B_pwm_test_T pwm_test_B;

/* Block states (default storage) */
DW_pwm_test_T pwm_test_DW;

/* Real-time model */
static RT_MODEL_pwm_test_T pwm_test_M_;
RT_MODEL_pwm_test_T *const pwm_test_M = &pwm_test_M_;
static void rate_scheduler(void);
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (pwm_test_M->Timing.TaskCounters.TID[2])++;
  if ((pwm_test_M->Timing.TaskCounters.TID[2]) > 999) {/* Sample time: [1.0s, 0.0s] */
    pwm_test_M->Timing.TaskCounters.TID[2] = 0;
  }
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      q = ceil(u1);
    } else {
      q = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != q)) {
      q = fabs(u0 / u1);
      if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

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
void pwm_test_step(void)
{
  real_T PulseGenerator;
  uint8_T tmp_0;
  boolean_T tmp;
  tmp = (pwm_test_M->Timing.TaskCounters.TID[2] == 0);
  if (tmp) {
    /* MultiPortSwitch: '<S2>/Output' incorporates:
     *  Constant: '<S2>/Vector'
     *  UnitDelay: '<S3>/Output'
     */
    pwm_test_B.Output =
      pwm_test_P.RepeatingSequenceStair_OutValue[pwm_test_DW.Output_DSTATE];
  }

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  PulseGenerator = (pwm_test_DW.clockTickCounter <
                    pwm_test_P.PulseGenerator_Duty) &&
    (pwm_test_DW.clockTickCounter >= 0) ? pwm_test_P.PulseGenerator_Amp : 0.0;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  if (pwm_test_DW.clockTickCounter >= pwm_test_P.PulseGenerator_Period - 1.0) {
    pwm_test_DW.clockTickCounter = 0;
  } else {
    pwm_test_DW.clockTickCounter++;
  }

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (pwm_test_P.ManualSwitch_CurrentSetting == 1) {
    PulseGenerator = pwm_test_P.Constant_Value_c;
  } else {
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Clock: '<S1>/Clock'
     *  Constant: '<Root>/Constant1'
     *  Constant: '<S1>/Constant'
     *  Lookup_n-D: '<S1>/Look-Up Table1'
     *  Math: '<S1>/Math Function'
     */
    switch ((int32_T)pwm_test_P.Constant1_Value) {
     case 1:
      break;

     case 2:
      PulseGenerator = pwm_test_B.Output;
      break;

     default:
      PulseGenerator = look1_binlxpw(rt_remd_snf(pwm_test_M->Timing.t[0],
        pwm_test_P.Constant_Value), pwm_test_P.LookUpTable1_bp01Data,
        pwm_test_P.RepeatingSequence_rep_seq_y, 1U);
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch' */
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* MATLABSystem: '<Root>/Standard Servo Write' */
  if (PulseGenerator < 0.0) {
    tmp_0 = 0U;
  } else if (PulseGenerator > 180.0) {
    tmp_0 = 180U;
  } else {
    PulseGenerator = rt_roundd_snf(PulseGenerator);
    if (PulseGenerator < 256.0) {
      tmp_0 = (uint8_T)PulseGenerator;
    } else {
      tmp_0 = MAX_uint8_T;
    }
  }

  MW_servoWrite(0, tmp_0);

  /* End of MATLABSystem: '<Root>/Standard Servo Write' */
  if (tmp) {
    /* Sum: '<S4>/FixPt Sum1' incorporates:
     *  Constant: '<S4>/FixPt Constant'
     *  UnitDelay: '<S3>/Output'
     */
    pwm_test_DW.Output_DSTATE += pwm_test_P.FixPtConstant_Value;

    /* Switch: '<S5>/FixPt Switch' */
    if (pwm_test_DW.Output_DSTATE > pwm_test_P.WrapToZero_Threshold) {
      /* Sum: '<S4>/FixPt Sum1' incorporates:
       *  Constant: '<S5>/Constant'
       */
      pwm_test_DW.Output_DSTATE = pwm_test_P.Constant_Value_cf;
    }

    /* End of Switch: '<S5>/FixPt Switch' */
  }

  {                                    /* Sample time: [0.001s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      ((pwm_test_M->Timing.clockTick1) * 0.001);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1, extmodeTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  if (pwm_test_M->Timing.TaskCounters.TID[2] == 0) {/* Sample time: [1.0s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      ((pwm_test_M->Timing.clockTick2) * 1.0);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(2, extmodeTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  pwm_test_M->Timing.t[0] =
    ((time_T)(++pwm_test_M->Timing.clockTick0)) * pwm_test_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    pwm_test_M->Timing.clockTick1++;
  }

  if (pwm_test_M->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [1.0s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 1.0, which is the step size
     * of the task. Size of "clockTick2" ensures timer will not overflow during the
     * application lifespan selected.
     */
    pwm_test_M->Timing.clockTick2++;
  }

  rate_scheduler();
}

/* Model initialize function */
void pwm_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&pwm_test_M->solverInfo,
                          &pwm_test_M->Timing.simTimeStep);
    rtsiSetTPtr(&pwm_test_M->solverInfo, &rtmGetTPtr(pwm_test_M));
    rtsiSetStepSizePtr(&pwm_test_M->solverInfo, &pwm_test_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&pwm_test_M->solverInfo, (&rtmGetErrorStatus
      (pwm_test_M)));
    rtsiSetRTModelPtr(&pwm_test_M->solverInfo, pwm_test_M);
  }

  rtsiSetSimTimeStep(&pwm_test_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&pwm_test_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&pwm_test_M->solverInfo, false);
  rtsiSetSolverName(&pwm_test_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(pwm_test_M, &pwm_test_M->Timing.tArray[0]);
  rtmSetTFinal(pwm_test_M, -1);
  pwm_test_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  pwm_test_M->Sizes.checksums[0] = (2594470970U);
  pwm_test_M->Sizes.checksums[1] = (2906666724U);
  pwm_test_M->Sizes.checksums[2] = (3688324002U);
  pwm_test_M->Sizes.checksums[3] = (25365744U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    pwm_test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(pwm_test_M->extModeInfo,
      &pwm_test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(pwm_test_M->extModeInfo, pwm_test_M->Sizes.checksums);
    rteiSetTPtr(pwm_test_M->extModeInfo, rtmGetTPtr(pwm_test_M));
  }

  /* InitializeConditions for Sum: '<S4>/FixPt Sum1' incorporates:
   *  UnitDelay: '<S3>/Output'
   */
  pwm_test_DW.Output_DSTATE = pwm_test_P.Output_InitialCondition;

  /* Start for MATLABSystem: '<Root>/Standard Servo Write' */
  pwm_test_DW.obj.matlabCodegenIsDeleted = false;
  pwm_test_DW.obj.isInitialized = 1;
  MW_servoAttach(0, 33);
  pwm_test_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void pwm_test_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Standard Servo Write' */
  if (!pwm_test_DW.obj.matlabCodegenIsDeleted) {
    pwm_test_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Standard Servo Write' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
