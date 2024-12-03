/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stdio.h>
#include <stdlib.h>
#include "Firmware.h"
#include "Firmware_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "MW_ArduinoHWInit.h"
#include "mw_freertos.h"
#define UNUSED(x)                      x = x
#define NAMELEN                        16

/* Function prototype declaration*/
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
SemaphoreHandle_t stopSem;
SemaphoreHandle_t baserateTaskSem;
mw_thread_t schedulerThread;
mw_thread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(Firmware_M) == (NULL));
  while (runModel) {
    mw_osSemaphoreWaitEver(&baserateTaskSem);
    Firmware_step();

    /* Get model outputs here */
    stopRequested = !((rtmGetErrorStatus(Firmware_M) == (NULL)));
    runModel = !stopRequested;
  }

  runModel = 0;
  terminateTask(arg);
  mw_osThreadExit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(Firmware_M, "stopping the model");
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    runModel = 0;
  }

  /* Terminate model */
  Firmware_terminate();
  mw_osSemaphoreRelease(&stopSem);
  return NULL;
}

int app_main(int argc, char **argv)
{
  init();
  MW_Arduino_Init();
  rtmSetErrorStatus(Firmware_M, 0);

  /* Initialize model */
  Firmware_initialize();

  /* Call RTOS Initialization function */
  mw_RTOSInit(0.001, 0);

  /* Wait for stop semaphore */
  mw_osSemaphoreWaitEver(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(mw_osSemaphoreDelete(&timerTaskSem[i]), 0,
                   "mw_osSemaphoreDelete");
    }
  }

#endif

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
