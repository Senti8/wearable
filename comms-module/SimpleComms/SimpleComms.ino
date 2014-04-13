
/*

Copyright (c) 2012, 2013 RedBearLab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

//"services.h/spi.h/boards.h" is needed in every new project
#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
 
#define DIGITAL_OUT_PIN    13
#define DIGITAL_IN_PIN     5

void blink(uint8_t count);

void setup()
{
  // Default pins set to 9 and 8 for REQN and RDYN
  // Set your REQN and RDYN here before ble_begin() if you need
  //ble_set_pins(3, 2);
  
  // Init. and start BLE library.
  ble_begin();
  
  // Enable serial debug
  Serial.begin(57600);
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  
  pinMode(DIGITAL_OUT_PIN, OUTPUT);
  pinMode(DIGITAL_IN_PIN, INPUT);
  
  // Default to internally pull high, change it if you need
  digitalWrite(DIGITAL_IN_PIN, HIGH);
    
  Serial.println("Senti8 command module initiated.");
}

void loop()
{
  static byte old_state = LOW;
  
  // If data is ready
  while(ble_available())
  {
    // read out command and data
    byte data0 = ble_read();
    byte data1 = ble_read();
    byte data2 = ble_read();
    
    bool shouldForwardCommand = false;
    
    if (data0 == 0x04)  // command is to reset.
    {
      digitalWrite(DIGITAL_OUT_PIN, LOW);
    }
    else if(data0 == 0x10) // emit scent command
    {
      shouldForwardCommand = true;
      Serial.print("emit scent command received: ");
      Serial.println(data1, HEX);
      blink(data1);
    }
    else if(data0 == 0x1a)  // scent selected command
    {
      shouldForwardCommand = true;
      Serial.print("scent selected command received: ");
      Serial.println(data1, HEX);
      blink(data1);
    }
    
    if(shouldForwardCommand = true) {
      Serial.println("forwarding command to software serial...");
      // just pass the bytes forward:
      mySerial.write(data0);
      mySerial.write(data1);
      mySerial.write(data2);
    }
  }
  
  // if there is data arriving from the device,
  // forward to BLE.
  if(mySerial.available()) {
    Serial.println("forwarding device command to BLE...");
    while(mySerial.available() > 0) {
      ble_write(mySerial.read()); 
    }
  }
  
  if (!ble_connected())
  {
    digitalWrite(DIGITAL_OUT_PIN, LOW);
  }
  
  // Allow BLE Shield to send/receive data
  ble_do_events();  
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



