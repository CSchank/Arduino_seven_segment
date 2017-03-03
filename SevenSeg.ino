#include "ShiftReg.h"
#include "SevenSeg.h"

SevenSeg display;

void setup() {
  display.init(12,11,8); //initialize the 4-digit display with clock pin 12, data pin 11 and latch pin 8
}

void loop() {
  float t = ((float)millis())/1000; //get current time in seconds since Arduino reset
  display.displayFloat(t,4,ZEROS); //display the current time on the 4-digit display
  display.update(); //render the screen on each loop
}
