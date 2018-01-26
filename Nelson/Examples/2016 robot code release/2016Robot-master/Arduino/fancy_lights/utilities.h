
void fillStrip(uint32_t c, uint8_t brightness) {
  uint8_t r = (uint8_t)(c >> 16);
  uint8_t g = (uint8_t)(c >>  8);
  uint8_t b = (uint8_t)c;
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, (r * brightness / 255), (g * brightness / 255), (b * brightness / 255));
  } 
  //
 // strip.show();
}

void fillStripZ(uint32_t c, uint8_t brightness) {
  uint8_t r = (uint8_t)(c >> 16);
  uint8_t g = (uint8_t)(c >>  8);
  uint8_t b = (uint8_t)c;
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    stripz.setPixelColor(i, (r * brightness / 255), (g * brightness / 255), (b * brightness / 255));
  } 
  //
 // strip.show();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
