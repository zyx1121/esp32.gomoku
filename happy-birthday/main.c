#include <Arduino.h>
#include <stdint.h>
#include <math.h>

#include "display.h"

void setup() {
  SetupDisplayIO();
}

void loop() {
  static uint32_t i = 0;
  static uint8_t j = 0;
  ReadBitFor2(j);
  Display();
  delayMicroseconds(100);
  if(++i == 750) {
    i = 0;
    if(++j == 10 * 16)
      j = 0;
  }
}
