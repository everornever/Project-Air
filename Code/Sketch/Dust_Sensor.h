#ifndef __DUST_SENSOR_H__
#define __DUST_SENSOR_H__

#include "Arduino.h"

class DustSensor {
  public:

    DustSensor(int pin);

    int getValue(void);

    static const int HIGH_Dust;
    static const int MID_Dust;
    static const int LIGHT_Dust;
    static const int LOW_Dust;
    static const int NO_VALUE;

    unsigned long starttime;

  protected:
    int  _pin;

    unsigned long duration;
    unsigned long sampletime_ms = 30000;  //sample 30s ;
    unsigned long lowpulseoccupancy = 0;

    float ratio = 0;
    float concentration = 0;

};

#endif // __DUST_SENSOR_H__