#include "Hardware.h"

Hardware::Hardware() {}

void Hardware::begin(int S0, int S1, int S2, int S3, int Out, int captureButton,int blackCalibrateButton, int whiteCalibrateButton) {
  this->tcs230 = TCS230(S0, S1, S2, S3, Out);
  this->captureButton = Button(captureButton);
  this->blackCalibrateButton = Button(blackCalibrateButton);
  this->whiteCalibrateButton = Button(whiteCalibrateButton);

  this->tcs230.begin();
  this->captureButton.begin();
  this->blackCalibrateButton.begin();
  this->whiteCalibrateButton.begin();
}

String Hardware::capture() {
  if (captureButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      tcs230.read();
      if (tcs230.R >= 0 && tcs230.G >= 0 && tcs230.B >= 0) break;
      delay(ITER_DELAY);
    }
  }
  Serial.print(SERIAL_CAPTURE + tcs230.rgb() + SERIAL_ENTER);
  delay(DEBOUNCING_DELAY);
  return tcs230.rgb();
}

bool Hardware::blackCalibrate() {
  tcs230.R_min = MAX;
  tcs230.G_min = MAX;
  tcs230.B_min = MAX;

  if (blackCalibrateButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      tcs230.read();
      if (tcs230.R<tcs230.R_min) {
        tcs230.R_min = tcs230.R;
      }
      if (tcs230.G<tcs230.G_min) {
        tcs230.G_min = tcs230.G;
      }
      if (tcs230.B<tcs230.B_min) {
        tcs230.B_min = tcs230.B;
      }
      delay(ITER_DELAY);
    }
  }

  delay(DEBOUNCING_DELAY);
  Serial.print(SERIAL_BLACK_CALIBRATE);
  return true;
}

bool Hardware::whiteCalibrate() {
  tcs230.R_max = MIN;
  tcs230.G_max = MIN;
  tcs230.B_max = MIN;

  if (blackCalibrateButton.pressed()) {
    for (int i=0;i<CAPTURE_SHOTS;i++) {
      tcs230.read();
      if (tcs230.R>tcs230.R_max) {
        tcs230.R_max = tcs230.R;
      }
      if (tcs230.G>tcs230.G_max) {
        tcs230.G_max = tcs230.G;
      }
      if (tcs230.B>tcs230.B_max) {
        tcs230.B_max = tcs230.B;
      }
      delay(ITER_DELAY);
    }
  }

  Serial.print(SERIAL_WHITE_CALIBRATE);
  delay(DEBOUNCING_DELAY);
  return true;
}