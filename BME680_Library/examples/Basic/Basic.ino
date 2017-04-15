#include <BME680_Library.h>

BME680_Library bme680;

void setup(void){
  Serial.begin(9600);

  Serial.print("BME Initialization...");
  if(bme680.begin()){
     Serial.print("Succeeded!");
  }
  else {
    Serial.print("Failed!");
    for(;;); // spin forever
  }
}

void loop(void){

}
