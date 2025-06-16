#ifndef SCANNER_H
#define SCANNER_H

#ifndef SCANNER_DATA_PIN
#error "SCANNER_DATA_PIN must be defined before including Scanner.h"
#endif // SCANNER_DATA_PIN

#include <FastLED.h>
#include "Buffer.h"

#define RED_MEDUIM CRGB(8, 0, 0)
#define RED_DIM CRGB(1, 0, 0)

class Scanner
{
public:
  Scanner(int led_count);
  void update();
  ~Scanner();

private:
  int LED_count;
  int index = 0;
  int dir = 1;
  int scanInterval; // in milliseconds
  unsigned long lastUpdate = 0;

  CRGB *leds;
  Buffer refs = Buffer(4);
};

Scanner::Scanner(int LED_count)
    : LED_count(LED_count)
{
  leds = new CRGB[LED_count]; // allocate memory
  index = 0;
  dir = 1;

  FastLED.addLeds<NEOPIXEL, SCANNER_DATA_PIN>(leds, LED_count);
}

void Scanner::update()
{
  if (index == LED_count - 1)
    dir = -1;
  else if (index == 0)
    dir = 1;

  refs.add(index);

  leds[refs.get(3)] = CRGB::Black; // turn off the next LED
  leds[refs.get(2)] = RED_DIM;     // very dim previous LED
  leds[refs.get(1)] = RED_MEDUIM;  // dim previous LED
  leds[refs.get(0)] = CRGB::Red;   // turn off previous LED

  index += dir;
  FastLED.show();
  delay(100);
}

Scanner::~Scanner() { delete[] leds; }

#endif // SCANNER_H
