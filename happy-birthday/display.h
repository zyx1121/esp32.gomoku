// _display_h for 4*8*8雙色LED點矩陣

enum color_e {
  blank,
  red,
  green,
};

// 雙色 LED 點矩陣控制腳位
const uint8_t rowData[8] = {32, 33, 25, 26, 27, 14, 12, 13};
const uint8_t rowScan[2] = {5, 18};
const uint8_t colData[4] = {0, 4, 16, 17};
const uint8_t colScan[2] = {15, 2};

// ic74154 真值表
const bool ic74154r[16][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {0, 0, 1, 0},
  {1, 0, 1, 0},
  {0, 1, 1, 0},
  {1, 1, 1, 0},
  {0, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 0, 1},
  {1, 1, 0, 1},
  {0, 0, 1, 1},
  {1, 0, 1, 1},
  {0, 1, 1, 1},
  {1, 1, 1, 1}
};
const bool ic74154g[16][4] = {
  {0, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 0, 1},
  {1, 1, 0, 1},
  {0, 0, 1, 1},
  {1, 0, 1, 1},
  {0, 1, 1, 1},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {0, 0, 1, 0},
  {1, 0, 1, 0},
  {0, 1, 1, 0},
  {1, 1, 1, 0}
};

// 顯示資料緩存
volatile uint8_t display_buffer[16][16];

//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
const uint8_t temp0[16][16] = {
  {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {2,2,2,0,2,2,2,2,0,0,0,2,2,2,2,2},
  {2,2,2,2,0,2,2,2,2,2,2,0,0,0,1,1},
  {2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2},
  {2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
  {2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2},
  {2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2},
  {2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2},
  {2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2},
  {2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2},
  {2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},
};

const uint8_t temp1[9][32] = {
  {0x00,0x00,0x01,0x80,0x01,0x08,0x03,0xFC,0x04,0x10,0x0A,0x20,0x31,0x40,0x01,0x80,0x02,0x04,0x07,0xFE,0x1C,0x04,0x64,0x04,0x04,0x04,0x04,0x04,0x07,0xFC,0x04,0x04}, // 0xA657,"名"
  {0x00,0x00,0x0C,0x46,0x08,0x78,0x7F,0x40,0x08,0x42,0x0F,0x7F,0x78,0x48,0x48,0x88,0x18,0x88,0x09,0x08,0x00,0x00,0x1F,0xF8,0x10,0x08,0x10,0x08,0x1F,0xF8,0x10,0x08}, // 0xADF5,"哲"
  {0x00,0x00,0x00,0xC0,0x0C,0x80,0x08,0x80,0x08,0x84,0x1F,0xFE,0x10,0x80,0x20,0x80,0x40,0x88,0x1F,0xFC,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x82,0x7F,0xFF,0x00,0x00}, // 0xA5CD,"生"
  {0x00,0x00,0x10,0x08,0x1F,0xFC,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x1F,0xF8,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x1F,0xF8,0x10,0x08}, // 0xA4E9,"日"
  {0x00,0x00,0x18,0x60,0x10,0x40,0x10,0x44,0x13,0xFE,0x58,0x44,0x54,0x44,0x54,0x44,0x10,0x44,0x17,0xFF,0x10,0x40,0x10,0x50,0x10,0x88,0x10,0x84,0x11,0x06,0x16,0x02}, // 0xA7D6,"快"
  {0x00,0x00,0x18,0x86,0x11,0x04,0x27,0xE9,0x7A,0x3E,0x13,0xE4,0x2A,0x2A,0x7B,0xFF,0x4A,0x31,0x00,0x80,0x7F,0xFF,0x00,0x80,0x04,0x98,0x08,0x86,0x10,0x83,0x60,0x81}, // 0xBCD6,"樂"
  {0x00,0x00,0x00,0xD0,0x4B,0x94,0x78,0x92,0x48,0x92,0x4B,0xFF,0x48,0x88,0x48,0x88,0x48,0xAB,0x48,0xCA,0x7B,0x8C,0x4A,0x88,0x40,0x95,0x00,0x95,0x03,0xA3,0x01,0x01}, // 0xAE40,"哦"
  {0x00,0x00,0x00,0xD0,0x4B,0x94,0x78,0x92,0x48,0x92,0x4B,0xFF,0x48,0x88,0x48,0x88,0x48,0xAB,0x48,0xCA,0x7B,0x8C,0x4A,0x88,0x40,0x95,0x00,0x95,0x03,0xA3,0x01,0x01}, // 0xAE40,"哦"
  {0x00,0x00,0x00,0xD0,0x4B,0x94,0x78,0x92,0x48,0x92,0x4B,0xFF,0x48,0x88,0x48,0x88,0x48,0xAB,0x48,0xCA,0x7B,0x8C,0x4A,0x88,0x40,0x95,0x00,0x95,0x03,0xA3,0x01,0x01}, // 0xAE40,"哦"
};

const uint8_t temp2[32 * 11] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x2020,"  "
  0x00,0x00,0x08,0x00,0x08,0x40,0x04,0x40,0x04,0x20,0xFE,0x10,0x43,0x28,0x42,0xCE,0x42,0x8A,0x42,0x48,0x42,0x28,0x42,0x18,0x42,0x0C,0xFF,0x08,0x02,0x00,0x00,0x00, // 0xA657,"名"
  0x00,0x00,0x00,0xC8,0x00,0x48,0xF9,0x48,0x4B,0xFE,0x48,0x2A,0x48,0x28,0x4A,0x28,0x49,0x80,0x48,0x7E,0x48,0x24,0x48,0x24,0xFB,0xE4,0x00,0x22,0x00,0x32,0x00,0x20, // 0xADF5,"哲"
  0x00,0x00,0x41,0x00,0x40,0x80,0x42,0x60,0x42,0x3C,0x42,0x24,0x42,0x20,0x42,0x20,0x7F,0xFE,0x42,0x22,0x42,0x20,0x42,0x20,0x43,0x20,0x42,0x30,0x60,0x20,0x40,0x00, // 0xA5CD,"生"
  0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x41,0x04,0x41,0x04,0x41,0x04,0x41,0x04,0x41,0x04,0x41,0x04,0x41,0x04,0x41,0x04,0xFF,0xFE,0x00,0x04,0x00,0x00,0x00,0x00, // 0xA4E9,"日"
  0x00,0x00,0x00,0xE0,0x00,0x00,0xFF,0xFE,0x00,0x22,0x82,0xC0,0x82,0x10,0x42,0x10,0x32,0x10,0x0F,0xFE,0x02,0x12,0x0A,0x10,0x12,0x10,0x63,0xF8,0xC2,0x10,0x02,0x00, // 0xA7D6,"快"
  0x00,0x00,0x85,0x90,0x84,0xD8,0x44,0xB6,0x25,0xD2,0x14,0x08,0x05,0xF8,0x04,0xAC,0xFE,0xAA,0x04,0xA8,0x05,0xF8,0x15,0x90,0x14,0xD8,0x24,0xB6,0x64,0xD2,0xC5,0x88, // 0xBCD6,"樂"
  0x00,0x00,0x1F,0xFC,0x04,0x08,0x04,0x08,0x0F,0xFC,0x00,0x00,0x4C,0x24,0xC4,0x24,0x7F,0xFE,0x02,0x22,0x41,0x20,0x30,0x3E,0x0F,0xE0,0x34,0x24,0x43,0x38,0xF1,0x20, // 0xAE40,"哦"
  0x00,0x00,0x1F,0xFC,0x04,0x08,0x04,0x08,0x0F,0xFC,0x00,0x00,0x4C,0x24,0xC4,0x24,0x7F,0xFE,0x02,0x22,0x41,0x20,0x30,0x3E,0x0F,0xE0,0x34,0x24,0x43,0x38,0xF1,0x20, // 0xAE40,"哦"
  0x00,0x00,0x1F,0xFC,0x04,0x08,0x04,0x08,0x0F,0xFC,0x00,0x00,0x4C,0x24,0xC4,0x24,0x7F,0xFE,0x02,0x22,0x41,0x20,0x30,0x3E,0x0F,0xE0,0x34,0x24,0x43,0x38,0xF1,0x20, // 0xAE40,"哦"
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 0x2020,"  "
};

void ReadBitFor1() {
  uint8_t i, j, k;
  for(i = 0; i < 16; i++) {
    for(j = 0; j < 16; j++) {
      if(j < 8) {
        k = 7 - j;
        if((temp1[0][0 + (2 * i)] >> k) % 2) {
          display_buffer[i][j] = 2;
        }else{
          display_buffer[i][j] = 0;
        }
      }else{
        k = 15 - j;
        if((temp1[0][1 + (2 * i)] >> k) % 2) {
          display_buffer[i][j] = 2;
        }else{
          display_buffer[i][j] = 0;
        }
      }
    }
  }
}

void ReadBitFor2(uint8_t offset) {
  uint8_t t0[8];
  uint8_t t1[8];
  uint8_t i, j, k;
  for(i = 0; i < 16; i++) {
    for(j = 0; j < 8; j++) {
      t0[j] = temp2[0 + (2 * (i + offset))] >> (7 - j);
      t1[j] = temp2[1 + (2 * (i + offset))] >> (7 - j);
    }
    for(j = 0; j < 8; j++) {
      if(t1[7 - j] % 2) display_buffer[j + 0][i] = 1; else display_buffer[j + 0][i] = 0;
      if(t0[7 - j] % 2) display_buffer[j + 8][i] = 1; else display_buffer[j + 8][i] = 0;
    }
  }
}

void SetupDisplayIO() {
	uint8_t i, j;
  for(i = 0; i < 8; i++) pinMode(rowData[i], OUTPUT);
  for(i = 0; i < 2; i++) pinMode(rowScan[i], OUTPUT);
  for(i = 0; i < 4; i++) pinMode(colData[i], OUTPUT);
  for(i = 0; i < 2; i++) pinMode(colScan[i], OUTPUT);
  
  ReadBitFor2(0);

  /*
  for(i = 0; i < 16; i++) {
    for(j = 0; j < 16; j++) {
      display_buffer[i][j] = temp0[i][j];
    }
  }
  */
}

void Display() {
  static uint8_t color = 0;
  static uint8_t column = 0;
  static uint8_t clear = 0;
  uint8_t i;

  if(clear == 0) {
    if(color == 1) {
      for(i = 0; i < 4; i++) digitalWrite(colData[i], ic74154r[column][i]);
      digitalWrite(colScan[0], LOW);
      digitalWrite(colScan[1], HIGH);
    }else{
      for(i = 0; i < 4; i++) digitalWrite(colData[i], ic74154g[column][i]);
      digitalWrite(colScan[0], HIGH);
      digitalWrite(colScan[1], LOW);
    }
    for(i = 0; i < 8; i++) {
      if(display_buffer[i + 0][column] == color) digitalWrite(rowData[i], HIGH);
      else digitalWrite(rowData[i], LOW);
    }
    digitalWrite(rowScan[0], LOW);
    digitalWrite(rowScan[0], HIGH);
    for(i = 0; i < 8; i++) {
      if(display_buffer[i + 8][column] == color) digitalWrite(rowData[i], HIGH);
      else digitalWrite(rowData[i], LOW);
    }      
    digitalWrite(rowScan[1], LOW);
    digitalWrite(rowScan[1], HIGH);
  }else{
    // 清除資料 等待變更掃描線
    for(i = 0; i < 8; i++) digitalWrite(rowData[i], LOW);
    for(i = 0; i < 2; i++) digitalWrite(rowScan[i], LOW);
    for(i = 0; i < 2; i++) digitalWrite(rowScan[i], HIGH);
  }

  if(++clear == 2) {
    clear = 0;
    if(++column == 16) {
      column = 0;
      if(++color == 3) {
        color = 1;
      }
    }
  }
}
