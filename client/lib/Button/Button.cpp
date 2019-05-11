#include "Button.h"

Button::Button() {
  
}

Button::Button(int pin) {
  this->pin = pin;
}

void Button::begin() {
  pinMode(pin, INPUT);
}

bool Button::pressed() {
  if (digitalRead(pin) == HIGH) {
    return true;
  }
  return false;
}