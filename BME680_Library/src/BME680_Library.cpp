
#include "BME680_Library.h"
#include <Wire.h>

BME680_Library::BME680_Library(uint8_t i2c_addr){
  bme680_sensor_no[0].bme680_bus_write = BME680_Library::i2c_write;
  bme680_sensor_no[0].bme680_bus_read = BME680_Library::i2c_read;
  bme680_sensor_no[0].bme680_burst_read = BME680_Library::i2c_burst_read;
  bme680_sensor_no[0].delay_msec = BME680_Library::delay_msec;

  i2c_address = i2c_addr;
  bme680_sensor_no[0].dev_addr = i2c_addr;

  bme680_sensor_no[0].interface = BME680_I2C_INTERFACE;
  bme680_sensor_no[0].chip_id = 0xFF;
}

boolean BME680_Library::begin(void){
  enum bme680_return_type com_rslt = bme680_init(&bme680_sensor_no[0]);
  return (com_rslt == BME680_COMM_RES_OK);
}

uint8_t BME680_Library::getDeviceID(void){
  return bme680_sensor_no[0].chip_id;
}

int8_t BME680_Library::i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint8_t data_len){


}

int8_t BME680_Library::i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint8_t data_len){
  // reads I2C @ dev_addr, asks for register address reg_addr
  // expects to read data_len bytes back and stores them in reg_data_ptr array

  enum bme680_return_type ret = BME680_COMM_RES_ERROR;     // assume an error will happen

  Wire.beginTransmission(dev_addr);                        // START+SLA+W
  Wire.write(reg_addr);                                    // REG
  Wire.endTransmission(false);                             // REP START
  Wire.requestFrom(dev_addr, data_len,  1U);               // SLA+R

  // using the blink without delay pattern here
  const int32_t timeout = 1000;                            // wait for up to 1s
  uint32_t previousMillis = millis();
  uint32_t currentMillis = millis();
  uint8_t num_read = 0;
  boolean complete = false;

  while(!complete){   // loop until break because got all the bytes or timed out
    currentMillis = millis();

    if(Wire.available()){
      *reg_data_ptr = Wire.read();                         // DATA
      reg_data_ptr++; // advance write pointer
      num_read++;     // increment read counter
    }

    if(num_read == data_len){                              // read complete
      ret = BME680_COMM_RES_OK;                            // good outcome
      complete = true;
    }
    else if (currentMillis - previousMillis >= timeout) {  // timeout
      complete = true;
    }
  }

  return ret;
}

int8_t BME680_Library::i2c_burst_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data_uint8_t, uint32_t length_uint32_t){
  // do stuff with Wire

}

void BME680_Library::delay_msec(BME680_MDELAY_DATA_TYPE ms){
  delay(ms);
}
