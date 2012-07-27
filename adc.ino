void adcPrint() {
  int rawValue1 = readChannel(0x48);  // Pressure Differntial Apex
  int rawValue2 = readChannel(0x49);  // Pressure Differntial Naca
  int rawValue3 = readChannel(0x4A);  // Strain Differtial Apex
  int rawValue4 = readChannel(0x4B);  // Strain Differtial Naca
  Serial.print(rawValue1);
  Serial.print(" ");
  Serial.print(rawValue2);
  Serial.print(" ");
  Serial.print(rawValue3);
  Serial.print(" ");
  Serial.print(rawValue4);
  Serial.print(" ");
  Serial3.print(rawValue1);
  Serial3.print(" ");
  Serial3.print(rawValue2);
  Serial3.print(" ");
  Serial3.print(rawValue3);
  Serial3.print(" ");
  Serial3.print(rawValue4);
  Serial3.print(" ");
  }
  
int readChannel(int DEVICE)
{
    int v;
    setting(DEVICE, CHANNEL | RANGE | 0x0003);  
    Wire.beginTransmission(DEVICE); // transmit to I2c device address
    uint8_t reg=0x00;

    Wire.write(reg);                   // point to device register 0, 16 bit ADC conversion results 
    Wire.endTransmission();            // stop transmitting

    Wire.requestFrom(DEVICE, 2);    // request 2 bytes from slave device
    while(Wire.available())            // need two bytes, MSB and LSB of converstion result value
     { 
      v =  Wire.read() << 8;     // get MSB of reading and shift it to high byte
      v += Wire.read();          // add in LSB to data
     }
    return v;
  }

//Function to configure the ADC device for desire channel, voltage range, compare mode
void setting(int DEVICE, int WORD)
 {
  Wire.beginTransmission(DEVICE); // transmit to ADS1115 device
  Wire.write(0x01);               // point to device configuration 16 bit register
  Wire.write(highByte(WORD));     // send MSB of configuration word
  Wire.write(lowByte(WORD));      // send LSB of configuration word
  Wire.endTransmission();         // stop transmitting  
 }
