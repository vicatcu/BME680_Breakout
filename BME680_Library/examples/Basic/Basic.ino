#include <BME680_Library.h>

BME680_Library bme680;

void setup(void){
  Serial.begin(9600);

  if(!bme680.begin()){
    Serial.print("BME680 Initialization Failed!");
    for(;;); // spin forever
  }

}

void loop(void){

}
