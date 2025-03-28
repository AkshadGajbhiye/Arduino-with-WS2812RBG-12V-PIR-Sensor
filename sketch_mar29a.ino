#include <Adafruit_NeoPixel.h>

#define PIR_PIN 2         // PIR sensor ka pin
#define LED_PIN 6         // RGB strip ka DIN pin
#define NUM_LEDS 72       // LED strip mein 72 LEDs

// NeoPixel object banayein
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Attractive colors array (RGB values)
uint32_t colors[] = {
  strip.Color(255, 0, 0),    // Vibrant Red
  strip.Color(0, 255, 255),  // Cyan
  strip.Color(255, 0, 255),  // Magenta
  strip.Color(255, 255, 0),  // Yellow
  strip.Color(128, 0, 255)   // Purple
};
int numColors = 5;           // Total colors in array

void setup() {
  pinMode(PIR_PIN, INPUT);      // PIR sensor ko input set karein
  strip.begin();                // Strip initialize karein
  strip.setBrightness(255);     // Brightness full (255)
  strip.show();                 // Shuru mein strip off karein
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) { // Motion detect hua
    danceColors();                    // Dancing colors effect chalayein
    clearStrip();                     // Effect ke baad strip off karein
    delay(100);                       // Thodi der wait karein next trigger se pehle
  } else {
    clearStrip();                     // No motion, strip off rakhein
  }
}

// Dancing colors effect function
void danceColors() {
  int delayTime = 9500 / NUM_LEDS; // 6.5 seconds ko LEDs ke beech divide karein (~90ms per LED)
  
  for (int i = 0; i < NUM_LEDS; i++) {
    // Har LED ko ek random attractive color se set karein
    int colorIndex = random(numColors); // Random color chunein
    strip.setPixelColor(i, colors[colorIndex]);
    
    // Peeche wali LED ko fade effect ke saath off karein
    if (i > 0) {
      strip.setPixelColor(i - 1, strip.Color(0, 0, 0));
    }
    
    strip.show();
    delay(delayTime); // Speed control karein (6.5 seconds total)
  }
  
  // Last LED tak pahunchne ke baad ek final flash
  for (int j = 0; j < 2; j++) { // 2 baar flash
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, colors[j % numColors]);
    }
    strip.show();
    delay(600);
    clearStrip();
    delay(600);
  }
}

// Function to clear the strip
void clearStrip() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}