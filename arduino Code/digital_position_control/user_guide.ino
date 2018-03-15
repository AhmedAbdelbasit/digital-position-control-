 /*
  * This code and tutorials were written by Eng. Ahmed abdelbasit Mohamed 
  * email:  <- abdelbasit4@gmail.com ->
  * github: <- https://github.com/AhmedAbdelbasit ->
  */

/* ##################
 * ##  Tutorials:  ##
 * ##################
 * 
 * 1. The initial control mode is speed control with reference 0 rpm
 * 
 * 2. To change the control type:
 *        write 'V' in the serial monitor to select speed control
 *        write 'P' in the serial monitor to select position control
 *        write 'F' in the serial monitor to select position control with velocity feedback
 *        
 * 3. To set a new seferenc :
 *        write 'S' followed by the reference value as an integer value
 *        for example:
 *            in speed control when typing 'S50' the reference speed is set to 50 rpm
 *            in position control when typing 'S50' the reference position is set to 50 degrees
 *    
 * 4. To reset the reference values and eliminating controller bias you must write a sequnce
 *    of 'c' character in the serial monitor like 'ccccc'
 * 
 * 5. To toggle the display mode between continuous and limited number of samples you should type
 *    'D' in the serial monitor
 *    
 *    
 */
