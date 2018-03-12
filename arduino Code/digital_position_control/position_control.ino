 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */
  
void measurePosition(){
  lastPosition = currentPosition;
  currentPosition = myEnc.read()*1.5*PI/180;
  
  relativePosition += (currentPosition-lastPosition);
  if(relativePosition > PI)
    relativePosition -= 2*PI;
  else if(relativePosition < -PI)
    relativePosition += 2*PI;
}

void controlPosition(boolean mode){
  // Position Controller
  positionError = positionRef - currentPosition;
//  if(abs(positionError) <= 2)
//    positionError = 0;
  if(mode)
    positionError -= Kspeed*measuredSpeed ;
  positionErrorSum += positionError * sampleTime/1000.0;
  float errorDiff = (positionError - lastPositionError)*1000.0/sampleTime;

  outputPWM = kp_p*positionError + ki_p*positionErrorSum + kd_p*errorDiff;
  
  
  
  if( outputPWM > 0 ){
    digitalWrite(8, HIGH);
  }else{
    outputPWM *= -1;
    digitalWrite(8, LOW);
  }

  outputPWM = (1-forwardDampFactor) * lastOutputPWM + forwardDampFactor * outputPWM;
  
  if( outputPWM > 250)
    outputPWM = 250;

  if(outputPWM > MIN_PWM)
    analogWrite(PWM_PIN, outputPWM);
  else
    analogWrite(PWM_PIN, 0);
    
  lastOutputPWM = outputPWM;
}
