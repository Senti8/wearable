// SerialReceiveDemo
//
// Copyright 2014 Robert Carlsen. All rights reserved.
// Released under the terms of the Apache 2.0 License.
//
// Created for the Senti8 project as part of the 2014 NASA Spaceapps Challenge.
//
// This sketch simply indicates (via blinking an LED) that the
// Arduino received a valid Senti8 command via serial connection.

#define LED_PIN 13

// prototypes
void blink(uint8_t count);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  while(Serial.available()) {

    blink(1);

    // three byte protocol
    // read out command and data
    byte data0 = Serial.read();
    byte data1 = Serial.read();
    byte data2 = Serial.read();

    if(data0 == 0x10) // emit scent command
    {
      blink(5);
    }
    else if(data0 == 0x1a)  // scent selected command
    {
      // NOP
    }
  }
}

void blink(uint8_t count)
{
  for(int i=0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                    // wait for a bit
    digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
  }
}

