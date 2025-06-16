#define SCANNER_DATA_PIN 6
#include "Scanner.h"

Scanner scanner(10);

void setup() {}

void loop() { scanner.update(); }
