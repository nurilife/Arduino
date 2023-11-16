#include <LedControl.h>

// Pin configuration for the LED matrix
const int DIN_PIN = 12;  // Data input pin
const int CLK_PIN = 11;  // Clock pin
const int CS_PIN = 10;   // Chip select pin
const int NUM_DEVICES = 1; // Number of MAX7219 devices

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NUM_DEVICES);

// Define the characters
byte characters[][8] = {
  { 0b00000000, 0b00110010, 0b01001010, 0b01001010, 0b00110010, 0b01000000, 0b01111110, 0b00000000 },
  { 0b00000000, 0b01110101, 0b00100101, 0b00101101, 0b00100101, 0b01010101, 0b01010101, 0b00000000 },
  {0b00000000, 0b01111110, 0b00000010, 0b00010010, 0b00010010, 0b00010100, 0b01111110, 0b00000000 }
  // Add more characters as needed
};

const int numCharacters = sizeof(characters) / sizeof(characters[0]);

void setup() {
  lc.shutdown(0, false);  // Wake up the MAX7219 devices
  lc.setIntensity(0, 8);  // Set the brightness (0-15)
  lc.clearDisplay(0);     // Clear the display
}

void scrollCharacter(byte character[8], int speed) {
  for (int col = 0; col < 8; col++) {
    for (int row = 0; row <8; row++) {
      lc.setRow(0, row, character[(col + row) % 8]);
    }
    delay(speed);
       
  }
}

void loop() {
  for (int i = 0; i < numCharacters; i++) {
    scrollCharacter(characters[i], 100);  // Adjust the speed as needed
    //delay(100);  // Pause between characters
  }
}
