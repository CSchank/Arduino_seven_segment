#include "Arduino.h"
#include "SevenSeg.h"

SevenSeg::SevenSeg() {

}

SevenSeg::init(int clockPin, int dataPin, int latchPin) {
  _sr.init(2, clockPin, dataPin, latchPin);
  Serial.begin(9600);
}

void SevenSeg::displayInt(int n, leadType l) {
  int dig[4];
  splitDig(n, dig);
  bool dec[4] = {0, 0, 0, 0};
  convertDisp(dig, dec, l);
}

void SevenSeg::displayFloat(float n, int pre, leadType l) {
  bool dec[4] = {0, 0, 0, 0};
  int nint;
  if (n > 1000) {
    pre = 0;
  } else if (n > 100) {
    if (pre > 1) {
      pre = 1;
    }
  } else if (n > 10) {
    if (pre > 2) {
      pre = 2;
    }
  } else {
    if (pre > 3) {
      pre = 3;
    }
  }
  nint = round(n * pow(10, pre));
  dec[3 - pre] = 1; //put decimal in right place
  int digs[4];
  splitDig(nint, digs);
  convertDisp(digs, dec, l);
}

void SevenSeg::splitDig(int n, int digs[]) {
  int tens = 1000;
  for (int i = 0; i < 4; i++) {
    digs[i] = n / tens;
    n -= tens * digs[i];
    tens /= 10;
  }
}

void SevenSeg::convertDisp(int digs[4], bool dec[4], leadType l) {
  byte tempState;
  bool firstDig = 0;
  for (int i = 0; i < 4; i++) {
    //if you come across the first non-zero digit, remember that.
    if ((digs[i] != 0) && (!firstDig)) {
      firstDig = 1;
      tempState = _nums[digs[i]];
      //if you have a 0 as the final number, show the zero
    } else if ((digs[i] == 0) && (i == 3)) {
      tempState = _nums[0];
      //if the digit is 0 and we haven't seen a first digit yet, show what we choose
    } else if ((digs[i] == 0) && (!firstDig)) {
      switch (l) {
        case ZEROS:
          tempState = _nums[0];
          break;
        case BLANK:
          tempState = 0;
          break;
      }
      //or else, show the number as expected
    } else {
      tempState = _nums[digs[i]];
    }
    _state[i] = tempState + _dec * dec[i];
  }
}

void SevenSeg::displayCustom(byte bytes[4]) {
  for (int i = 0; i < 4; i++) {
    _state[i] = bytes[i];
  }
}

void SevenSeg::update() {
  for (int i = 0; i < 4; i++) {
    byte temp[2] = {_state[3-i], _digits[i]};
    _sr.setPByte(temp);
  }
}
