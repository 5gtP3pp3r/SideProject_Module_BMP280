#pragma once

#define SERIAL_SPEED 115200
#define BUTTON1_PIN 26
#define BUTTON2_PIN 25

#define EMPTY ""
#define DEFAULT_ZERO 0
#define DEFAULT_ZERO_F 0.0f
#define INTERVAL_5 5000                 // 5 secondes
#define INTERVAL_4 4000
#define INTERVAL_3 3000
#define INTERVAL_2 2000
#define INTERVAL_1 1000
#define INTERVAL_500 500                // 500 millisecondes
#define INTERVAL_400 400
#define INTERVAL_300 300
#define INTERVAL_200 200
#define INTERVAL_100 100
#define INTERVAL_50 50                  // 50 millisecondes
#define INTERVAL_40 40
#define INTERVAL_30 30
#define INTERVAL_20 20
#define INTERVAL_10 10

// BMP280
#define BMP_ADD 0x76                    // SD0 sur GND. Si VCC: 0x77
#define SEALEVELPRESSURE_HPA (1013.25)
#define DEGRE "°c"
#define METRE "m"
#define KPA "kPa"
#define PERCENT "%" 
#define KILOPASCAL 1000.0f

// ADXL345
#define ADXL_ADD 0x53                   // SD0 sur GND. SI sur VCC: 0x1D
#define MS2 "m/s²"                      // Accélération en mètre par seconde au carré. La gravité est une accélération constante de 9.81m/s² soit 1G.
#define G_CONST 9.81f                   // Constante De la gravité.

// WIFI D1 Mini Data loggar shield
#define SD_CS 5                         // Première fois avec un protocole SPI! Pin CS à définir selon dispo
#define SD_SCK 18
#define SD_MISO 19
#define SD_MOSI  23
#define CSV ".csv"

#define JSON_FILE_PATH "/config.json"
