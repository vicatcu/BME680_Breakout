
#include "BME680_Library.h"
#include <Wire.h>
// #include <Arduino.h> // this breaks stuff right now

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

s8 BME680_Library::i2c_write(u8 dev_addr, u8 reg_addr, u8 *reg_data_ptr, u8 data_len){
  // do stuff with Wire

}

s8 BME680_Library::i2c_read(u8 dev_addr, u8 reg_addr, u8 *reg_data_ptr, u8 data_len){
  // do stuff with Wire

}

s8 BME680_Library::i2c_burst_read(u8 slave_addr, u8 reg_addr, u8 *data_u8, u32 length_u32){
  // do stuff with Wire

}

void BME680_Library::delay_msec(BME680_MDELAY_DATA_TYPE ms){
  // delay(ms); // issues with including Arduino.h right now preclude this
}
