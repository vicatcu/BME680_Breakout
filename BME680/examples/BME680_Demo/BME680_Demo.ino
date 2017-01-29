#include <Wire.h>
//#include <BME680.h>

//BME680 bme680;

void setup(void){

  // Start serial and Wire
  Serial.begin(115200);
  Serial.println("BME680 Demonstration");
  Wire.begin();

  // Setup the sensor
  // The sensor can run in sleep, forced, sequential, or parallel mode. 
  // Invoke the configure call for the mode you wish to operate in.

  BME680.configureSleep(); // No settings needed
  BME680.configureForced(oversampling, IIRfilter, gas_enable, heater_index, heater_ontime, heater_temperature);
  BME680.configureSequential(oversampling, IIRfilter, gas_enable, heater_setpoints, heater_ontimes, heater_temperatures, standby_time);
  BME680.configureParallel(oversampling, IIRfilter, gas_enable, heater_setpoints, waittime, heater_ontimes, heater_temperatures);

  // If you don't need custom configurations and just want to get started, configure as "simple"
  // This sets the BME680 to parallel mode with the highest oversampling, so the measurements are
  // continuously updated in the most precise setting.
  BME680.configureSimple();
  

  // Print header for sensor output
  Serial.println("Temperature[C], Temperature[F], Humidity[%], Dewpoint[C], \
                  Dewpoint[F], Pressure[hPa], Altitude[m], Altitude[ft], VOC");
}

void loop(void){

  // Print sensor readings in a CSV format.
  // Output can easily be read into Excel or other data anaalysis tools.
  Serial.print(bmp680.readTemperatureC(), 2);
  Serial.print(",");
  Serial.print(bmp680.readTemperatureF(), 2);
  Serial.print(",");   
  Serial.print(bmp680.readHumidity(), 2);
  Serial.print(",");
  Serial.print(bmp680.readDewpointC(), 2);
  Serial.print(",");
  Serial.print(bmp680.readDewpointF(), 2);
  Serial.print(",");
  Serial.print(bmp680.readPressure(), 2);
  Serial.print(",");
  Serial.print(bmp680.readAltitudem(), 2);
  Serial.print(",");
  Serial.print(bmp680.readAltitudeft(), 2);
  Serial.print(",");
  Serial.println(bmp680.readVOC(), 2);
  
  delay(1000);
  
}

