//// Temperature Sensor Library----------------------------------------------------
//
//#include <OneWire.h>                         // temp lib
//#include <DallasTemperature.h>               // temp lib
// 
//// Temperature Sensor Setting (must be located in main) -------------------------
//
//#define ONE_WIRE_BUS 13                      // Set Digital Pin for Temp 1&2                       
//OneWire oneWire(ONE_WIRE_BUS);               // Calls library OneWire
//DallasTemperature sensors(&oneWire);         // Calls library DallsTemperature
//// Sets address for temperature sensors (specific to device - must be changed)
//DeviceAddress tempSensorIn = { 0x28, 0xB9, 0xAC, 0xA5, 0x03, 0x00, 0x00, 0x51 };
//DeviceAddress tempSensorOut = { 0x28, 0x51, 0xAC, 0xA5, 0x03, 0x00, 0x00, 0xD9 };
//long previousMillis = 0;                     // will store last time DS was updated
//long interval = 5000;                        // interval at which to read temp (milliseconds)
//
//// Temperature Sensor Setting (must be located main Setup) -------------------------
//
//  sensors.begin();                           // Initilize sensors
//  sensors.setResolution(tempSensorIn, 9);    // Val is resolution, 9-12 bit
//  sensors.setResolution(tempSensorOut, 9);   // Val is resolution, 9-12 bit
//
//// Temperature Sensor Loop (must be located in main Loop) -------------------------
// 
//  if (millis() - previousMillis > interval) {
//     previousMillis = millis();
//     tempPrint();
//   }
//   else
//   {
//    noTempPrint();
//   }
//  Wire.requestFrom(2, 6);                    // request 6 bytes from slave device #2
//  while(Wire.available())                    // slave may send less than requested
//  {
//    char c = Wire.read();                    // receive a byte as character
//    Serial.print(c);                         // print the character
//  }
//  
//  
//// ADC Read part 2 of channels------------------------------------------------------
//
//  int readChannel2(int DEVICE)
//{
//    int v;
//    setting(DEVICE, CHANNEL2 | RANGE | 0x0003);  
//    Wire.beginTransmission(DEVICE); // transmit to I2c device address
//    uint8_t reg=0x00;
//
//    Wire.write(reg);                   // point to device register 0, 16 bit ADC conversion results 
//    Wire.endTransmission();            // stop transmitting
//
//    Wire.requestFrom(DEVICE, 2);    // request 2 bytes from slave device
//    while(Wire.available())            // need two bytes, MSB and LSB of converstion result value
//     { 
//      v =  Wire.read() << 8;     // get MSB of reading and shift it to high byte
//      v += Wire.read();          // add in LSB to data
//     }
//    return v;
//}
//
//// Temperature Sensor void designations --------------------------------------------
//
//void printTemperature(DeviceAddress deviceAddress)
//{
//  float tempC = sensors.getTempC(deviceAddress);
//  if (tempC == -127) {
//    Serial.print("00");
//    Serial3.print("00");
//  } else {
//    Serial.print(tempC, 0);
//    Serial3.print(tempC, 0);
//  }
//}
//
//void tempPrint()
//{ 
//  sensors.requestTemperatures();
//  printTemperature(tempSensorIn);
//  Serial.print(" ");
//  Serial3.print(" ");
//  printTemperature(tempSensorOut);
//  Serial.print(" ");
//  Serial3.print(" ");
//}
//
//void noTempPrint()
//{
//  Serial.print("-");
//  Serial.print(" ");
//  Serial.print("-");
//  Serial.print(" ");
//  Serial3.print("-");
//  Serial3.print(" ");
//  Serial3.print("-");
//  Serial3.print(" ");
//}
