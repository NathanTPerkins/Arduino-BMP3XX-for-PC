#include "Adafruit_BMP3XX.h"
#include "Arduino.h"
#include <string.h>
#include <time.h>

Adafruit_BMP3XX::Adafruit_BMP3XX(const char *filename){
    if(filename == NULL){
        this->random_values = true;
        this->running = true;
        srand(time(NULL));
        return;
    }
    this->random_values = false;
    #ifdef USING_CSV
    this->_filename = new char[strlen(filename) + 1];
    strncpy(this->_filename, filename, strlen(filename) + 1);
    sensor_data = new csv_parser::arduino_parser(filename, 10);
    this->file_index = 0;
    #else
    srand(time(NULL));
    #endif

    this->running = true;

}

bool Adafruit_BMP3XX::begin_I2C(uint8_t addr){
    return true;
}

bool Adafruit_BMP3XX::begin_SPI(uint8_t cs_pin){
    return _init();
}

bool Adafruit_BMP3XX::begin_SPI(int8_t cs_pin, int8_t sck_pin, int8_t miso_pin, int8_t mosi_pin){
    return _init();
}

bool Adafruit_BMP3XX::_init(){
#ifdef BMP3XX_DEBUG
    Serial.print("Reset result: ");
    Serial.println(1);
#endif
#ifdef BMP3XX_DEBUG
    Serial.print("Init result: ");
    Serial.println(1);
#endif
#ifdef BMP3XX_DEBUG
    Serial.print("Valtrim result: ");
    Serial.println(1);
#endif
#ifdef BMP3XX_DEBUG
    Serial.print("T1 = ");
    Serial.println(1);
    Serial.print("T2 = ");
    Serial.println(1);
    Serial.print("T3 = ");
    Serial.println(1);
    Serial.print("P1 = ");
    Serial.println(1);
    Serial.print("P2 = ");
    Serial.println(1);
    Serial.print("P3 = ");
    Serial.println(1);
    Serial.print("P4 = ");
    Serial.println(1);
    Serial.print("P5 = ");
    Serial.println(1);
    Serial.print("P6 = ");
    Serial.println(1);
    Serial.print("P7 = ");
    Serial.println(1);
    Serial.print("P8 = ");
    Serial.println(1);
    Serial.print("P9 = ");
    Serial.println(1);
    Serial.print("P10 = ");
    Serial.println(1);
    Serial.print("P11 = ");
    Serial.println(1);
#endif
    setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
    setPressureOversampling(BMP3_NO_OVERSAMPLING);
    setIIRFilterCoeff(BMP3_IIR_FILTER_DISABLE);
    setOutputDataRate(BMP3_ODR_25_HZ);

    return true;

}

float Adafruit_BMP3XX::readTemperature(){
    performReading();
    return temperature;
}

uint8_t Adafruit_BMP3XX::chipID(void) { return 1; }

float Adafruit_BMP3XX::readPressure(void) {
  performReading();
  return pressure;
}

float Adafruit_BMP3XX::readAltitude(float seaLevel) {
  // Equation taken from BMP180 datasheet (page 16):
  //  http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

  // Note that using the equation from wikipedia can give bad results
  // at high altitude. See this thread for more information:
  //  http://forums.adafruit.com/viewtopic.php?f=22&t=58064

  float atmospheric = readPressure() / 100.0F;
  return 44330.0 * (1.0 - pow(atmospheric / seaLevel, 0.1903));
}

bool Adafruit_BMP3XX::performReading(){
#ifdef BMP3XX_DEBUG
    Serial.println("Setting sensor settings");
#endif
#ifdef BMP3XX_DEBUG
    Serial.println(("Setting power mode"));
#endif
#ifdef BMP3XX_DEBUG
    Serial.println(("Getting sensor data"));
#endif

#ifdef USING_CSV
    this->temperature = atof(this->sensor_data->operator[](this->file_index)[TEMPERATURE]);
    this->pressure = atof(this->sensor_data->operator[](this->file_index)[PRESSURE]);
#else
    this->temperature = rand() / rand();
    this->pressure = rand() / rand();
#endif

    return true;
}

bool Adafruit_BMP3XX::setTemperatureOversampling(uint8_t oversample) {
  return true;
}

bool Adafruit_BMP3XX::setPressureOversampling(uint8_t oversample) {
  return true;
}

bool Adafruit_BMP3XX::setIIRFilterCoeff(uint8_t filtercoeff) {
  return true;
}

bool Adafruit_BMP3XX::setOutputDataRate(uint8_t odr) {
  return true;
}

void Adafruit_BMP3XX::increase_file_index(){
    ++this->file_index;
}


