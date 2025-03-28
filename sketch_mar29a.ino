#include <Adafruit_NeoPixel.h>

#define PIR_PIN 2         // PIR sensor pin
#define LED_PIN 6         // RGB strip DIN pin
#define NUM_LEDS 72       // LED strip 72 LEDs

// NeoPixel object
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
  pinMode(PIR_PIN, INPUT);      // PIR sensor input set
  strip.begin();                // Strip initialize
  strip.setBrightness(255);     // Brightness full (255)
  strip.show();                 // strip off
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) { // if Motion detect
    danceColors();                    // colors effect
    clearStrip();                     // After Effect strip off
    delay(100);                       
  } else {
    clearStrip();                     // No motion, strip off
  }
}

// colors effect function
void danceColors() {
  int delayTime = 9500 / NUM_LEDS; // 6.5 seconds LEDs (~90ms per LED)
  
  for (int i = 0; i < NUM_LEDS; i++) {
  
    int colorIndex = random(numColors); // Random color
    strip.setPixelColor(i, colors[colorIndex]);
    
    if (i > 0) {
      strip.setPixelColor(i - 1, strip.Color(0, 0, 0));
    }
    
    strip.show();
    delay(delayTime); // Speed control (6.5 seconds total)
  }
  
  for (int j = 0; j < 2; j++) { // 2 flash
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
