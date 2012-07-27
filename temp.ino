float inTrans = 0;
float exTrans = 0;
float inC = 0;
float exC = 0;
float conv = 1024/5;
float trans = 0.0225;

void aTempPrint()
{
  int tempIn = analogRead(atempIn);
  int tempEx = analogRead(atempEx);
  float inTrans = (tempIn / conv);
  float exTrans = (tempEx / conv);
  inC = ((inTrans - 1.375) / trans);
  exC = ((exTrans - 1.375) / trans);
  Serial.print(inC, 0);
  Serial.print(" ");
  Serial.print(exC, 0);
  Serial.print(" ");
  Serial3.print(inC, 0);
  Serial3.print(" ");
  Serial3.print(exC, 0);
  Serial3.print(" ");
  if(tempIn < minTemp) {
    digitalWrite(heatPin, HIGH);             // Turns on heater is temperature is lower than threshold
  }
  else {
    digitalWrite(heatPin, LOW);              // Turns heater off
    Serial3.println("h");
    Serial3.println(" ");
  }
}
  
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127) {
    Serial.print("00");
    Serial3.print("00");
  } else {
    Serial.print(tempC, 0);
    Serial3.print(tempC, 0);
  }
}

void tempPrint()
{ 
  sensors.requestTemperatures();
  printTemperature(tempSensorIn);
  Serial.print(" ");
//  Serial3.print(" ");
  printTemperature(tempSensorOut);
  Serial.print(" ");
//  Serial3.print(" ");
}

void noTempPrint()
{
  Serial.print("-");
  Serial.print(" ");
  Serial.print("-");
  Serial.print(" ");
//  Serial3.print("-");
//  Serial3.print(" ");
//  Serial3.print("-");
//  Serial3.print(" ");
}
