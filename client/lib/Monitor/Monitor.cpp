#include "Monitor.h"

Monitor::Monitor() {}

void Monitor::begin(int baudrate) {
  Serial.begin(baudrate);
  delay(BEGIN_DELAY);
}

void Monitor::print(const String &string) {
  Serial.println(string);
}