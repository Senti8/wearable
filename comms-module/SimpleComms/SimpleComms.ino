// SimpleComms
//
// Copyright 2014 Robert Carlsen. All rights reserved.
// Released under the terms of the Apache 2.0 License.
//
// Created for the Senti8 project as part of the 2014 NASA Spaceapps Challenge.
//
// This sketch acts as a bridge between the RedBear BLE shield and a
// software serial connection, using the hardware serial connection as
// a monitor.
//

#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define LED_PIN    13

void blink(uint8_t count);

void setup()
{
  // Default pins set to 9 and 8 for REQN and RDYN
  // Set your REQN and RDYN here before ble_begin() if you need
  //ble_set_pins(3, 2);

  // Init and start BLE library.
  ble_begin();

  // Enable serial debug
  Serial.begin(57600);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);

  pinMode(LED_PIN, OUTPUT);

  Serial.println("Senti8 command module initiated.");
}

void loop()
{
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
      digitalWrite(LED_PIN, LOW);
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

  // if there is data arriving from the device, forward to BLE.
  if(mySerial.available()) {
    Serial.println("forwarding device command to BLE...");
    while(mySerial.available() > 0) {
      ble_write(mySerial.read());
    }
  }

  if (!ble_connected())
  {
    digitalWrite(LED_PIN, LOW);
  }

  // Allow BLE Shield to send/receive data
  ble_do_events();
}

void blink(uint8_t count)
{
  for(int i=0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                            // wait for a bit
    digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
  }
}



