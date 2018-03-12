 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */
  
void loop() {
  timeNow = millis();
  if(timeNow - lastTic >= sampleTime ){
    
    /* Measurements */
    measurePosition();
    measureSpeed();
    
    if(Serial.available() > 0){
      serialCommand = Serial.read();
      handleCommand();
    }
    
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
