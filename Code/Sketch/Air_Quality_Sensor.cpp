#include "Air_Quality_Sensor.h"

const int AirQualitySensor::FORCE_SIGNAL   = 0;
const int AirQualitySensor::HIGH_POLLUTION = 1;
const int AirQualitySensor::LOW_POLLUTION  = 2;
const int AirQualitySensor::FRESH_AIR      = 3;

AirQualitySensor::AirQualitySensor(int pin)
    : _pin(pin), _voltageSum(0), _volSumCount(0) {
    // do nothing
}

bool AirQualitySensor::init(void) {
    int initVoltage = analogRead(_pin);

    if (10 < initVoltage && initVoltage < 798) {
        _currentVoltage = initVoltage;
        _lastVoltage = _currentVoltage;

        _standardVoltage = initVoltage;
        _lastStdVolUpdated = millis();

        return true;
    } else {
        return false;
    }
}

int AirQualitySensor::slope(void) {
    _lastVoltage = _currentVoltage;
    _currentVoltage = analogRead(_pin);

    _voltageSum += _currentVoltage;
    _volSumCount += 1;

    updateStandardVoltage();
    if (_currentVoltage - _lastVoltage > 400 || _currentVoltage > 700) {
        return AirQualitySensor::FORCE_SIGNAL;
    } else if ((_currentVoltage - _lastVoltage > 400 && _currentVoltage < 700)
               || _currentVoltage - _standardVoltage > 150) {
        return AirQualitySensor::HIGH_POLLUTION;
    } else if ((_currentVoltage - _lastVoltage > 200 && _currentVoltage < 700)
               || _currentVoltage - _standardVoltage > 50) {
        return AirQualitySensor::LOW_POLLUTION;
    } else {
        return AirQualitySensor::FRESH_AIR;
    }

    return -1;
}

int AirQualitySensor::getValue(void) {
    return _currentVoltage;
}

void AirQualitySensor::updateStandardVoltage(void) {
    if (millis() - _lastStdVolUpdated > 500000) {
        _standardVoltage = _voltageSum / _volSumCount;
        _lastStdVolUpdated = millis();

        _voltageSum = 0;
        _volSumCount = 0;
    }
}