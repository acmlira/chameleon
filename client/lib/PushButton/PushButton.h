#include "Arduino.h"

class PushButton {
private:
  int pin;
public:
  PushButton();
  PushButton(int pin);

  void begin();

  bool pressed();
};