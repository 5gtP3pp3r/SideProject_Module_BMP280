#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "const.h"

#define BMP_ADD 0x76                    // SD0 sur GND. Si VCC: 0x77
#define SEALEVELPRESSURE_HPA (1013.25)
#define DEGRE "°c"
#define METRE "m"
#define KPA "kPa"
#define PERCENT "%" 
#define KILOPASCAL 1000.0f

// Le module que j'ai est un "semblant" de BMP280, il ne calcule que la température et la pression atmosphérique et peut donc aussi donner
// une approximation de l'altitude. Le module a besoin d'être connecté au pins SCL (clock) SDA (data) et SDO doit être connecté au GND
// pour obtenir l'adresse 0x76 ou VCC pour l'adresse 0x77. Bien sure les GND et VCC doivent être connectées pour son fonctionnement. 

class BMP280Sensor {
private:
    float m_temperature;
    float m_altitude;
    float m_presure;
    float m_maxTemperature;    
    float m_maxPresure;
    float m_maxAltitude;
    float m_groundAltitude;
    Adafruit_BMP280 m_BMP280;
    uint64_t m_lastReadTime;
    uint16_t m_interval;
    void setMembresValues();
    void setMaxValues();
    void setGroundAltitude();
public:
    BMP280Sensor();
    void tick();
    String getTemperatureString();
    String getAltitudeString();
    String getPresureString();
    float getTemperaturefloat();
    float getAltitudefloat();
    float getPresurefloat();
    float getMaxTemperature();
    float getMaxAltitude();
    float getMaxPresure();
};