# SevenSeg
Arduino class for managing 4-digit seven segment displays (designed for display with model number 5641AH, but any multiplexed 4-digit display should work as well) using two 595 Shift Registers.

## Installation
First, follow instructions to install the required [ShiftReg](https://github.com/CSchank/ShiftReg) class into your sketch folder.

Then, place [SevenSeg.h](SevenSeg.h) and [SevenSeg.cpp](SevenSeg.cpp) in the folder of your Arduino sketch. In the sketch, place an include at the top:
```arduino
#include "SevenSeg.h"
```
Then, instantiate the object and call init() from your setup() function. init() takes 3 arguments:

1. Arduino pin attached to clock pin.
2. Arduino pin attached to data pin.
3. Arduino pin attached to latch pin.

Also, you should call update() in your loop() function to render the digits. Because it's multiplexed, you'll need to call this several times per second to see the output.
```arduino
SevenSeg display;

void setup() {
  display.init(12,11,8);
}

void loop(){
  //choose what to display
  display.update(); //render the display
}
```
Now, you can call the various functions to display numbers on the screen, including helper functions for integers and floats. You can also feed it custom 7-segment characters.

See [SevenSeg.ino](https://github.com/CSchank/SevenSeg/blob/master/SevenSeg.ino) for a full example.

##License
This class is released under the [Creative Commons Attribution-ShareAlike CC BY-SA License](https://creativecommons.org/licenses/by-sa/4.0/deed.en).
