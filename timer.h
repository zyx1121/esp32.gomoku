#ifndef TIMER_H_
#define TIMER_H_

typedef struct systemTime_s {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint16_t milli;
}systemTime_t;

typedef struct timeFlag_s {
  bool half;
  bool quarter;
  bool eight;
  bool deci;
  bool milli;
}timeFlag_t;

volatile systemTime_t systemTime;

volatile timeFlag_t timeFlag; 

static hw_timer_t * timer = NULL;
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void MilliChanged(void) {
  
  if (++systemTime.milli > 999) {
    systemTime.milli = 0;
    if (++systemTime.second > 59) {
      systemTime.second = 0;
      if (++systemTime.minute > 59) {
        systemTime.minute = 0;
        if (++systemTime.hour > 23) {
          systemTime.hour = 0;
        }
      }
    }
  }
  
  timeFlag.half = ((systemTime.milli / 500) % 2) ? true : false;
  timeFlag.quarter = ((systemTime.milli / 250) % 2) ? true : false;
  timeFlag.eight = ((systemTime.milli / 125) % 2) ? true : false;
  timeFlag.deci = ((systemTime.milli / 100) % 2) ? true : false;
  
}

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  
  static uint8_t i = 0;
  if(++i == 10) {
    MilliChanged();
    timeFlag.milli = true;
    i = 0;
  }
  
  Display();
  
  portEXIT_CRITICAL_ISR(&timerMux);
}

void SetupTimer(void) {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 100, true);
  timerAlarmEnable(timer);
}

#endif
