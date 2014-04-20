/////ledonoff maps 6 neopixels to hard-coded on/off colors
/////LED #1 is blue
/////LED #2 is green
/////LED #3 is purple
/////LED #4 is yellow
/////LED #5 is orange
/////LED #6 is pink

void ledonoff(uint8_t led1, uint8_t led2, uint8_t led3, uint8_t led4, uint8_t led5, uint8_t led6, uint8_t wait) {
//led #1

if(led1){
  strip.setPixelColor(0, strip.Color(0, 0, 255));  //blue #1
}else{
 strip.setPixelColor(0, strip.Color(0, 0, 0));  //else off
} 
  
//led #2
if(led2){
  strip.setPixelColor(1, strip.Color(0, 255, 0));  //green #2
}else{
 strip.setPixelColor(1, strip.Color(0, 0, 0));  //else off
} 

//led #3
if(led3){
  strip.setPixelColor(2, strip.Color(175, 0, 200));  //purple #3
}else{
 strip.setPixelColor(2, strip.Color(0, 0, 0));  //else off
} 


//led #4
if(led4){
  strip.setPixelColor(3, strip.Color(255, 255, 0));  //yellow #4
}else{
 strip.setPixelColor(3, strip.Color(0, 0, 0));  //else off
} 


//led #5
if(led5){
  strip.setPixelColor(4, strip.Color(255, 50, 0));  //orange #5
}else{
 strip.setPixelColor(4, strip.Color(0, 0, 0));  //else off
} 

//led #6
if(led6){
  strip.setPixelColor(5, strip.Color(255, 48, 48));  //hot pink #6
}else{
 strip.setPixelColor(5, strip.Color(0, 0, 0));  //else off
} 


///at very end, show the colors
  strip.show();
  delay(wait);

  
  
  
}
