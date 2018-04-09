#include <Encoder.h>

#define DIR_PIN 8
#define PWM_PIN 9

#define INT_PIN_1 2
#define INT_PIN_2 3

#define PPR 240.0
#define SAMPLES_PER_MEASURE 20.0

#define CONTINUOUS 0
#define LIMITED 1

int currentPWM = 0;
float measuredSpeed = 0;    // measured from encoder ticks

float currentPosition= 0;     // measured from encoder ticks
float relativePosition = 0;   // conditioned to range [ -180 : 180 ]
float lastPosition = 0;       // delayed measure

Encoder myEnc(2, 3);

long lastTic;
long timeNow;
float sampleTime = 50;

int samplesCounter = 0;
boolean state = false;

void setup() {
  Serial.begin(38400);
  
  pinMode(DIR_PIN,OUTPUT);
  pinMode(PWM_PIN,OUTPUT);
  delay(10);
  lastTic = millis();
}

void loop(){

  if(Serial.available() > 0 ){
    Serial.read();
    digitalWrite(DIR_PIN, 1- digitalRead(DIR_PIN));
    currentPWM = 0;
    analogWrite(PWM_PIN, 0);
    myEnc.write(0);
    delay(2000);
  }
  
  timeNow = millis();
  if((timeNow - lastTic >= sampleTime) && (currentPWM < 255)){
    
    /* Measurements */
    measurePosition();
    measuredSpeed += measureSpeed();
    samplesCounter ++;
    
    if(samplesCounter == SAMPLES_PER_MEASURE ){
      if(digitalRead(DIR_PIN))
        Serial.print(currentPWM * 12.0 / 255.0);
      else
        Serial.print(-currentPWM * 12.0 / 255.0);
      Serial.print("\t");
      Serial.println(measuredSpeed*60/(2*PI*SAMPLES_PER_MEASURE));
      samplesCounter = 0;
      measuredSpeed = 0;
      currentPWM ++;
      analogWrite(PWM_PIN, currentPWM);
    }
    lastTic = timeNow;
  }

  
}

