#include <FastLED.h>

const int NUM_LEDS = 300;
CRGB bigLED[NUM_LEDS];
const int ledPin = 8;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, ledPin, GRB>(bigLED, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:
    //CRGB color = CRGB(0,255,0);
    CRGB color = CRGB(random(255),random(255),random(255));
    for(int i = 0;  i < NUM_LEDS; i++){
      bigLED[i] = color;
    }
    delay(1000);
    FastLED.show(); // this updates the board

    

}
