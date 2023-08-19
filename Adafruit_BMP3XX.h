#ifndef ADAFRUIT_BMP3XX_H
#define ADAFRUIT_BMP3XX_H

#include "bmp3.h"
#ifdef USING_CSV

#include <CSVParser.h>
#define TEMPERATURE 0
#define PRESSURE 1

#endif

/*
temperature,
pressure
*/

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define BMP3XX_DEFAULT_ADDRESS (0x77) ///< The default I2C address
/*=========================================================================*/
#define BMP3XX_DEFAULT_SPIFREQ (1000000) ///< The default SPI Clock speed

class Adafruit_BMP3XX{
public:
    Adafruit_BMP3XX(const char * filename = NULL);

    bool begin_I2C(uint8_t addr = BMP3XX_DEFAULT_ADDRESS/*,TwoWire *theWire = &Wire*/);
    bool begin_SPI(uint8_t cs_pin /*,SPIClass *theSPI = &SPI*/);
    bool begin_SPI(int8_t cs_pin, int8_t sck_pin, int8_t miso_pin,int8_t mosi_pin);
    uint8_t chipID(void);
    float readTemperature(void);
    float readPressure(void);
    float readAltitude(float seaLevel);

    bool setTemperatureOversampling(uint8_t os);
    bool setPressureOversampling(uint8_t os);
    bool setIIRFilterCoeff(uint8_t fs);
    bool setOutputDataRate(uint8_t odr);

    /// Perform a reading in blocking mode
    bool performReading(void);

    /// Temperature (Celsius) assigned after calling performReading()
    double temperature;
    /// Pressure (Pascals) assigned after calling performReading()
    double pressure;

    void increase_file_index();

private:

    bool _init(void);
    bool random_values;
    bool running;
    char *_filename;
    int file_index;
    #ifdef USING_CSV
    csv_parser::parser* sensor_data;
    #endif

};

#endif