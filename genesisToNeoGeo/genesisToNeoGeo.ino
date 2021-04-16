// genesisToNeoGeo.ino
// Author: 
//      Evan Allen <abzman2000@gmail.com>
//
// Borrowed largely from...
//
// SegaControllerSerialReader.ino
//
// Author:
//       Jon Thysell <thysell@gmail.com>
//
// Copyright (c) 2017 Jon Thysell <http://jonthysell.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <SegaController.h>
#include <RoxMux.h>
// Controller DB9 pins (looking face-on to the end of the plug):
//
// 5 4 3 2 1
//  9 8 7 6
//
// Connect pin 5 to +5V and pin 8 to GND
// Connect the remaining pins to digital I/O pins (see below)

// Specify the Arduino pins that are connected to
// DB9 Pin 7, DB9 Pin 1, DB9 Pin 2, DB9 Pin 3, DB9 Pin 4, DB9 Pin 6, DB9 Pin 9
SegaController controller(8, 2, 3, 4, 5, 6, 7);
SegaController controller2(A1, 9, 10, 11, 12, 13, A0);

// Controller states
word currentState = 0;
word lastState = 0;
word currentState2 = 0;
word lastState2 = 0;

RoxMCP23018 <0x21> controllerA;
RoxMCP23018 <0x20> controllerB;
void setup()
{
  controllerA.begin(true);
  controllerB.begin(true);
  for (int i = 0; i > 16; i++)
  {
    controllerA.pinMode(i, OUTPUT);
    controllerB.pinMode(i, OUTPUT);
    controllerA.digitalWrite(i, 0);
    controllerB.digitalWrite(i, 0);
  }
  //Serial.begin(115200);
}

void loop()
{
  currentState = controller.getState();
  currentState2 = controller2.getState();
  sendState();
}

void sendState()
{
  // Only report controller state if it's changed
  if (currentState != lastState | currentState2 != lastState2)
  {
    controllerA.digitalWrite(0, (currentState & SC_BTN_UP) ? 0 : 1);
    controllerA.digitalWrite(1, (currentState & SC_BTN_DOWN) ? 0 : 1);
    controllerA.digitalWrite(2, (currentState & SC_BTN_LEFT) ? 0 : 1);
    controllerA.digitalWrite(3, (currentState & SC_BTN_RIGHT) ? 0 : 1);
    controllerA.digitalWrite(4, (currentState & SC_BTN_START) ? 0 : 1);
    controllerA.digitalWrite(5, (currentState & SC_BTN_A) ? 0 : 1);
    controllerA.digitalWrite(6, (currentState & SC_BTN_C) ? 0 : 1);
    controllerA.digitalWrite(7, (currentState & SC_BTN_B) ? 0 : 1);
    controllerA.digitalWrite(8, (currentState & SC_BTN_X) ? 0 : 1);
    controllerA.digitalWrite(9, (currentState & SC_BTN_Y) ? 0 : 1);
    controllerA.digitalWrite(10, (currentState & SC_BTN_Z) ? 0 : 1);
    controllerB.digitalWrite(0, (currentState2 & SC_BTN_UP) ? 0 : 1);
    controllerB.digitalWrite(1, (currentState2 & SC_BTN_DOWN) ? 0 : 1);
    controllerB.digitalWrite(2, (currentState2 & SC_BTN_LEFT) ? 0 : 1);
    controllerB.digitalWrite(3, (currentState2 & SC_BTN_RIGHT) ? 0 : 1);
    controllerB.digitalWrite(4, (currentState2 & SC_BTN_START) ? 0 : 1);
    controllerB.digitalWrite(5, (currentState2 & SC_BTN_A) ? 0 : 1);
    controllerB.digitalWrite(6, (currentState2 & SC_BTN_C) ? 0 : 1);
    controllerB.digitalWrite(7, (currentState2 & SC_BTN_B) ? 0 : 1);
    controllerB.digitalWrite(8, (currentState2 & SC_BTN_X) ? 0 : 1);
    controllerB.digitalWrite(9, (currentState2 & SC_BTN_Y) ? 0 : 1);
    controllerB.digitalWrite(10, (currentState2 & SC_BTN_Z) ? 0 : 1);
    controllerA.update(1);
    controllerB.update(1);
    /*
    Serial.print((currentState & SC_CTL_ON)    ? "+" : "-");
    Serial.print((currentState & SC_BTN_UP)    ? "U" : "0");
    Serial.print((currentState & SC_BTN_DOWN)  ? "D" : "0");
    Serial.print((currentState & SC_BTN_LEFT)  ? "L" : "0");
    Serial.print((currentState & SC_BTN_RIGHT) ? "R" : "0");
    Serial.print((currentState & SC_BTN_START) ? "S" : "0");
    Serial.print((currentState & SC_BTN_A)     ? "A" : "0");
    Serial.print((currentState & SC_BTN_B)     ? "B" : "0");
    Serial.print((currentState & SC_BTN_C)     ? "C" : "0");
    Serial.print((currentState & SC_BTN_X)     ? "X" : "0");
    Serial.print((currentState & SC_BTN_Y)     ? "Y" : "0");
    Serial.print((currentState & SC_BTN_Z)     ? "Z" : "0");
    Serial.print((currentState & SC_BTN_MODE)  ? "M" : "0");
    Serial.print((currentState2 & SC_CTL_ON)    ? "+" : "-");
    Serial.print((currentState2 & SC_BTN_UP)    ? "U" : "0");
    Serial.print((currentState2 & SC_BTN_DOWN)  ? "D" : "0");
    Serial.print((currentState2 & SC_BTN_LEFT)  ? "L" : "0");
    Serial.print((currentState2 & SC_BTN_RIGHT) ? "R" : "0");
    Serial.print((currentState2 & SC_BTN_START) ? "S" : "0");
    Serial.print((currentState2 & SC_BTN_A)     ? "A" : "0");
    Serial.print((currentState2 & SC_BTN_B)     ? "B" : "0");
    Serial.print((currentState2 & SC_BTN_C)     ? "C" : "0");
    Serial.print((currentState2 & SC_BTN_X)     ? "X" : "0");
    Serial.print((currentState2 & SC_BTN_Y)     ? "Y" : "0");
    Serial.print((currentState2 & SC_BTN_Z)     ? "Z" : "0");
    Serial.print((currentState2 & SC_BTN_MODE)  ? "M" : "0");
    Serial.print("\n");
    */
    lastState = currentState;
    lastState2 = currentState2;
  }
}
