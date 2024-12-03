/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pwm_test.h
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

#ifndef pwm_test_h_
#define pwm_test_h_
#ifndef pwm_test_COMMON_INCLUDES_
#define pwm_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_ServoWriteRead.h"
#endif                                 /* pwm_test_COMMON_INCLUDES_ */

#include "pwm_test_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Output;                       /* '<S2>/Output' */
} B_pwm_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_inter_T obj; /* '<Root>/Standard Servo Write' */
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
  uint8_T Output_DSTATE;               /* '<S3>/Output' */
} DW_pwm_test_T;

/* Parameters (default storage) */
struct P_pwm_test_T_ {
  real_T RepeatingSequenceStair_OutValue[12];
                              /* Mask Parameter: RepeatingSequenceStair_OutValue
                               * Referenced by: '<S2>/Vector'
                               */
  real_T RepeatingSequence_rep_seq_y[2];
                                  /* Mask Parameter: RepeatingSequence_rep_seq_y
                                   * Referenced by: '<S1>/Look-Up Table1'
                                   */
  uint8_T WrapToZero_Threshold;        /* Mask Parameter: WrapToZero_Threshold
                                        * Referenced by: '<S5>/FixPt Switch'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 90
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;     /* Computed Parameter: PulseGenerator_Period
                                     * Referenced by: '<Root>/Pulse Generator'
                                     */
  real_T PulseGenerator_Duty;         /* Computed Parameter: PulseGenerator_Duty
                                       * Referenced by: '<Root>/Pulse Generator'
                                       */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T Constant_Value;               /* Expression: period
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T LookUpTable1_bp01Data[2];     /* Expression: rep_seq_t - min(rep_seq_t)
                                        * Referenced by: '<S1>/Look-Up Table1'
                                        */
  real_T Constant_Value_c;             /* Expression: 90
                                        * Referenced by: '<Root>/Constant'
                                        */
  uint8_T Constant_Value_cf;           /* Computed Parameter: Constant_Value_cf
                                        * Referenced by: '<S5>/Constant'
                                        */
  uint8_T Output_InitialCondition;/* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S3>/Output'
                                   */
  uint8_T ManualSwitch_CurrentSetting;
                              /* Computed Parameter: ManualSwitch_CurrentSetting
                               * Referenced by: '<Root>/Manual Switch'
                               */
  uint8_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S4>/FixPt Constant'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM_pwm_test_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTick2;
    struct {
      uint16_T TID[3];
    } TaskCounters;

    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_pwm_test_T pwm_test_P;

/* Block signals (default storage) */
extern B_pwm_test_T pwm_test_B;

/* Block states (default storage) */
extern DW_pwm_test_T pwm_test_DW;

/* Model entry point functions */
extern void pwm_test_initialize(void);
extern void pwm_test_step(void);
extern void pwm_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pwm_test_T *const pwm_test_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S1>/Output' : Eliminate redundant signal conversion block
 * Block '<S2>/Out' : Eliminate redundant signal conversion block
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pwm_test'
 * '<S1>'   : 'pwm_test/Repeating Sequence'
 * '<S2>'   : 'pwm_test/Repeating Sequence Stair'
 * '<S3>'   : 'pwm_test/Repeating Sequence Stair/LimitedCounter'
 * '<S4>'   : 'pwm_test/Repeating Sequence Stair/LimitedCounter/Increment Real World'
 * '<S5>'   : 'pwm_test/Repeating Sequence Stair/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* pwm_test_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
