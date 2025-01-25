#pragma once
#include <Arduino.h>
#include "Modules/BMP280Sensor.h"

class Program {
private:
    BMP280Sensor* m_BMP280;
    uint64_t m_lastReadTime;
    uint16_t m_interval;
public:
    Program();
    void printValues();
    void loop();
};