#include "filter.h"
LSM303 compass;
L3G gyro;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;




Filter::Filter() {

}


bool Filter::calcAngle(float& obsAngle, float& fusAngle, float& gBias){ 
  val = compass.readReg(LSM303::STATUS_A);


  if(val & 0x0F){
    //read the gyro
    gyro.read(); 
    //read the compass
    compass.readAcc();
    
    //calculate angles and bias
    //correct for bias to predict angle
    predAngle = lastAngle + ((gyro.g.y * .00875)-lastBias)*(0.1); 
    //get observation value
    obsAngle = (atan2((compass.a.x),(compass.a.z)) * (180.0/3.14259)) - accOffset; 
    //correct
    fusAngle = (1-k)*(obsAngle) + k*predAngle;
    //calculatae new bias
    gBias = epsilon*(obsAngle - predAngle)+ lastBias;


    //accumulate offset and get average
    
     if(buttonB.isPressed()){ 
      //start with values at 0
      startVal = true;
      accOffset = 0;
      accTemp = 0;
     }

     //we need to get average
     if(startVal){
      if(counter < 250){
        //add observed angle and update counter
        accTemp += obsAngle;
        counter++;
      }else{
        //reset counter
        counter = 0;
        //divide by number of values to get average
        accOffset = accTemp/250.0;
        //average ahs been gotten, no need to repeat yet
        startVal = false;
      }
     }

     
     if(buttonC.isPressed()) accOffset = 0; // for recalibration
    
    //update variables
    lastAngle = fusAngle;
    lastBias = gBias;
    return 1;
  }else return 0;
}


void Filter::Init(void) {
  Wire.begin();

  if (!gyro.init())
  {
    while (1)
    {
      Serial.println(F("ERROR"));
      delay(100);
    }
  }

  gyro.enableDefault();
  
  if (!compass.init())
  {
    while (1)
    {
      Serial.println(F("ERROR"));
      delay(100);
    }
  }

  compass.enableDefault();



  gyro.writeReg(L3G::CTRL1, 0xBF);
  //10 ms intervals
  compass.writeReg(LSM303::CTRL1, 0x67);
}
