void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127) {
    Serial.print("22");
//    Serial3.print("22");
  } else {
    Serial.print(tempC, 0);
//    Serial3.print("22");
  }
}

void tempPrint()
{ 
  sensors.requestTemperatures();
  printTemperature(tempSensorIn);
  Serial.print(",");
//  Serial3.print(",");
  printTemperature(tempSensorOut);
  Serial.print(",");
//  Serial3.print(",");
}

