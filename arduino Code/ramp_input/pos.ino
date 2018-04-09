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
