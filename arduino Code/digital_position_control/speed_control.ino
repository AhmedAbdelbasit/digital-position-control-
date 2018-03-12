 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */
  
void measureSpeed(){
  
  float newSpeed = ((currentPosition - lastPosition))* 1000.0 /(sampleTime);
  measuredSpeed = (1-feedbackDampFactor) * measuredSpeed + feedbackDampFactor * newSpeed;
}

void controlSpeed(){
  speedError = speedRef - measuredSpeed;
  float errorDiff = (speedError - lastSpeedError)*1000.0/sampleTime;
  lastSpeedError = speedError;
  speedErrorSum += speedError * sampleTime/1000.0;
  
  outputPWM = kp_s * speedError + ki_s * speedErrorSum + kd_s * errorDiff;

  if( outputPWM > 0 ){
    digitalWrite(8, HIGH);
  }else{
    outputPWM *= -1;
    digitalWrite(8, LOW);
  }
  
  if( outputPWM > 255){
    outputPWM = 255;
  }

  if(outputPWM > MIN_PWM)
    analogWrite(PWM_PIN, outputPWM);
  else
    analogWrite(PWM_PIN, 0);
}

