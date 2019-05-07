#include "Arduino.h"
#include "ColorSensor.h"
#include "PushButton.h"

#define DEBOUNCING_DELAY 200
#define ITER_DELAY 50
#define CAPTURE_SHOTS 10

class Hardware {
private:
  ColorSensor colorSensor;
  PushButton capturePushButton, calibratePushButton_BLACK, calibratePushButton_WHITE;
public:
  Hardware();
  Hardware(int S0, int S1, int S2, int S3, int Out, int capturePushButton,int calibratePushButton_BLACK, int calibratePushButton_WHITE);

  void begin();
  void begin(int S0, int S1, int S2, int S3, int Out, int capturePushButton,int calibratePushButton_BLACK, int calibratePushButton_WHITE);

  bool capture();
  bool calibrate_BLACK();
  bool calibrate_WHITE();

  String RGB();
};