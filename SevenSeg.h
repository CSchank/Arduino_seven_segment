/*
  SevenSeg.h - Class for managing 5641AH 4-digit 7-segment displays using two 595 Shift Registers.
  Dependent on ShiftReg.h.
  Created by Christopher W. Schankula, Feburary 18, 2017.
  Released into the public domain.
*/
#ifndef SevenSeg_h
#define SevenSeg_h

#include "Arduino.h"
#include "ShiftReg.h"

enum leadType {
  ZEROS,
  BLANK
};

class SevenSeg
{
  public:
    SevenSeg();
    init(int clockPin, int dataPin, int latchPin);
    void displayInt(int n, leadType l);
    void displayFloat(float n, int pre, leadType l);
    void displayCustom(byte bytes[4]);
    void update();
  private:
    void convertDisp(int digs[4],bool dec[4], leadType l);
    void splitDig(int n,int *digs);
    const byte _nums[10] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};
    const byte _dec = B00000001;
    const byte _digits[5] = {B01110000, B10110000, B11010000, B11100000, B00000000};
    byte _state[4];
    ShiftReg _sr;
};

#endif
