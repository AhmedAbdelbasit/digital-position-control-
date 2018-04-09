 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */

  
float measureSpeed(){
  return ((currentPosition - lastPosition))* 1000.0 /(sampleTime);
}
