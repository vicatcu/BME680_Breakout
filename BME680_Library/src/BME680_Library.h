#ifndef __BME680_LIBRARY__
#define __BME680_LIBRARY__

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "utility/bme680.h"
}

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

  // these have to be static so that the class can bootstrap the driver by passing a function pointer
  static s8 i2c_write(u8 dev_addr, u8 reg_addr, u8 *reg_data_ptr, u8 data_len);
  static s8 i2c_read(u8 dev_addr, u8 reg_addr, u8 *reg_data_ptr, u8 data_len);
  static s8 i2c_burst_read(u8 slave_addr, u8 reg_addr, u8 *data_u8, u32 length_u32);
  static void delay_msec(BME680_MDELAY_DATA_TYPE);
public:
  BME680_Library(void);
  uint8_t begin(void);


};

#endif
