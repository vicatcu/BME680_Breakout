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
  struct bme680_t bme680_sensor_no[1];
  /* BME680 sensor’s compensated data structure instance */
  struct bme680_comp_field_data compensate_data_sensor[1][3];
  /* BME680 sensor’s uncompensated data structure instance */
  struct bme680_uncomp_field_data uncompensated_data_of_sensor[1][3];
  /* BME680 sensor’s configuration structure instance */
  struct bme680_sens_conf set_conf_sensor[1];
  /* BME680 sensor’s heater configuration structure instance */
  struct bme680_heater_conf set_heatr_conf_sensor[1];

  uint8_t i2c_address;

  // these have to be static so that the class can bootstrap the driver by passing a function pointer
  static int8_t i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint8_t data_len);
  static int8_t i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint8_t data_len);
  static int8_t i2c_burst_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint32_t data_len);
  static void delay_msec(BME680_MDELAY_DATA_TYPE);
public:
  BME680_Library(uint8_t i2c_addr = BME680_I2C_ADDR_SECONDARY);
  boolean begin(void);

  uint8_t getDeviceID(void);
};

#endif
