#include <Zumo32U4.h>
#include <Wire.h>
#ifndef __FILTER_H
#define __FILTER_H


class Filter
{ 
  
    public:
    uint8_t val;
    float accOffset;
    float accTemp = 0;
    float predAngle;
    float lastAngle = 0;
    float lastBias = 0;

    int counter = 0;
    bool startVal = 0;
    float k = 0.5;
    float epsilon = 0.01;


   Filter();
    void Init();
    bool calcAngle(float& obsAngle, float& fusAngle, float& bias);

};

#endif
