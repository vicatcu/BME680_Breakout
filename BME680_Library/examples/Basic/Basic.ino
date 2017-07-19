#include <BME680_Library.h>
#include <Wire.h>

BME680_Library bme680;

void setup(void){
  Serial.begin(9600);

  Wire.begin();

  Serial.print("BME Initialization...");
  if(bme680.begin()){
     Serial.print("Succeeded!");
  }
  else {
    Serial.print("Failed!");
    for(;;); // spin forever
  }

  Serial.print("Configuring Forced Mode...");
  if(bme680.configureForcedMode()){
     Serial.print("Succeeded!");
  }
  else {
    Serial.print("Failed!");
    for(;;); // spin forever
  }

  Serial.println(F("Temperature(degC),Relative_Humidity(%),Pressure(hPa),Gas_Resistance(Ohms)"));
}

void loop(void){
  if(bme680.read()){
    Serial.print(bme680.getTemperature(), 2);
    Serial.print(F(","));
    Serial.print(bme680.getRelativeHumidity(), 2);
    Serial.print(F(","));
    Serial.print(bme680.getBarometricPressure(), 2);
    Serial.print(F(","));
    Serial.print(bme680.getGasResistance());
    Serial.println();
  }
  else{
    Serial.println("BME680 Read Failed!");
  }
  
  delay(2000);
}
