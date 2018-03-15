/* Encoder Library, for measuring quadrature encoded signals
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 * Copyright (c) 2011,2013 PJRC.COM, LLC - Paul Stoffregen <paul@pjrc.com>
 *
 * Version 1.2 - fix -2 bug in C-only code
 * Version 1.1 - expand to support boards with up to 60 interrupts
 * Version 1.0 - initial release
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
  
#include <Encoder.h>

 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */
  
#define DIR_PIN 8
#define PWM_PIN 9

#define INT_PIN_1 2
#define INT_PIN_2 3

#define MIN_PWM 25
#define PPR 240.0
#define SPEED_CONTROL 1
#define POSITION_CONTROL 2
#define POS_CONTROL_VEL_FEEDBACK 3

#define CONTINUOUS 0
#define LIMITED 1

char serialCommand = 'S';

Encoder myEnc(2, 3);

// Speed Control variables
float speedRef =0;          // rad/s
float measuredSpeed = 0;    // measured from encoder ticks
float speedError = 0;       // reference - measured
float lastSpeedError = 0;   // delayed measure for derivative calculation
float speedErrorSum = 0;    // intgeration of error signal

// Position Control variables
float positionRef = 0;        // in radian
float currentPosition= 0;     // measured from encoder ticks
float relativePosition = 0;   // conditioned to range [ -180 : 180 ]
float lastPosition = 0;       // delayed measure
float positionError = 0;      // reference - measured
float lastPositionError = 0;  // delayed measure for derivative calculation
float positionErrorSum = 0;   // intgeration of error signal

// Manipulated signal
float outputPWM = 0;
float lastOutputPWM = 0;

// Timing parameters
long lastTic;
long timeNow;
float sampleTime = 10;

// optimum 1.5 1 0 2

// PID Parameters POSITION
float kp_p= 90;
float ki_p= 38;
float kd_p= 0.04;
float Kspeed = 0.2;
/* OPTIMAL
float kp_p= 90;
float ki_p= 38;
float kd_p= 0.04;
float Kspeed = 0.2;
 */
 
float kp_s= 15;
float ki_s= 10;
float kd_s= 0;
/* OPTIMAL
 * float kp_s= 15;
float ki_s= 10;
float kd_s= 0;
 */
 
// MOTOR LPF
float forwardDampFactor = 0.01;

// Feedback LPF
float feedbackDampFactor = 0.025;

//byte controlMode = POSITION_CONTROL;
byte controlMode = SPEED_CONTROL;
//byte controlMode = POS_CONTROL_VEL_FEEDBACK;

// Serial monitor display
byte serialDisplayMode = CONTINUOUS;
int numberOfSamples  = 500;
int sampleCounter = 0;

void setup() {
  Serial.begin(38400);
  
  pinMode(DIR_PIN,OUTPUT);
  pinMode(PWM_PIN,OUTPUT);
  delay(10);
  lastTic = millis();
}
