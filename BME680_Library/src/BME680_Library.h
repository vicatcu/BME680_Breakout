#ifndef __BME680_LIBRARY__
#define __BME680_LIBRARY__

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "utility/bme680.h"
}

#include <Arduino.h>

class BME680_Library {
private:
  struct bme680_dev gas_sensor;
  struct bme680_field_data data;
  uint8_t i2c_address;

  // these have to be static so that the class can bootstrap the driver by passing a function pointer
  static int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
  static int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
  static void delay_msec(uint32_t ms);
public:
  BME680_Library(uint8_t i2c_addr = BME680_I2C_ADDR_SECONDARY);
  boolean begin(void);
  uint8_t getDeviceID(void);
  boolean configureForcedMode(void);
  boolean read();
  float getTemperature();
  float getRelativeHumidity();
  float getBarometricPressure();
  uint32_t getGasResistance();
};

#endif
