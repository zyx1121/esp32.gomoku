#ifndef GOMOKU_H
#define GOMOKU_H
#include "display.h"
#include "button.h"
#include "timer.h"

typedef struct gomoku_s {
	uint8_t selLoc[2]; // Select Location
  uint8_t board[16][16];
  uint8_t stone;
}gomoku_t;

volatile gomoku_t gomoku;

void SetupGomoku() {
  uint8_t i, j;
  for(i = 0; i < 16; i++) {
    for(j = 0; j < 16; j++) {
      displayBuffer[i][j] = blank;
      gomoku.board[i][j] = blank;
    }
  }
  for(i = 0; i < 2; i++) gomoku.selLoc[i] = 8;

  gomoku.board[7][7] = red;
  gomoku.stone = green;
  
  displayBuffer[7][7] = red;
}

void GomokuSelect_GetNew() {
  int8_t y = gomoku.selLoc[0];
  int8_t x = gomoku.selLoc[1];
  uint8_t i, j, k;
  bool check = false;
  for(i = 1; i < 16; i++) {
    for(j = 0; j < 2; j++) {
      for(k = 0; k < i; k++) {
        if(i % 2 == 1) {
          if(j == 0) {if(y - 1 >= 0) {if(gomoku.board[--y][x] == blank) check = true;}}
          else {if(x + 1 <= 15) {if(gomoku.board[y][++x] == blank) check = true;}}
        }else{
          if(j == 0) {if(y + 1 <= 15) {if(gomoku.board[++y][x] == blank) check = true;}}
          else {if(x - 1 >= 0) {if(gomoku.board[y][--x] == blank) check = true;}}
        }
        if(check) break;
      }
      if(check) break;
    }
    if(check) {
      gomoku.selLoc[0] = y;
      gomoku.selLoc[1] = x;
      break;
    }
  }
}

void GomokuJudgment() {
  int8_t y = gomoku.selLoc[0];
  int8_t x = gomoku.selLoc[1];
  uint8_t num;
  uint8_t i, j;
  for(i = 0; i < 4; i++) {
    j = 1;
    num = 0;
    switch(i) {
      case 0: {
        while(gomoku.board[y + j][x] == gomoku.stone) num++;
        while(gomoku.board[y - j][x] == gomoku.stone) num++;
        break;
      }
      case 1: {
        while(gomoku.board[y + j][x + j] == gomoku.stone) num++;
        while(gomoku.board[y - j][x - j] == gomoku.stone) num++;
        break;
      }
      case 2: {
        while(gomoku.board[y][x + j] == gomoku.stone) num++;
        while(gomoku.board[y][x - j] == gomoku.stone) num++;
        break;
      }
      case 3: {
        while(gomoku.board[y + j][x - j] == gomoku.stone) num++;
        while(gomoku.board[y - j][x + j] == gomoku.stone) num++;
        break;
      }
    }
    if(num == 4) {
      SetupGomoku();
      break;
    }else{
      if(gomoku.stone == red) gomoku.stone = green; else gomoku.stone = red;
      GomokuSelect_GetNew();
    }
  }
}

void GomokuSelect(uint8_t btn) {
  int8_t y = gomoku.selLoc[0];
  int8_t x = gomoku.selLoc[1];
  uint8_t i;
  if(button[btn].status == pressed) {
    displayBuffer[gomoku.selLoc[0]][gomoku.selLoc[1]] = blank;
    switch(btn) {
      case 0:
        for(i = 1; i < 16; i++) if(y + i <= 15 && x - i >= 0) if(gomoku.board[y + i][x - i] == blank) {gomoku.selLoc[0] += i; gomoku.selLoc[1] -= i; break;}
        break;
      case 1:
        for(i = 1; i < 16; i++) if(y + i <= 15) if(gomoku.board[y + i][x] == blank) {gomoku.selLoc[0] += i; break;}
        break;
      case 2:
        for(i = 1; i < 16; i++) if(y + i <= 15 && x + i <= 15) if(gomoku.board[y + i][x + i] == blank) {gomoku.selLoc[0] += i; gomoku.selLoc[1] += i; break;}
        break;
      case 3:
        for(i = 1; i < 16; i++) if(x - i >= 0) if(gomoku.board[y][x - i] == blank) {gomoku.selLoc[1] -= i; break;}
        break;
      case 4:
        displayBuffer[y][x] = gomoku.stone;
        gomoku.board[y][x] = gomoku.stone;
        GomokuJudgment();
        break;
      case 5:
        for(i = 1; i < 16; i++) if(x + i <= 15) if(gomoku.board[y][x + i] == blank) {gomoku.selLoc[1] += i; break;}
        break;
      case 6:
        for(i = 1; i < 16; i++) if(y - i >= 0 && x - i >= 0) if(gomoku.board[y - i][x - i] == blank) {gomoku.selLoc[0] -= i; gomoku.selLoc[1] -= i; break;}
        break;
      case 7:
        for(i = 1; i < 16; i++) if(y - i >= 0) if(gomoku.board[y - i][x] == blank) {gomoku.selLoc[0] -= i; break;}
        break;
      case 8:
        for(i = 1; i < 16; i++) if(y - i >= 0 && x + i <= 15) if(gomoku.board[y - i][x + i] == blank) {gomoku.selLoc[0] -= i; gomoku.selLoc[1] += i; break;}
        break;
    }
  }
}

void Gomoku() {
  if(timeFlag.quarter == 0) displayBuffer[gomoku.selLoc[0]][gomoku.selLoc[1]] = gomoku.stone;
  else displayBuffer[gomoku.selLoc[0]][gomoku.selLoc[1]] = blank;

  uint8_t i;
  for(i = 0; i < 9; i++) GomokuSelect(i);
}

#endif
