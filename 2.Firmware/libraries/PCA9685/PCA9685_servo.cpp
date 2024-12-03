#include "C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\PCA9685_servo.h"

#include "Arduino.h"
#include "Adafruit_PWMServoDriver.h"
#include "Wire.h"


// boardAddress uint8 [1,1] Tunable
// pwmFrecuency single [1,1] Non tunable
// servoChannel uint8 [1,1] Non tunable
// servoMin uint16 [1,1] Non tunable
// servoMax uint16 [1,1] Non tunable

Adafruit_PWMServoDriver pca9685Obj;
uint16_T  servoMinGlobal;
uint16_T  servoMaxGlobal;
uint8_T  servoChannelGlobal;

float pwmFrecuencyGlobal;

void setupFunctionPCA9685_servo(uint8_T * boardAddress,int size_vector__1,float  pwmFrecuency,int size_vector__2,uint8_T  servoChannel,int size_vector__3,uint16_T  servoMin,int size_vector__4,uint16_T  servoMax,int size_vector__5){
    pca9685Obj = Adafruit_PWMServoDriver(servoChannel);
    // Initialize PCA9685
    pca9685Obj.begin();

    // Set PWM Frequency to tuned frecuency in Hz
    pca9685Obj.setPWMFreq(pwmFrecuency);

    pwmFrecuencyGlobal = pwmFrecuency;
    servoMinGlobal = servoMin;
    servoMaxGlobal = servoMax;
    servoChannelGlobal = servoChannel;

}

// currentAngle single [1,1]
// desireAngle single [1,1]

void stepFunctionPCA9685_servo(float * currentAngle,int size_vector_1,float desireAngle,int size_vector_a, uint8_T * boardAddress,int size_vector__1){
    desireAngle = abs(desireAngle - *currentAngle);

    int period;
    period = 1/pwmFrecuencyGlobal;

    int timePerStep;
    timePerStep = period/4096;

    uint16_T minClockCycles =  servoMinGlobal/timePerStep;
    uint16_T maxClockCycles =  servoMaxGlobal/timePerStep;

    int orientation;
    uint16_T pwm;

    if (*currentAngle <= desireAngle) {
        orientation = 1;
    }
    else {
        orientation = -1;
    }

    // Move servo servoChannel from currentAngle to desireAngle degrees
    for (float posDegrees = *currentAngle; posDegrees <= desireAngle; posDegrees = posDegrees + (1 * orientation)) {
        // Determine PWM pulse width
        pwm = map(posDegrees, 0, 180, minClockCycles, maxClockCycles);
        // Write to PCA9685
        pca9685Obj.setPWM(servoChannelGlobal, 0, pwm);
    }
    *currentAngle = desireAngle;
  
}