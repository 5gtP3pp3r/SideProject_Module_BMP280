#include "Program.h"

Program::Program()
  : m_BMP280(nullptr),
    m_temperature(EMPTY),
    m_altitude(EMPTY),
    m_presure(EMPTY),

    m_lastTemperature(EMPTY),
    m_lastAltitude(EMPTY),
    m_lastPresure(EMPTY),
    
    m_lastReadTime(DEFAULT_ZERO),
    m_interval(INTERVAL_1) {                 // 1 sec
    this->m_BMP280 = new BMP280Sensor();
    Serial.begin(SERIAL_SPEED);
}

void Program::getBMP280Values() {
    m_temperature = m_BMP280->getTemperatureString();
    m_altitude = m_BMP280->getAltitudeString();
    m_presure = m_BMP280->getPresureString();
}

void Program::printValues() {
    if (m_temperature != m_lastTemperature ||
        m_altitude != m_lastAltitude ||
        m_presure != m_lastPresure) {
            Serial.println(m_temperature);
            Serial.println(m_altitude);
            Serial.println(m_presure);
            Serial.println(EMPTY);

            m_lastTemperature = m_temperature;
            m_lastAltitude = m_altitude;
            m_lastPresure = m_presure;
    }
}

void Program::loop() {
    m_BMP280->tick();
    getBMP280Values();
    if (m_lastReadTime + m_interval < millis()) {           // Pour l'instant, lecture au 1 seconde
        m_lastReadTime = millis();
        printValues();
    }
}