#include <stdint.h>

#include "display.h"
#include "button.h"
#include "timer.h"
#include "espwifi.h"

#include "gomoku.h"

void setup() {
  //SetupWiFi();
  SetupDisplay();
  SetupButton();
  SetupTimer();
  SetupGomoku();
}

void loop() {
  if(timeFlag.milli) {
    Button();
    Gomoku();
    timeFlag.milli = false;
  }
}
