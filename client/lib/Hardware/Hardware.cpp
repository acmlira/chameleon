#include "Hardware.h"

Hardware::Hardware() {}

void Hardware::begin(int S0, int S1, int S2, int S3, int Out, int capturePushButton,int blackCalibratePushButton, int whiteCalibratePushButton) {
  this->colorSensor = ColorSensor(S0, S1, S2, S3, Out);
  this->capturePushButton = PushButton(capturePushButton);
  this->blackCalibratePushButton = PushButton(blackCalibratePushButton);
  this->whiteCalibratePushButton = PushButton(whiteCalibratePushButton);

  this->colorSensor.begin();
  this->capturePushButton.begin();
  this->blackCalibratePushButton.begin();
  this->whiteCalibratePushButton.begin();
}

void Hardware::capture() {
  if (capturePushButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      colorSensor.read();
      if (colorSensor.R >= 0 && colorSensor.G >= 0 && colorSensor.B >= 0) break;
      delay(ITER_DELAY);
    }
  }
  delay(DEBOUNCING_DELAY);
}

void Hardware::blackCalibrate() {
  colorSensor.R_min = MAX;
  colorSensor.G_min = MAX;
  colorSensor.B_min = MAX;

  if (blackCalibratePushButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      colorSensor.read();
      if (colorSensor.R<colorSensor.R_min) {
        colorSensor.R_min = colorSensor.R;
      }
      if (colorSensor.G<colorSensor.G_min) {
        colorSensor.G_min = colorSensor.G;
      }
      if (colorSensor.B<colorSensor.B_min) {
        colorSensor.B_min = colorSensor.B;
      }
      delay(ITER_DELAY);
    }
  }

  delay(DEBOUNCING_DELAY);
}

void Hardware::whiteCalibrate() {
  colorSensor.R_max = MIN;
  colorSensor.G_max = MIN;
  colorSensor.B_max = MIN;

  if (blackCalibratePushButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      colorSensor.read();
      if (colorSensor.R>colorSensor.R_max) {
        colorSensor.R_max = colorSensor.R;
      }
      if (colorSensor.G>colorSensor.G_max) {
        colorSensor.G_max = colorSensor.G;
      }
      if (colorSensor.B>colorSensor.B_max) {
        colorSensor.B_max = colorSensor.B;
      }
      delay(ITER_DELAY);
    }
  }

  delay(DEBOUNCING_DELAY);
}

String Hardware::RGB() {
  return colorSensor.RGB();
}