#include "Hardware.h"

Hardware::Hardware() {

}

Hardware::Hardware(int S0, int S1, int S2, int S3, int Out, int capturePushButton,int calibratePushButton_BLACK, int calibratePushButton_WHITE) {
  this->colorSensor = ColorSensor(S0, S1, S2, S3, Out);
  this->capturePushButton = PushButton(capturePushButton);
  this->calibratePushButton_BLACK = PushButton(calibratePushButton_BLACK);
  this->calibratePushButton_WHITE = PushButton(calibratePushButton_WHITE);
}

void Hardware::begin() {
  colorSensor.begin();
  capturePushButton.begin();
  calibratePushButton_BLACK.begin();
  calibratePushButton_WHITE.begin();
}

void Hardware::begin(int S0, int S1, int S2, int S3, int Out, int capturePushButton,int calibratePushButton_BLACK, int calibratePushButton_WHITE) {
  this->colorSensor = ColorSensor(S0, S1, S2, S3, Out);
  this->capturePushButton = PushButton(capturePushButton);
  this->calibratePushButton_BLACK = PushButton(calibratePushButton_BLACK);
  this->calibratePushButton_WHITE = PushButton(calibratePushButton_WHITE);

  this->colorSensor.begin();
  this->capturePushButton.begin();
  this->calibratePushButton_BLACK.begin();
  this->calibratePushButton_WHITE.begin();
}

bool Hardware::capture() {
  if (capturePushButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      colorSensor.read();
      if (colorSensor.R >= 0 && colorSensor.G >= 0 && colorSensor.B >= 0) break;
      delay(ITER_DELAY);
    }
  }
  delay(DEBOUNCING_DELAY);
  return true;
}

bool Hardware::calibrate_BLACK() {
  colorSensor.R_min = MAX;
  colorSensor.G_min = MAX;
  colorSensor.B_min = MAX;

  if (calibratePushButton_BLACK.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      colorSensor.read();
      if (colorSensor.R<colorSensor.R_min) {
        colorSensor.R_min = colorSensor.R;
      }
      if (colorSensor.G<colorSensor.G_min) {
        colorSensor.G_min = colorSensor.G;
      }
      if (colorSensor.B<colorSensor.B) {
        colorSensor.B_min = colorSensor.B;
      }
      delay(ITER_DELAY);
    }
  }

  delay(DEBOUNCING_DELAY);
  return true;
}

bool Hardware::calibrate_WHITE() {
  colorSensor.R_max = MIN;
  colorSensor.G_max = MIN;
  colorSensor.B_max = MIN;

  if (calibratePushButton_BLACK.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      colorSensor.read();
      if (colorSensor.R>colorSensor.R_max) {
        colorSensor.R_max = colorSensor.R;
      }
      if (colorSensor.G>colorSensor.G_max) {
        colorSensor.G_max = colorSensor.G;
      }
      if (colorSensor.B>colorSensor.B) {
        colorSensor.B_max = colorSensor.B;
      }
      delay(ITER_DELAY);
    }
  }

  delay(DEBOUNCING_DELAY);
  return true;
}

String Hardware::RGB() {
  return colorSensor.RGB();
}