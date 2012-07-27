// <<< HATS Multi-Control Sensor Package for Arduino MEGA-2560 >>>

// Subsystem code is placed into tabs within the Arduino software
// hatsControl.ino is the main page

// Necessary Libraries ----------------------------------------------------------

#include <OneWire.h>                         // temp lib
#include <DallasTemperature.h>               // temp lib
#include <Wire.h>                            // temp lib
#include <Encoder.h>                         // encoder lib
#include <I2Cdev.h>                          // i2c lib
#include "ADS1115.h"                         // ADCr lib

// Temperature Sensor Setting (must be located in main) -------------------------

#define ONE_WIRE_BUS 13                      // Set Digital Pin for Temp 1&2                       
OneWire oneWire(ONE_WIRE_BUS);               // Calls library OneWire
DallasTemperature sensors(&oneWire);         // Calls library DallsTemperature
// Sets address for temperature sensors (specific to device - must be changed)
DeviceAddress tempSensorIn = { 0x28, 0xB9, 0xAC, 0xA5, 0x03, 0x00, 0x00, 0x51 };
DeviceAddress tempSensorOut = { 0x28, 0x51, 0xAC, 0xA5, 0x03, 0x00, 0x00, 0xD9 };
long previousMillis = 0;                     // will store last time DS was updated
long interval = 5000;                        // interval at which to read temp (milliseconds)
int minTemp = 500;                           // sets ADC value at which heater is activated


// Motor Control Parameters -----------------------------------------------------

char keyboardInput;                          // accept keyboard input
int runValue = 0;                            // set initial motor value to off

// ADC Parameters ---------------------------------------------------------------

const int RANGE= 0x0200; const int range = 4096;  // +/-4.096 vdc range, electrical limit = Vcc applies
const int CHANNEL = 0x00E0; byte ch = 0;          // input wired to + AIN0 - AIN1, diff +/- max range

// Analog Pins ------------------------------------------------------------------

int presAm = A0;                             // Pressure Ambient
int atempIn = A1;                            // Analog Temp Interior
int atempEx = A2;                            // Analog Temp Interior
#define windX  A8                            // Wind Sensor X Dir
#define windY  A9                            // Wind Sensor Y Dir
#define windZ  A10                           // Wind Sensor Z Dir
#define windAll  A11                         // Wind Sensor Omni

// Digital Pins (temp pin set above) --------------------------------------------

int motorPin = 12;                           // Motor Control Out
Encoder motor1(3, 2);                        // Encoder A&B for Motor1
Encoder motor2(19, 18);                      // Encoder A&B for Motor2
int heatPin = 6;                             // heater pin

// Set Up -----------------------------------------------------------------------

void setup(){
  Wire.begin();
  Serial.begin(19200);                       // Sets baud rate for data to SD card (Open Log default 9600)
  Serial3.begin(4800);                       // Sets baud rate for HASP connection (HASP requires 4800)
  delay(5000);                               // Wait a second for OpenLog to init
  Serial.println("asu-hats-data");                // Print File name
  Serial.println();                          // Print line
  Serial3.println("asu-hats-data");               // Print File name
  Serial3.println();                         // Print line
  sensors.begin();                           // Initilize sensors
  sensors.setResolution(tempSensorIn, 9);    // Val is resolution, 9-12 bit
  sensors.setResolution(tempSensorOut, 9);   // Val is resolution, 9-12 bit
  pinMode(motorPin, OUTPUT);                 // Motor pin set to output
}

// Print Loop -------------------------------------------------------------------

void loop(){
  millisPrint();                             // Print Time
  adcPrint();                                // Print ADC Strain and Pressure
  pressPrint();                              // Pressure Print
  windPrint();                               // Print Wind 
  motorControl();                            // Set Motor Speed (0-100)
  aTempPrint();                              // Analog Temp Sensor (uncalibrated)
  encoderPrint();                            // Print Encoder
  if (millis() - previousMillis > interval) {
     previousMillis = millis();
     tempPrint();
   }
   else
   {
    noTempPrint();
   }
  Wire.requestFrom(2, 6);                    // request 6 bytes from slave device #2
  while(Wire.available())                    // slave may send less than requested
  {
    char c = Wire.read();                    // receive a byte as character
    Serial.print(c);                         // print the character
  }
  Serial.println();                          // Print Space
  Serial3.println();                         // Print Space
}

// Time Loop --------------------------------------------------------------------

void millisPrint(){                          
  Serial.print(millis()); 
  Serial.print(" ");
  Serial3.print(millis()); 
  Serial3.print(" ");
}
