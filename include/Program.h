#pragma once
#include <Arduino.h>
#include "Sensors/BMP280Sensor.h"

class Program {
private:
    BMP280Sensor* m_BMP280;
    String m_temperature;
    String m_altitude;
    String m_presure;
    //String m_humidity;

    String m_lastTemperature;
    String m_lastAltitude;
    String m_lastPresure;
    //String m_lastHumidity;

    uint64_t m_lastReadTime;
    uint16_t m_interval;

    void getBMP280Values();
public:
    Program();
    void printValues();
    void loop();
};