#include "LedControl.h"

// Pin configurations for connecting to the LED matrix (adjust as needed)
const int dataPin = 12;
const int clockPin = 11;
const int csPin = 10;

LedControl lc = LedControl(dataPin, clockPin, csPin, 1);

const uint64_t IMAGES[] = {
  0x1c08080808080c08,
  0x3e0408102020221c,
  0x1c2220201820221c,
  0x20203e2224283020,
  0x1c2220201e02023e,
  0x1c2222221e02221c,
  0x040404081020203e,
  0x1c2222221c22221c,
  0x1c22203c2222221c,
  0x1c2222222222221c
};

const int IMAGES_LEN = sizeof(IMAGES) / 8;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop() {
  for (int i = 0; i < 10; ++i) {
    displayNumber(i);
    delay(1000);  // Display each number for 1 second
  }
}

void displayNumber(int num) {
  if (num >= 0 && num <= 9) {
    uint64_t pattern = IMAGES[num];
    displayPattern(pattern);
  }
}

void displayPattern(uint64_t pattern) {
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      bool bit = (pattern >> (8 * row + col)) & 1;
      lc.setLed(0, row, col, bit);
    }
  }
}
