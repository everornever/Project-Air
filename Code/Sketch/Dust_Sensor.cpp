#include "Dust_Sensor.h"

const int DustSensor::NO_VALUE = 4;
const int DustSensor::HIGH_Dust = 3;
const int DustSensor::MID_Dust = 2;
const int DustSensor::LIGHT_Dust = 1;
const int DustSensor::LOW_Dust = 0;

DustSensor::DustSensor(int pin)
    : _pin(pin){
}

int DustSensor::getValue() {
  
  // Serial.print("StartTime:");
  // Serial.print(starttime);
  // Serial.print("Time:");
  // Serial.print(millis());
  // Serial.print("Diff:");
  // Serial.print(millis() - starttime);
  // Serial.print("\n");
  
  duration = pulseIn(_pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;  // represents the Low Pulse Occupancy Time(LPO Time) detected in given 30s. Its unit is microseconds.

  if ((millis() - starttime) > sampletime_ms)  //if the sampel time == 30s
  {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);                              // reflects on which level LPO Time takes up the whole sample time.
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;  // is a figure that has a physical meaning. It is calculated using the spec sheet curve
    Serial.println(concentration);

    if (concentration < 1.0) {
      lowpulseoccupancy = 0;
      starttime = millis();
      return DustSensor::LOW_Dust;
    }
    if (concentration > 1.0 && concentration < 20000) {
      lowpulseoccupancy = 0;
      starttime = millis();
      return DustSensor::LIGHT_Dust;
    }

    if (concentration > 20000 && concentration < 315000) {
      lowpulseoccupancy = 0;
      starttime = millis();
      return DustSensor::MID_Dust;
    }
    if (concentration > 315000) {
      lowpulseoccupancy = 0;
      starttime = millis();
      return DustSensor::HIGH_Dust;
    }

  } else {
    Serial.print("not 30s yet");
    Serial.print("\n");
    return DustSensor::NO_VALUE;
  }
}