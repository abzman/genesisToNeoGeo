/*
  Example for the RoxTCA9548A library

  The TCA9548A is an i2c multiplexer, it's used when you have multiple modules
  all with the same i2c address or when the module has limited address selection.

  Some i2c devices have a single fixed address or 2 addresses to select from,
  like in the case of some OLED displays, if you want to have more modules
  separately then you can use an i2c multiplexer like the TCA9548A.

  Many modules will have a 3 bit address giving you up to 8 independent devices
  like the MCP23017, using a multiplexer can increase the number of these devices.
  The MCP23017 gives you 16 IO pins, if you have 8 of them then you'd have 128 IO Pins,
  but by using just one TCA9548A you can have a total 1,024 IO pins! if you use
  use 8 TCA9548A's then you can have a theoretical 8,192 IO pins!

  Happy Coding!
*/

#include <RoxMux.h>

// the number "1" specifies how many TCA9548As are to be used
RoxTCA9548A <1> mux;

void setup(){
  // begin the wire library, the argument in the begin method specifies the clock speed
  // true = 400,000 bit/s
  // false = 100,000 bit/s
  mux.begin(true);
  // set the address of each TCA9548A, in this example we only have one
  // the first argument is the index of the TCA9548A and the second argument
  // is the address
  mux.setAddress(0, 0x70);

  // add a short delay
  delay(100);

  // select i2c port 0
  mux.select(0);
  // do something on port 0

  // select i2c port 3
  mux.select(3);
  // do something on port 3

  // go back to i2c port 0
  mux.select(0);
}

void loop(){

}
