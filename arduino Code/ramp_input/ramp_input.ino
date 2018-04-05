#include <Encoder.h>

#define DIR_PIN 8
#define PWM_PIN 9

#define INT_PIN_1 2
#define INT_PIN_2 3

#define PPR 240.0

#define CONTINUOUS 0
#define LIMITED 1

char serialCommand = 'S';

Encoder myEnc(2, 3);

void setup() {
  Serial.begin(38400);
  
  pinMode(DIR_PIN,OUTPUT);
  pinMode(PWM_PIN,OUTPUT);
  delay(10);
  lastTic = millis();
}

void loop(){
  if(Serial.available() > 0){
    serialCommand = Serial.read();
    handleCommand();
    sampleCounter = 0;
  }

  if( serialDisplayMode == CONTINUOUS || sampleCounter < numberOfSamples){
    timeNow = millis();
    if(timeNow - lastTic >= sampleTime ){
      sampleCounter ++;
      
      /* Measurements */
      measurePosition();
      measureSpeed();
      
      /* Controller Type*/
      if(controlMode == SPEED_CONTROL){
        controlSpeed();
      }else if(controlMode == POSITION_CONTROL){
        controlPosition(false);
      }else{
        controlPosition(true);
      }
  
      Serial.print(measuredSpeed*60/(2*PI));
      Serial.print("\t");
      Serial.print(relativePosition*180/PI);
      Serial.println();
      
      lastTic = timeNow;
    }
  }
  
}

