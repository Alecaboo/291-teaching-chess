#include <FastLED.h>

const int NUM_LEDS = 300;
CRGB bigLED[NUM_LEDS];
const int ledPin = 8;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, ledPin, GRB>(bigLED, 300);

}

void loop() {
  // put your main code here, to run repeatedly:
    CRGB color = CHSV(255,0,0);
      for (int i = 0; i < 5; i++){
        
        bigLED[i] = color;

      }
    FastLED.show(); // this updates the board

    

}
