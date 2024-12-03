/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pwm_test_data.c
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

/* Block parameters (default storage) */
P_pwm_test_T pwm_test_P = {
  /* Mask Parameter: RepeatingSequenceStair_OutValue
   * Referenced by: '<S2>/Vector'
   */
  { 0.0, 30.0, 60.0, 90.0, 120.0, 150.0, 180.0, 150.0, 120.0, 90.0, 60.0, 30.0 },

  /* Mask Parameter: RepeatingSequence_rep_seq_y
   * Referenced by: '<S1>/Look-Up Table1'
   */
  { 0.0, 180.0 },

  /* Mask Parameter: WrapToZero_Threshold
   * Referenced by: '<S5>/FixPt Switch'
   */
  11U,

  /* Expression: 2
   * Referenced by: '<Root>/Constant1'
   */
  2.0,

  /* Expression: 90
   * Referenced by: '<Root>/Pulse Generator'
   */
  90.0,

  /* Computed Parameter: PulseGenerator_Period
   * Referenced by: '<Root>/Pulse Generator'
   */
  1000.0,

  /* Computed Parameter: PulseGenerator_Duty
   * Referenced by: '<Root>/Pulse Generator'
   */
  500.0,

  /* Expression: 0
   * Referenced by: '<Root>/Pulse Generator'
   */
  0.0,

  /* Expression: period
   * Referenced by: '<S1>/Constant'
   */
  10.0,

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S1>/Look-Up Table1'
   */
  { 0.0, 10.0 },

  /* Expression: 90
   * Referenced by: '<Root>/Constant'
   */
  90.0,

  /* Computed Parameter: Constant_Value_cf
   * Referenced by: '<S5>/Constant'
   */
  0U,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S3>/Output'
   */
  0U,

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  1U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S4>/FixPt Constant'
   */
  1U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
