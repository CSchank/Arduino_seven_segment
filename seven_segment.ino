const int clockPin =  12;
const int latchPin = 8;
const int dataPin = 11;
const int numSR = 2;
const byte decimal = B10000000;

const byte nums[10] = {B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111101, B00000111, B01111111, B01101111};
const byte digits[5] = {B00001101, B00001011, B00001110, B00000111, B00000000};

byte disp[numSR] = {digits[4],nums[1]};
void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  float reading = analogRead(A1)*5000.0/1024;
  displayInt(reading/10);
}

void displayInt(int input) {
  int dig[4] = {0, 0, 0, 0};
  int tens = 1000;
  byte newDisp[2];
  bool firstDig = 0;
  for(int i = 0; i < 4; i++) {
    dig[i] = input / tens;
    input -= tens*dig[i];
    if ((dig[i] != 0) && (!firstDig)) {
      firstDig = 1;
      newDisp[1] = nums[dig[i]];
    } else if ((dig[i] == 0) && (i == 3)) {
      newDisp[1] = nums[0];
    } else if ((dig[i] == 0) && (!firstDig)) {
      newDisp[1] = 0;
    } else {
      newDisp[1] = nums[dig[i]];
    }
    newDisp[0] = digits[i];
    tens/=10;
    shiftHelper(newDisp);
  }
}

void displayFloat(float input, int precision) {
  if (input > 999) { //1000-9999
    displayInt(int(input)); //if it's greater than 999, then just display using the Integers.
  } else if (input > 99) { //100-999
    
  } else if (input > 9) { //10-99
    
  } else {//1-10
    
  }
}

//shift out to register helper
void shiftHelper(byte input[numSR]) {
  digitalWrite(latchPin, 0);
  for (int i = 0; i < numSR; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, input[i]);
  }
  digitalWrite(latchPin, 1);
}
