#ifndef BME680_H
#define BME680_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>

#define BME680_I2C_ADDRESS          (0x77)   /* Device Address (default) */
#define BME680_ID                   (0x50)   /* Chip ID of device */
#define BME680_STATUS               (0x73)   /* Status of the BME680 */
#define BME680_RESET                (0x60)   /* Reset the sensor */
#define BME680_CONFIG               (0x75)   /*  General config register */

// Pressure Data - Field 0
#define BME680_FIELD0_PRESS_MSB     (0x1F)    /* MSB of raw pressure measurement */
#define BME680_FIELD0_PRESS_LSB     (0x20)    /* LSB of raw pressure measurement */
#define BME680_FIELD0_PRESS_XLSB    (0x21)    /* XLSB of raw pressure measurement */

// Pressure Data - Field 1
#define BME680_FIELD1_PRESS_MSB     (0x30)    /* MSB of raw pressure measurement */
#define BME680_FIELD1_PRESS_LSB     (0x31)    /* LSB of raw pressure measurement */
#define BME680_FIELD1_PRESS_XLSB    (0x32)    /* XLSB of raw pressure measurement */

// Pressure Data - Field 2
#define BME680_FIELD2_PRESS_MSB     (0x41)    /* MSB of raw pressure measurement */
#define BME680_FIELD2_PRESS_LSB     (0x42)    /* LSB of raw pressure measurement */
#define BME680_FIELD2_PRESS_XLSB    (0x43)    /* XLSB of raw pressure measurement */

// Temperature 1 Data - Field 0
#define BME680_FIELD0_TEMP1_MSB     (0x22)    /* MSB of raw temperature measurement */
#define BME680_FIELD0_TEMP1_LSB     (0x23)    /* LSB of raw temperature measurement */
#define BME680_FIELD0_TEMP1_XLSB    (0x24)    /* XLSB of raw temperature measurement */

// Temperature 1 Data - Field 1
#define BME680_FIELD1_TEMP1_MSB     (0x33)    /* MSB of raw temperature measurement */
#define BME680_FIELD1_TEMP1_LSB     (0x34)    /* LSB of raw temperature measurement */
#define BME680_FIELD1_TEMP1_XLSB    (0x35)    /* XLSB of raw temperature measurement */

// Temperature 1 Data - Field 2
#define BME680_FIELD2_TEMP1_MSB     (0x44)    /* MSB of raw temperature measurement */
#define BME680_FIELD2_TEMP1_LSB     (0x45)    /* LSB of raw temperature measurement */
#define BME680_FIELD2_TEMP1_XLSB    (0x46)    /* XLSB of raw temperature measurement */

// Humidity Data - Field 0
#define BME680_FIELD0_HUM_MSB       (0x25)    /* MSB of raw humidity measurement */
#define BME680_FIELD0_HUM_LSB       (0x26)    /* LSB of raw humidity measurement */

// Humidity Data - Field 1
#define BME680_FIELD1_HUM_MSB       (0x36)    /* MSB of raw humidity measurement */
#define BME680_FIELD1_HUM_LSB       (0x37)    /* LSB of raw humidity measurement */

// Humidity Data - Field 2
#define BME680_FIELD2_HUM_MSB       (0x47)    /* MSB of raw humidity measurement */
#define BME680_FIELD2_HUM_LSB       (0x48)    /* LSB of raw humidity measurement */

// Gas Data - Field 0
#define BME680_FIELD0_GAS_MSB       (0x2A)    /* MSB of raw gas measurement */
#define BME680_FIELD0_GAS_LSB       (0x2B)    /* LSB of raw gas measurement */

// Gas Data - Field 1
#define BME680_FIELD1_GAS_MSB       (0x3B)    /* MSB of raw gas measurement */
#define BME680_FIELD1_GAS_LSB       (0x3C)    /* LSB of raw gas measurement */

// Gas Data - Field 2
#define BME680_FIELD2_GAS_MSB       (0x4C)    /* MSB of raw gas measurement */
#define BME680_FIELD2_GAS_LSB       (0x4D)    /* LSB of raw gas measurement */

// Gas Resistance Range
#define BME680_FIELD0_GAS_RANGE_LSB (0x2B)    /* ADC range of gas resistance */
#define BME680_FIELD1_GAS_RANGE_LSB (0x3C)    /* ADC range of gas resistance */
#define BME680_FIELD2_GAS_RANGE_LSB (0x4D)    /* ADC range of gas resistance */

// New Data Status
#define BME680_FIELD0_MEAS_STATUS_0 (0x1D)    /* New data flag for field 0 */
#define BME680_FIELD1_MEAS_STATUS_0 (0x2E)    /* New data flag for field 1 */
#define BME680_FIELD2_MEAS_STATUS_0 (0x3F)    /* New data flag for field 2 */
#define BME680_FIELD0_MEAS_STATUS_1 (0x1E)    /* New data flag for field 0 */
#define BME680_FIELD1_MEAS_STATUS_1 (0x2F)    /* New data flag for field 1 */
#define BME680_FIELD2_MEAS_STATUS_1 (0x40)    /* New data flag for field 2 */

// Gas Control Registers
#define BME680_IDAC_HEAT_0          (0x50)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_1          (0x51)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_2          (0x52)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_3          (0x53)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_4          (0x54)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_5          (0x55)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_6          (0x56)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_7          (0x57)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_8          (0x58)    /* idac_heat of particular heater set point */
#define BME680_IDAC_HEAT_9          (0x59)    /* idac_heat of particular heater set point */

#define BME680_RES_HEAT_0           (0x5A)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_1           (0x5B)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_2           (0x5C)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_3           (0x5D)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_4           (0x5E)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_5           (0x5F)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_6           (0x60)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_7           (0x61)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_8           (0x62)    /* Decimal value for achieving target heater resistance */
#define BME680_RES_HEAT_9           (0x63)    /* Decimal value for achieving target heater resistance */

#define BME680_GAS_WAIT_0           (0x64)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_1           (0x65)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_2           (0x66)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_3           (0x67)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_4           (0x68)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_5           (0x69)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_6           (0x6A)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_7           (0x6B)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_8           (0x6C)    /* Controls heater timing of the gas sensor */
#define BME680_GAS_WAIT_9           (0x6D)    /* Controls heater timing of the gas sensor */

#define BME680_GAS_WAIT_SHARED      (0x6E)    /* Wait time between sub measurement sequences in parallel mode */

#define BME680_CTRL_GAS_0           (0x70)    /* Gas sensor control settings */
#define BME680_CTRL_GAS_1           (0x71)    /* Gas sensor control settings */

// Pressure, Temperature, and Relative Humidity Control Registers
#define BME680_CTRL_HUM             (0x72)    /* Controls humidity sensor settings */
#define BME680_CTRL_MEAS            (0x74)    /* Controls measurement settings */

class BME680 {

public:
      BME680();
      uint8_t status(void);
      uint8_t write(uint8_t reg, uint8_t data);
      uint8_t read(uint8_t reg);
private:
};

#endif
