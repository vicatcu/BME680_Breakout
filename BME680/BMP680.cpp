#include "BMP680.h"

BMP680::BMP680() {

}

uint8_t BMP680::write(uint8_t reg, uint8_t data) {

      Wire.beginTransmission(BMP680_I2C_ADDRESS);             // START+SLA+W
      Wire.write(reg);                                        // REG
      Wire.write(data);                                       // DATA
      Wire.endTransmission(true);                             // STOP

      // read back the value of the register
      return read(reg);
}

uint8_t BMP680::read(uint8_t reg){
      uint8_t chr = 0;
      Wire.beginTransmission(BMP680_I2C_ADDRESS);             // START+SLA+W
      Wire.write(reg);                                        // REG
      Wire.endTransmission(false);                            // REP START
      Wire.requestFrom(BMP680_I2C_ADDRESS, 1, true);          // SLA+R
      if(Wire.available()){
            chr = Wire.read();                                // DATA
      }

      return chr;
}

uint8_t BMP680::status(void) {
      return read(BMP680_STATUS);
}
