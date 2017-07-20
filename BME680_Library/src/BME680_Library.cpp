
#include "BME680_Library.h"
#include <Wire.h>

BME680_Library::BME680_Library(uint8_t i2c_addr){
  gas_sensor.dev_id = i2c_addr;
	gas_sensor.intf = BME680_I2C_INTF;
	gas_sensor.read = BME680_Library::i2c_read;
	gas_sensor.write = BME680_Library::i2c_write;
	gas_sensor.delay_ms = BME680_Library::delay_msec;
}

boolean BME680_Library::begin(void){
  int8_t rslt = BME680_OK;
	rslt = bme680_init(&gas_sensor);
  return BME680_OK == rslt;
}

boolean BME680_Library::configureForcedMode(void){
  int8_t rslt = -1;
  uint8_t set_required_settings;

	/* Set the temperature, pressure and humidity settings */
	gas_sensor.tph_sett.os_hum = BME680_OS_2X;
	gas_sensor.tph_sett.os_pres = BME680_OS_4X;
	gas_sensor.tph_sett.os_temp = BME680_OS_8X;
	gas_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

	/* Set the remaining gas sensor settings and link the heating profile */
	gas_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
	/* Create a ramp heat waveform in 3 steps */
	gas_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
	gas_sensor.gas_sett.heatr_dur = 150; /* milliseconds */

	/* Select the power mode */
	/* Must be set before writing the sensor configuration */
	gas_sensor.power_mode = BME680_FORCED_MODE;

	/* Set the required sensor settings needed */
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL
		| BME680_GAS_SENSOR_SEL;

	/* Set the desired sensor configuration */
	rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

	/* Set the power mode */
	rslt = bme680_set_sensor_mode(&gas_sensor);

	/* Get the total measurement duration so as to sleep or wait till the
	 * measurement is complete */
	uint16_t meas_period;
	bme680_get_profile_dur(&meas_period, &gas_sensor);
	BME680_Library::delay_msec(meas_period); /* Delay till the measurement is ready */

  return (rslt == 0);
}

uint8_t BME680_Library::getDeviceID(void){
  return gas_sensor.chip_id;
}

int8_t BME680_Library::i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len){
  int8_t ret = -1; /* Return 0 for Success, non-zero for failure */

/*
 * The parameter dev_id can be used as a variable to store the I2C address of the device
 */

/*
 * Data on the bus should be like
 * |------------+---------------------|
 * | I2C action | Data                |
 * |------------+---------------------|
 * | Start      | -                   |
 * | Write      | (reg_addr)          |
 * | Write      | (reg_data[0])       |
 * | Write      | (....)              |
 * | Write      | (reg_data[len - 1]) |
 * | Stop       | -                   |
 * |------------+---------------------|
 */

  uint8_t num_written = 0;

  Wire.beginTransmission(dev_id); // starts queueing bytes to be written

  while(num_written < len){    // queue a (addr / value) pair of bytes per data value
    Wire.write(reg_addr);           // write the register address
    Wire.write(*reg_data);      // write the register value
    reg_addr++;                     // advance the register address
    reg_data++;                 // advance the write value pointer
    num_written++;                  // increment the number of bytes written
  }

  if(0 == Wire.endTransmission()){  // actually sends the queued bytes
    // if endTransmission returns a non-zero result
    // it's some kind of error, otherwise it's good
    ret = 0;
  }

  return ret;
}


int8_t BME680_Library::i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len){
  int8_t ret = -1; /* Return 0 for Success, non-zero for failure */

  /*
   * The parameter dev_id can be used as a variable to store the I2C address of the device
   */

  /*
   * Data on the bus should be like
   * |------------+---------------------|
   * | I2C action | Data                |
   * |------------+---------------------|
   * | Start      | -                   |
   * | Write      | (reg_addr)          |
   * | Stop       | -                   |
   * | Start      | -                   |
   * | Read       | (reg_data[0])       |
   * | Read       | (....)              |
   * | Read       | (reg_data[len - 1]) |
   * | Stop       | -                   |
   * |------------+---------------------|
   */

  Wire.beginTransmission(dev_id);                          // START+SLA+W
  Wire.write(reg_addr);                                    // REG
  Wire.endTransmission(false);                             // STOP (false would be REP START)
  Wire.requestFrom(dev_id, len,  1U);                      // SLA+R and STOP

  // using the blink without delay pattern here
  const int32_t timeout = 1000;                            // wait for up to 1s
  uint32_t previousMillis = millis();
  uint32_t currentMillis = millis();
  uint8_t num_read = 0;
  boolean complete = false;

  while(!complete){   // loop until break because got all the bytes or timed out
    currentMillis = millis();

    if(Wire.available()){
      *reg_data = Wire.read();                         // DATA
      reg_data++; // advance write pointer
      num_read++;     // increment read counter
    }

    if(num_read == len){                              // read complete
      ret = 0;                            // good outcome
      complete = true;
    }
    else if (currentMillis - previousMillis >= timeout) {  // timeout
      complete = true;
    }
  }

  return ret;
}

void BME680_Library::delay_msec(uint32_t ms){
  delay(ms);
}

boolean BME680_Library::read(){

  int rslt = bme680_get_sensor_data(&data, &gas_sensor);
  // if(rslt != 0){
  //   Serial.print("RSLT = ");
  //   Serial.println(rslt, HEX);
  // }
  return (rslt == 0);
}

float BME680_Library::getTemperature(){
  return data.temperature / 100.0f;
}

float BME680_Library::getRelativeHumidity(){
  return data.humidity / 1000.0f;
}

float BME680_Library::getBarometricPressure(){
  return data.pressure / 100.0f;
}

uint32_t BME680_Library::getGasResistance(){
  if(data.status & BME680_HEAT_STAB_MSK){
    return data.gas_resistance;
  }
  else{
    return 0;
  }
}
