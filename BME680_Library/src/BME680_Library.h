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

public:
  BME680_Library(void);

};

#endif
