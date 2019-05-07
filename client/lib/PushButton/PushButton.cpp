#include "PushButton.h"

PushButton::PushButton() {
  
}

PushButton::PushButton(int pin) {
  this->pin = pin;
}

void PushButton::begin() {
  pinMode(pin, INPUT);
}

bool PushButton::pressed() {
  if (digitalRead(pin) == HIGH) {
    return true;
  }
  return false;
}