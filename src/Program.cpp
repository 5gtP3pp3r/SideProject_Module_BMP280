#include "Program.h"

Program::Program()
  : m_BMP280(nullptr),   
    m_lastReadTime(DEFAULT_ZERO),
    m_interval(INTERVAL_1) {                 // 1 sec
    this->m_BMP280 = new BMP280Sensor();
    Serial.begin(SERIAL_SPEED);
}

void Program::printValues() {
    Serial.print(this->m_BMP280->getTemperatureString());
    Serial.println("    Température max: " + String(this->m_BMP280->getMaxTemperature()) + DEGRE);
    Serial.print(this->m_BMP280->getAltitudeString());
    Serial.println("        Altitude max: " + String(this->m_BMP280->getMaxAltitude()) + "m");
    Serial.print(this->m_BMP280->getPresureString());
    Serial.println("    Pression max: " + String(this->m_BMP280->getMaxPresure()) + KPA);
    Serial.println(EMPTY);  
}

void Program::loop() {
    m_BMP280->tick();
    if (m_lastReadTime + m_interval < millis()) {   // Pour l'instant, lecture au 1 seconde
        m_lastReadTime = millis();
        printValues();
    }
}
