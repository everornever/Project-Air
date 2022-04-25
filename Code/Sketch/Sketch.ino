/*
	Project Airsensor

	This Sketch programms the Arduino to read the data of each sensor
  an displays it on the OLED Display

	The circuit:
	* Temperatur & humidity sensor on digital pin 3
	* Dust sensor on digital pin 7
  * Air quality sensor on analog pin 0
  * display on I2C. pin

	Created 11.02.2022
	By Leon Kling

*/

#include <Arduino.h>
#include "DHT.h"
#include <U8x8lib.h>
#include "Air_Quality_Sensor.h"
#include "Dust_Sensor.h"

#define DHTTYPE DHT11  // DHT 11 is the type of temp. sensor)
#define DHTPIN 3       // Temp. sensor pin

DustSensor dustsensor(7);   // The dust sensor object
AirQualitySensor airsensor(A0);                                                                      // The air sensor object
DHT tempSensor(DHTPIN, DHTTYPE);                                                                     // The temp sensor object
U8X8_SSD1306_128X64_NONAME_SW_I2C display(/* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);  // The display object


void setup(void) {

  Serial.begin(9600);
  while (!Serial);

  Serial.println("Waiting sensor to init...");
  delay(20000);

  if (airsensor.init()) {
    Serial.println("Sensor ready.");
  } else {
    Serial.println("Sensor ERROR!");
  }

  tempSensor.begin();

  display.setBusClock(100000);  // to limit the I2C bus clock
  display.begin();
  display.setFlipMode(1);  // displays supports a 180-degree rotation of the internal frame buffer
  
}

void loop(void) {

  display.setFont(u8x8_font_torussansbold8_r);  // Define a u8x8 font for the glyph and string drawing functions.
  display.setCursor(0, 0);                      // Define the cursor for the print function. x, y: Column/row position for the cursor of the print function.

  readTempSensor();
  readAirQuality();
  readDustSensor();

  display.refreshDisplay();
  delay(200);
}

void readTempSensor(void) {

  float temp, humi;  // Temp sensor values

  temp = tempSensor.readTemperature();
  display.print(temp);
  display.print("C");

  Serial.print(temp);
  Serial.print("\n");

  humi = tempSensor.readHumidity();
  display.setCursor(10, 0);
  display.print(humi);
  display.print("%");

  Serial.print(humi);
  Serial.print("\n");
}

void readDustSensor(void) {

  if (dustsensor.starttime == 0){
    dustsensor.starttime = millis();
  }

  // Dust sensor value
  int current_dust = -1;

  current_dust = dustsensor.getValue();
  if (current_dust >= 0)  // if a valid data returned.
  {
    if (current_dust == 0) {
      display.setCursor(0, 3);
      display.print("*** No Dust ****");  //16
    } else if (current_dust == 1) {
      display.setCursor(0, 3);
      display.print("** Light Dust **");
      display.print("!High pollution!");
    } else if (current_dust == 2) {
      display.setCursor(0, 3);
      display.print("**** Dusty! ****");
    } else if (current_dust == 3) {
      display.setCursor(0, 3);
      display.print("**** Smoke! ****");
    }
    else if (current_dust == 4) {
      display.setCursor(0, 3);
      display.print("* No Value Yet *");
    }
  }

}

void readAirQuality(void) {

  // Air quality sensor value
  int current_quality = -1;

    // Serial.print("Sensor value: ");
    // Serial.println(airsensor.getValue());

    // if (current_quality == AirQualitySensor::FORCE_SIGNAL) {
    //     Serial.println("High pollution! Force signal active.");
    // } else if (current_quality == AirQualitySensor::HIGH_POLLUTION) {
    //     Serial.println("High pollution!");
    // } else if (current_quality == AirQualitySensor::LOW_POLLUTION) {
    //     Serial.println("Low pollution!");
    // } else if (current_quality == AirQualitySensor::FRESH_AIR) {
    //     Serial.println("Fresh air.");
    // }

    // delay(1000);

  current_quality = airsensor.slope();
  if (current_quality >= 0)  // if a valid data returned.
  {
    if (current_quality == 0) {
      Serial.println("High pollution! Force signal active");
      Serial.print("\n");
      display.setCursor(0, 5);
      display.print("+++ WARNING! +++");
    } else if (current_quality == 1) {
      Serial.println("High pollution!");
      Serial.print("\n");
      display.setCursor(0, 5);
      display.print("!High pollution!");
    } else if (current_quality == 2) {
      Serial.println("Low pollution!");
      Serial.print("\n");
      display.setCursor(0, 5);
      display.print(" Low pollution  ");
    } else if (current_quality == 3) {
      Serial.println("Fresh air");
      Serial.print("\n");
      display.setCursor(0, 5);
      display.print("   Fresh air!   ");
    }
  }
}
