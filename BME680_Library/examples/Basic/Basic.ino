#include <BME680_Library.h>
#include <Wire.h>

BME680_Library bme680;

void setup(void){
  Serial.begin(115200);

  Wire.begin();

  Serial.print("BME Initialization...");
  if(bme680.begin()){
     Serial.print("Succeeded!");
  }
  else {
    Serial.print("Failed!");
    for(;;); // spin forever
  }
  Serial.println();

  Serial.print("Configuring Forced Mode...");
  if(bme680.configureForcedMode()){
     Serial.print("Succeeded!");
  }
  else {
    Serial.print("Failed!");
    for(;;); // spin forever
  }
  Serial.println();

  Serial.println(F("Temperature(degC),Relative_Humidity(%),Pressure(hPa),Gas_Resistance(Ohms)"));
}

void loop(void){
  bme680.configureForcedMode(); // otherwise you get BME680_W_NO_NEW_DATA warning code?
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
