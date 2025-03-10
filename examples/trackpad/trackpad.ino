/**
 * Reads X/Y values from a PS/2 mouse connected to an Arduino
 * using the PS2Mouse library available from
 *   http://github.com/kristopher/PS2-Mouse-Arduino/
 * Original by Kristopher Chambers <kristopher.chambers@gmail.com>
 * Updated by Jonathan Oxer <jon@oxer.com.au>
 */

#include <PS2Mouse.h>
#define MOUSE_DATA 5 //grijs
#define MOUSE_CLOCK 6 //paars

PS2Mouse mouse(MOUSE_CLOCK, MOUSE_DATA, STREAM);

/**
 * Setup
 */
void setup()
{
  Serial.begin(38400);
  mouse.initialize();
  Serial.print("hello");
}

/**
 * Main program loop
 */
void loop()
{
  int16_t data[3];
  mouse.report(data);
  Serial.print(data[1]); // X Movement Data
  Serial.print(",");
  Serial.print(data[2]); // Y Movement Data

  Serial.println();
}
