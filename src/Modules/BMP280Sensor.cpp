#include "Modules/BMP280Sensor.h"

// Source utilisation et méthodes librairie: adafruit/Adafruit BMP280 Library@^2.6.8 depuis "PIO Home/Librairies". 

BMP280Sensor::BMP280Sensor()
  : m_temperature(DEFAULT_ZERO_F),
    m_altitude(DEFAULT_ZERO_F),                             
    m_presure(DEFAULT_ZERO_F),   
    m_maxTemperature(DEFAULT_ZERO_F),
    m_maxAltitude(DEFAULT_ZERO_F),
    m_maxPresure(DEFAULT_ZERO_F),
    m_groundAltitude(DEFAULT_ZERO_F),
    m_lastReadTime(DEFAULT_ZERO),                           
    m_interval(INTERVAL_500) {                              // Pour l'instant, lecture au 1/2 seconde.  
        Wire.begin();        
        if (!this->m_BMP280.begin(BMP_ADD)) {               // Simple vérification affiché dans le port série. A servi à détecter que je n'avais pas un BME mais un BMP.
            Serial.println("Incapable de démarrer le capteur BME280. Vérifiez l'adresse et le câblage.");
            while(true);                                    // La librairie de ADXL345 m'a montré que c'est une manière de créer une boucle infinie pour arrèter le programme sans cracher mais boucle dans le vide à l'infinie.
        } else {                                            // Sera utilisé dans tout les objets, à la mise en route de l'esp32 avant le lancement. On pourrait utiliser le LCD. Si problème d'un objet, on connaitra la cause.
                                                            // Au lieu d'un Serial.println() dans le port série COM4, puisque l'esp32 ne sera pas physiquement connecté, on aurait les infos sur le LCD placé sur la fusée. 
            Serial.println("Capteur BME280 initialisé avec succès.");
        }    
        setGroundAltitude();                      
    }               

void BMP280Sensor::setMembresValues() {
    this->m_temperature = this->m_BMP280.readTemperature();
    this->m_altitude = this->m_BMP280.readAltitude(SEALEVELPRESSURE_HPA) - this->m_groundAltitude;
    this->m_presure = this->m_BMP280.readPressure() / KILOPASCAL;        // divisé par 1000.0f pour passer de Pascal (Pa) à Kilo Pascal (kPa)
}
void BMP280Sensor::setMaxValues() {
    if (this->m_temperature > this->m_maxTemperature) {
        this->m_maxTemperature = this->m_temperature;
    }
    if (this->m_altitude > this->m_maxAltitude) {
        this->m_maxAltitude = this->m_altitude;
    }
    if (this->m_presure > this->m_maxPresure) {
        this->m_maxPresure = this->m_presure;
    }
}
void BMP280Sensor::setGroundAltitude() {
    this->m_groundAltitude = this->m_BMP280.readAltitude(SEALEVELPRESSURE_HPA);
}

// Si on utilise les string... exemple, affichage des données simples dans HASS
String BMP280Sensor::getTemperatureString() {
    return String("Température: ") + this->m_temperature + DEGRE;
}
String BMP280Sensor::getAltitudeString() {
    return String("Altitude: ") + this->m_altitude + METRE;
}
String BMP280Sensor::getPresureString() {
    return String("Pression: ") + this->m_presure + KPA;
}

// Si on utilise les float... exemple, pour calcules ou données pour un tableau. Pouraient être envoyées à un fichiers .csv 
float BMP280Sensor::getTemperaturefloat() {
    return this->m_temperature;
}
float BMP280Sensor::getAltitudefloat() {
    return this->m_altitude;
}
float BMP280Sensor::getPresurefloat() {
    return this->m_presure;
}

float BMP280Sensor::getMaxTemperature() {
    return this->m_maxTemperature;
}
float BMP280Sensor::getMaxAltitude() {
    return this->m_maxAltitude;
}
float BMP280Sensor::getMaxPresure() {
    return this->m_maxPresure;
}

void BMP280Sensor::tick() {
    if (this->m_lastReadTime + this->m_interval < millis()) {           // Pour l'instant, lecture au 1/2 seconde
        this->m_lastReadTime = millis();
        setMembresValues();
        setMaxValues();
    }
}
