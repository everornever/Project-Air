#ifndef __AIR_QUALITY_SENSOR_H__
#define __AIR_QUALITY_SENSOR_H__

#include "Arduino.h"

class AirQualitySensor {
  public:
    AirQualitySensor(int pin);

    bool init(void);
    int  slope(void);
    int  getValue(void);

    static const int FORCE_SIGNAL;
    static const int HIGH_POLLUTION;
    static const int LOW_POLLUTION;
    static const int FRESH_AIR;

  protected:
    int  _pin;

    int  _lastVoltage;
    int  _currentVoltage;
    int  _standardVoltage;

    long _voltageSum;
    int  _volSumCount;
    long _lastStdVolUpdated;

    void updateStandardVoltage(void);
};

#endif // __AIR_QUALITY_SENSOR_H__