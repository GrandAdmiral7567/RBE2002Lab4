#include "dataFilter.h"
LSM303 compass;
L3G gyro;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
dataFilter::dataFilter() {

}





void dataFilter::Init(void) {
  Wire.begin();


    if (!gyro.init())
  {
    while (1)
    {
      Serial.println("ERROR NO GYRO");
      delay(1000);
    }
  }

  gyro.enableDefault();



  
  if (!compass.init())
  {
    while (1)
    {
      Serial.println("ERROR NO COMPASS");
      delay(1000);
    }
  }

  compass.enableDefault();


  compass.writeReg(LSM303::CTRL1, 0x67);
  gyro.writeReg(L3G::CTRL1, 0xBF);
}







bool dataFilter::calcAngle(float& gBias, float& obsAngle, 
    float& fusAngle){ 
  val = compass.readReg(LSM303::STATUS_A);
  
  if(val & 0x0F){
    compass.readAcc();
    gyro.read(); 
    //calculate predicted angle
    predAngle = (.01)*((gyro.g.y * .00875) - prevBias)+prevAngle;

    //calculate observed angle
    obsAngle = (atan2((compass.a.x),(compass.a.z))*(180.0/3.14259)) - accumOffset;

       //calculate bias from gyro
    gBias = eps*(obsAngle - predAngle)+prevBias; 

    //calculate fused angle
    fusAngle = (1-k)*obsAngle+k*predAngle;




     if(startVal){
      if(counter < 250){
        accumTemp += obsAngle;
        counter++;
      }else{
        accumOffset = accumTemp/250.0;
        counter = 0;
        startVal = false;
      }
     }
    
    prevBias = gBias;
    prevAngle = fusAngle;
    return 1;
  }
  else return 0;
}



