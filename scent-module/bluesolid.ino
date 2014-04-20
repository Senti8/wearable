////bluechase implements a blue solid pattern in 6 neopixels
void bluesolid(uint8_t wait) {
  uint16_t i, j;

  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.setPixelColor(1, strip.Color(0, 0, 255));
  strip.setPixelColor(2, strip.Color(0, 0, 255));
  strip.setPixelColor(3, strip.Color(0, 0, 255));
  strip.setPixelColor(4, strip.Color(0, 0, 255));
  strip.setPixelColor(5, strip.Color(0, 0, 255));
  strip.show();
  delay(wait);
 
}
