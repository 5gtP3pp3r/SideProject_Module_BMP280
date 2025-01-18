#include "Sensors/BMP280Sensor.h"

BMP280Sensor::BMP280Sensor()
  : m_temperature(DEFAULT_ZERO_F),
    m_altitude(DEFAULT_ZERO_F),                             // Pour afficher un altitude réel depuis le sol du lancement, devra créer une classe pour le clacul. 
    m_presure(DEFAULT_ZERO_F),                              // Prendre l'altitude stable avant le lancement, le conserver dans une données membre et relancer 
    m_lastReadTime(DEFAULT_ZERO),                           // l'altitude moins la donnée enregistrée. Comme ça l'altitude depuis le sol sera visible. 
    m_interval(INTERVAL_500) {                              // Pour l'instant, lecture au 1/2 seconde.          
        if (!m_BMP280.begin(BMP_ADD)) {                     // Simple vérification affiché dans le port série. A servi à détecter que je n'avais pas un BME mais un BMP.
            Serial.println("Incapable de démarrer le capteur BME280. Vérifiez l'adresse et le câblage.");
        } else {
            Serial.println("Capteur BME280 initialisé avec succès.");
        }                          
    }               

void BMP280Sensor::setMembresValues() {
    this->m_temperature = m_BMP280.readTemperature();
    this->m_altitude = m_BMP280.readAltitude(SEALEVELPRESSURE_HPA);
    this->m_presure = m_BMP280.readPressure() / KILOPASCAL;        // divisé par 1000.0f pour passer de Pascal (Pa) à Kilo Pascal (kPa)
}

// Si on utilise les string... exemple, affichage des données simples dans HASS
String BMP280Sensor::getTemperatureString() {
    return String("Température: ") + m_temperature + DEGRE;
}
String BMP280Sensor::getAltitudeString() {
    return String("Altitude: ") + m_altitude + METRE;
}
String BMP280Sensor::getPresureString() {
    return String("Pression: ") + m_presure + KPA;
}

// Si on utilise les float... exemple, pour calcules ou données pour un tableau. Pouraient être envoyées à un fichiers .csv 
float BMP280Sensor::getTemperaturefloat(){
    return m_temperature;
}
float BMP280Sensor::getAltitudefloat(){
    return m_altitude;
}
float BMP280Sensor::getPresurefloat(){
    return m_presure;
}

void BMP280Sensor::tick() {
    if (m_lastReadTime + m_interval < millis()) {           // Pour l'instant, lecture au 1/2 seconde
        m_lastReadTime = millis();
        setMembresValues();
    }
}
