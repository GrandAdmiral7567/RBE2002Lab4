#include <Zumo32U4.h>
#include <Wire.h>
#ifndef __FILTER_H
#define __FILTER_H

class dataFilter
{ //for variables and functions
  public:


    dataFilter();
    void Init();
    bool calcAngle(float& gBias, float& obsAngle, 
    float& fusAngle)
    
    ;
    uint8_t val;

    float predAngle;
    float prevAngle = 0;
    float prevBias = 0;
    float accumOffset;
    float accumTemp = 0;
    
    float k = 0.7;
    float eps = .05;

    
    int counter = 0;
    bool startVal = 0;

};

#endif
