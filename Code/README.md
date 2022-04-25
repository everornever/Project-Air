# Software

Die Software wurde mit der [Arduino IDE](https://www.arduino.cc/en/software) geschrieben. Hier wurde die neue 2.0 Beta Version verwendet.

## 1. Bibliotheken

Folgende Bibliotheken weden verwendet:

- **Arduino:** Für die Basic Arduino SDK
- **DHT:** Für den Temperatur Sensor
- **U8X8:** Für den OLED Display

Für den Dust Sensor und den Air Quality Sensor wurden eigene Bibliotheken geschrieben.

## 2. Pins

Folgende Pins sind belegt:
- I2C - Display
- A0 - Air Quality Sensor
- D7 - Dust Sensor
- D3 - Temp Sensor

## 3. Anforderungen:

- Die AirQuality Bibliothek soll die 0 - 748 voltage in 4 Messewerte aufteilen
- Die Dust Sensor Bibliothek soll anhand einer vorgegebenen Rechnung die aktuellen Messwert ausgeben
- Die Dust Sensor Bibliothek soll dies erst nach 30 Sekunden Messzeit tun
- Es soll mithilfe einer Bibliothek die Temperatur und Luftfeutigkeit gemessen werden
- Es soll mithilfe einer Bibliothek alle Messwerte auf dem Display angezeigt werden


