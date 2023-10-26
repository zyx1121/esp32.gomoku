#ifndef BUTTON_H_
#define BUTTON_H_

const uint8_t btnsData[4] = {36, 39, 34, 35};

const uint8_t ic74147[9][4] = {
  {0, 1, 1, 1},
  {1, 0, 1, 1},
  {0, 0, 1, 1},
  {1, 1, 0, 1},
  {0, 1, 0, 1},
  {1, 0, 0, 1},
  {0, 0, 0, 1},
  {1, 1, 1, 0},
  {0, 1, 1, 0},
};

typedef struct button_s {
  bool data;
	uint8_t status;
  uint16_t time;
}button_t;

enum buttonStatus_e {
	idle,
	pressed,
	holding,
	released
};

volatile button_t button[9];

void SetupButton() {
  uint8_t i;
  for(i = 0; i < 4; i++) pinMode(btnsData[i], INPUT);
}

void Button(void) {
	uint8_t i, j, check;
  for(i = 0; i < 9; i++) {
    check = 0;
    for(j = 0; j < 4; j++) {
      if(digitalRead(btnsData[j]) == ic74147[i][j]) check++; else break;
    }
    if(check == 4) button[i].data = true; else button[i].data = false;

    switch(button[i].status) {
      case idle:
        if(button[i].data == true) button[i].status = pressed;
        break;
      case pressed:
        button[i].status = holding;
        break;
      case holding:
        if(button[i].data == false) button[i].status = released;
        //else if(button[i].time < 5000) button[i].time++;
        break;
      case released:
        button[i].status = idle;
        break;
    }

  }
}

#endif
