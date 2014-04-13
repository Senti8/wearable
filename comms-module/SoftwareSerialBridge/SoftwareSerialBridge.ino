/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial deviceSerial(2,3); // RX, TX

#define DIGITAL_OUT_PIN    13
void blink(uint8_t count);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);

  // set the data rate for the SoftwareSerial port
  deviceSerial.begin(4800);
}

void loop() // run over and over
{    
  
  bool didReceive = false;
  
  while(deviceSerial.available() > 0) {
    didReceive = true;
    Serial.write(deviceSerial.read());
  } 
  
  while(Serial.available() > 0) {
    deviceSerial.write(Serial.read());
  }
  
  if(didReceive){
    blink(1);
  }
}

void blink(uint8_t count)
{
  for(int i=0; i < count; i++) {
    digitalWrite(DIGITAL_OUT_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                            // wait for a bit
    digitalWrite(DIGITAL_OUT_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);   
  }
}

