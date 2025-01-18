#include "Modules/BMP280Sensor.h"

// Source utilisation et méthodes librairie: adafruit/Adafruit BMP280 Library@^2.6.8 depuis "PIO Home/Librairies". 

BMP280Sensor::BMP280Sensor()
  : m_temperature(DEFAULT_ZERO_F),
    m_altitude(DEFAULT_ZERO_F),                             // Pour afficher un altitude réel depuis le sol du lancement, devra créer une classe pour le clacul.  Prendre l'altitude
    m_presure(DEFAULT_ZERO_F),                              // stable avant le lancement, la conserver dans une données membre et relancer l'altitude moins la donnée enregistrée. 
    m_lastReadTime(DEFAULT_ZERO),                           // Comme ça l'altitude depuis le sol sera visible. Ou bien dans une donnée membre à l'intérieur de cette classe directement.
    m_interval(INTERVAL_500) {                              // Pour l'instant, lecture au 1/2 seconde.          
        if (!m_BMP280.begin(BMP_ADD)) {                     // Simple vérification affiché dans le port série. A servi à détecter que je n'avais pas un BME mais un BMP.
            Serial.println("Incapable de démarrer le capteur BME280. Vérifiez l'adresse et le câblage.");
            while(true);                                    // La librairie de ADXL345 m'a montré que c'est une manière de créer une boucle infinie pour arrèter le programme sans cracher mais boucle dans le vide à l'infinie.
        } else {                                            // Sera utilisé dans tout les objets, à la mise en route de l'esp32 avant le lancement. On pourrait utiliser le LCD. Si problème d'un objet, on connaitra la cause.
                                                            // Au lieu d'un Serial.println() dans le port série COM4, puisque l'esp32 ne sera pas physiquement connecté, on aurait les infos sur le LCD placé sur la fusée. 
            Serial.println("Capteur BME280 initialisé avec succès.");
        }                          
    }               

void BMP280Sensor::setMembresValues() {
    this->m_temperature = this->m_BMP280.readTemperature();
    this->m_altitude = this->m_BMP280.readAltitude(SEALEVELPRESSURE_HPA);
    this->m_presure = this->m_BMP280.readPressure() / KILOPASCAL;        // divisé par 1000.0f pour passer de Pascal (Pa) à Kilo Pascal (kPa)
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
float BMP280Sensor::getTemperaturefloat(){
    return this->m_temperature;
}
float BMP280Sensor::getAltitudefloat(){
    return this->m_altitude;
}
float BMP280Sensor::getPresurefloat(){
    return this->m_presure;
}

void BMP280Sensor::tick() {
    if (this->m_lastReadTime + this->m_interval < millis()) {           // Pour l'instant, lecture au 1/2 seconde
        this->m_lastReadTime = millis();
        setMembresValues();
    }
}
