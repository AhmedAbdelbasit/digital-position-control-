 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */

void loop() {
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
