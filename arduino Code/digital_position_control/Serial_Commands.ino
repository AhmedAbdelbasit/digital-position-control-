 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */
  
void handleCommand(){
  switch (serialCommand){
    case 'P':
      controlMode = POSITION_CONTROL;
      myEnc.write(0);
      positionErrorSum = 0;
      lastPositionError = 0;
      Serial.println("Position Control Enabled");
      break;
    case 'V':
      controlMode = SPEED_CONTROL;
      measuredSpeed = 0;
      lastSpeedError = 0;
      speedErrorSum = 0;
      Serial.println("Speed Control Enabled");
      break;
    case 'F':
      myEnc.write(0);
      controlMode = POS_CONTROL_VEL_FEEDBACK;
      positionErrorSum = 0;
      Serial.println("Position With Velocity feedback");
      break;
    case 'S':
      while(!Serial.available()){}
      if(controlMode == SPEED_CONTROL){
        speedRef = Serial.parseInt()*2*PI/60.0;
        measuredSpeed = 0;
        lastSpeedError = 0;
        speedErrorSum = 0;
      }else{
        positionRef = Serial.parseInt()*PI/180;
        lastPositionError = 0;
        positionErrorSum = 0;
      }
      break;
    default :
      resetSpeed();
      resetPosition();
  }
}

void resetPosition(){
  positionRef = 0;
  currentPosition = 0;
  relativePosition = 0;
  lastPositionError = 0;
  positionErrorSum = 0;
  myEnc.write(0);
}

void resetSpeed(){
  speedRef = 0;
  lastSpeedError = 0;
  speedErrorSum = 0;
}

