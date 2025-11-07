// Include the Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Define the GPIO pin connected to the NeoPixel data line
#define LED_PIN 27

// Define the number of NeoPixels in the strip/chain
#define NUM_LEDS 1

// Create a NeoPixel object
// Parameter 1: Number of LEDs in the strip
// Parameter 2: GPIO pin number
// Parameter 3: Pixel type flags. NEO_GRB + NEO_KHZ800 is common for WS2812B
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialize the NeoPixel library
  pixels.setBrightness(10); // Set brightness to 10 (out of 255)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();  // Send the updated colors to the strip (all off)
}

void loop() {
  // --- Set color to RED ---
  // Set the first pixel (index 0) to Red
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show(); // Send the color to the LED
  delay(1000);   // Wait for 1 second

  // --- Set color to GREEN ---
  // Set the first pixel (index 0) to Green
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show(); // Send the color to the LED
  delay(1000);   // Wait for 1 second

  // --- Set color to BLUE ---
  // Set the first pixel (index 0) to Blue
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show(); // Send the color to the LED
  delay(1000);   // Wait for 1 second

  // --- Set color to WHITE ---
  // Set the first pixel (index 0) to White
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  pixels.show(); // Send the color to the LED
  delay(1000);   // Wait for 1 second
}
