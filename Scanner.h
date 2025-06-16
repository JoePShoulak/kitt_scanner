#ifndef SCANNER_H
#define SCANNER_H

#include <FastLED.h>

class Scanner
{
public:
  Scanner(int led_count, int data_pin, int scan_interval = 100);
  void update();
  ~Scanner();

private:
  int LED_count;
  int index = 0;
  int dir = 1;
  int scanInterval; // in milliseconds
  unsigned long lastUpdate = 0;

  CRGB *leds;
  CRGB redMedium = CRGB(8, 0, 0); // very dim red
  CRGB redDim = CRGB(1, 0, 0);    // barely on red
};

#endif // SCANNER_H
