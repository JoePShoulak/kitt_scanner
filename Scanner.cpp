#include "Scanner.h"

#define DATA_PIN 6

Scanner::Scanner(int LED_count, int dataPin)
    : LED_count(LED_count)
{
    leds = new CRGB[LED_count]; // allocate memory
    index = 0;
    dir = 1;

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, LED_count); // FIXME: can't use the dataPin argument for a template?
}

void Scanner::update()
{
    unsigned long now = millis();
    if (now - lastUpdate < scanInterval)
        return;
    lastUpdate = now;

    if (index == LED_count - 1)
        dir = -1;
    else if (index == 0)
        dir = 1;

    if (dir == 1)
    {
        leds[index] = CRGB::Red;
        if (index - 1 >= 0)
            leds[index - 1] = redMedium;
        if (index - 2 >= 0)
            leds[index - 2] = redDim;
        if (index - 3 >= 0)
            leds[index - 3] = CRGB::Black;
    }
    else
    {
        leds[index] = CRGB::Red;
        if (index + 1 < LED_count)
            leds[index + 1] = redMedium;
        if (index + 2 < LED_count)
            leds[index + 2] = redDim;
        if (index + 3 < LED_count)
            leds[index + 3] = CRGB::Black;
    }

    index += dir;
    FastLED.show();
}

Scanner::~Scanner()
{
    delete[] leds;
}
