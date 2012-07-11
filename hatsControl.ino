// <<< HATS Multi-Control Sensor Package for Arduino MEGA-2560 >>>

// Subsystem code is placed into tabs within the Arduino software
// hatsControl.ino is the main page

// Necessary Libraries ----------------------------------------------------------

#include <OneWire.h>                         // temp lib
#include <DallasTemperature.h>               // temp lib
#include <Wire.h>                            // temp lib
#include <Encoder.h>                         // encoder lib
#include <SimpleTimer.h>

// Temperature Sensor Setting (must be located in main) -------------------------

#define ONE_WIRE_BUS 13                      // Set Digital Pin for Temp 1&2                       
OneWire oneWire(ONE_WIRE_BUS);               // Calls library OneWire
DallasTemperature sensors(&oneWire);         // Calls library DallsTemperature
//Sets address for temperature sensors (specific to device - must be changed)
DeviceAddress tempSensorIn = { 0x28, 0xB9, 0xAC, 0xA5, 0x03, 0x00, 0x00, 0x51 };
DeviceAddress tempSensorOut = { 0x28, 0x51, 0xAC, 0xA5, 0x03, 0x00, 0x00, 0xD9 };


// Motor Control Parameters -----------------------------------------------------

char keyboardInput;                          // accept keyboard input
int runValue = 0;                            // set initial motor value to off

// Analog Pins ------------------------------------------------------------------

int presApxF = A1;                           // Pressure front of Apex (2)
int presApxB = A0;                           // Pressure back of Apex (1)
int presNacaF = A2;                          // Pressure front of NACA (3)
int presNacaB = A3;                          // Pressure back of NACA (4)
int presAm = A4;                             // Pressure Ambient
#define windX  A8                            // Wind Sensor X Dir
#define windY  A9                            // Wind Sensor Y Dir
#define windZ  A10                           // Wind Sensor Z Dir
#define windAll  A11                         // Wind Sensor Omni
int strainApx1 = A12;                        // Strain Apex 1
int strainApx2 = A13;                        // Strain Apex 2
int strainNaca1 = A14;                       // Strain Naca 1
int strainNaca2 = A15;                       // Strain Naca 2

// Digital Pins (temp pin set above) --------------------------------------------

int motorPin = 12;                           // Motor Control Out
Encoder motor1(19, 18);                      // Encoder A&B for Motor1
Encoder motor2(21, 20);                      // Encoder A&B for Motor2
int ledPin =  11;                            // Open Log Status LED

// Set Up -----------------------------------------------------------------------

void setup(){
  Serial.begin(19200);                       // Sets baud rate for data to SD card (Open Log default 9600)
  Serial3.begin(4800);                       // Sets baud rate for HASP connection (HASP requires 4800)
  delay(2000);                               // Wait a second for OpenLog to init
  Serial.println("hats-log");                // Print File name
  Serial.println();                          // Print line
//  Serial3.println("hats-log");                // Print File name
//  Serial3.println();                          // Print line
  sensors.begin();                           // Initilize sensors
  sensors.setResolution(tempSensorIn, 9);    // Val is resolution, 9-12 bit
  sensors.setResolution(tempSensorOut, 9);   // Val is resolution, 9-12 bit
  pinMode(motorPin, OUTPUT);                 // Motor pin set to output
}

// Print Loop -------------------------------------------------------------------

void loop(){
  millisPrint();                             // Print Time
  //tempPrint();                             // Print Encoder
  presPrint();                               // Print Pressure
  strainPrint();                             // Print Strain
  windPrint();                               // Print Wind 
  encoderPrint();                            // Print Encoder
  motorControl();                            // Set Motor Speed (0-100)
  Serial.println();                          // Print Space
//  Serial3.println();                         // Print Space
}

// Time Loop --------------------------------------------------------------------

void millisPrint(){                          
  Serial.print(millis()); 
  Serial.print(",");
//  Serial3.print(millis()); 
//  Serial3.print(",");
}
