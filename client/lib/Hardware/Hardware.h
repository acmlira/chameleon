#include "Arduino.h"
#include "ColorSensor.h"
#include "PushButton.h"

#define DEBOUNCING_DELAY 200
#define ITER_DELAY 50
#define CAPTURE_SHOTS 10

class Hardware {
private:
  ColorSensor colorSensor;
  PushButton capturePushButton, blackCalibratePushButton, whiteCalibratePushButton;
public:
  Hardware();

  void begin(int S0, int S1, int S2, int S3, int Out, int capturePushButton,int blackCalibratePushButton, int whiteCalibratePushButton);
  void capture();
  void blackCalibrate();
  void whiteCalibrate();

  String RGB();
};