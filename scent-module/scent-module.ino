// neopixel_cuff is used to configure the light sequence for the Senti8 band
// This code was developed as part of the 2014 NASA SpaceApps Competition, NYC USA.
// Learn more about Senti8 project at http://www.senti8.com 
// This portion of code was written by J. Brooks Zurn and modified from 
// Strandtest sample code from Adafruit Neopixel library.
// Additions to support serial communication by Robert Carlsen.


#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

// change these to use available pins
SoftwareSerial deviceSerial(9,10); // RX, TX

typedef enum {
    ScentTypeNotSet = 0,
    ScentTypeSoil,
    ScentTypeHome,
    ScentTypeFood,
    ScentTypeNature,
    ScentTypeSpace,
    ScentTypeFire
} ScentType;

#define PIN 6
#define NUMLEDS 6  //number of neopixel LEDs
#define LED_PIN 7  // debugging pin

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

// prototypes
void blink(uint8_t count);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  // set the data rate for the SoftwareSerial port
  deviceSerial.begin(4800);
}

void loop() {
  
  ScentType scentType = ScentTypeNotSet;
  while(deviceSerial.available() > 0) {
    // read out command and data
    byte data0 = deviceSerial.read();
    byte data1 = deviceSerial.read();
    byte data2 = deviceSerial.read();
    
    if(data0 == 0x10) // emit scent command
    {
      scentType = (ScentType)data1;
      //blink(data1);
    }
    else if(data0 == 0x1a)  // scent selected command (not used)
    {
      scentType = (ScentType)data1;
      //blink(data1);
    }
  } 
  
  int mainwait=5000;
  
  // if we got a scent command...
  // ...then change the display
  // order: blue, green, violet, yellow, orange, red
  
  if(scentType != ScentTypeNotSet) {
    switch(scentType){
      case ScentTypeSoil:
        ledonoff(0,0,1,0,0,0,mainwait);
        break;
      
      case ScentTypeHome:
        ledonoff(0,0,0,1,0,0,mainwait);
        break;
      
      case ScentTypeFood:
        ledonoff(0,0,0,0,1,0,mainwait);
        break;
      
      case ScentTypeNature:
        ledonoff(0,1,0,0,0,0,mainwait);
        break;
      
      case ScentTypeSpace:
        ledonoff(1,0,0,0,0,0,mainwait);
        break;
        
      case ScentTypeFire:
        ledonoff(1,1,1,1,1,1,mainwait);
        break;
    }
    
    delay(mainwait*1.5);
  }
  
  // "attract" loop...chase while no commands received.
  bluechase(mainwait); //delay(mainwait/5);
  
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



