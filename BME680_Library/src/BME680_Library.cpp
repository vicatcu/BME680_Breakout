
#include "BME680_Library.h"
#include <Wire.h>
#include <Arduino.h>

void delay(unsigned long);

BME680_Library::BME680_Library(void){
  bme680_sensor_no[0].bme680_bus_write = BME680_Library::i2c_write;
  bme680_sensor_no[1].bme680_bus_read = BME680_Library::i2c_read;
  bme680_sensor_no[1].bme680_burst_read = BME680_Library::i2c_burst_read;
  bme680_sensor_no[1].delay_msec = BME680_Library::delay_msec;
  bme680_sensor_no[1].dev_addr = BME680_I2C_ADDR_SECONDARY;
  bme680_sensor_no[1].interface = BME680_I2C_INTERFACE;
}

uint8_t BME680_Library::begin(void){
  enum bme680_return_type com_rslt = bme680_init(&bme680_sensor_no[0]);
  return (com_rslt == BME680_COMM_RES_OK) ? 1 : 0;
}

int8_t BME680_Library::i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint8_t data_len){
  // do stuff with Wire

}

int8_t BME680_Library::i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint8_t data_len){
  // do stuff with Wire

}

int8_t BME680_Library::i2c_burst_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data_uint8_t, uint32_t length_uint32_t){
  // do stuff with Wire

}

void BME680_Library::delay_msec(BME680_MDELAY_DATA_TYPE ms){
  delay(ms);
}
