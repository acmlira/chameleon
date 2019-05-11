#include "Arduino.h"
#include "TCS230.h"
#include "Button.h"

#define DEBOUNCING_DELAY 200
#define ITER_DELAY 50
#define CAPTURE_SHOTS 10

#define SERIAL_CAPTURE "\nCaptured: "
#define SERIAL_BLACK_CALIBRATE "Black calibrated\n"
#define SERIAL_WHITE_CALIBRATE "White calibrated\n"
#define SERIAL_CONNECTED "Connected with IP: "
#define SERIAL_ENTER "\n"

class Hardware {
private:
  TCS230 tcs230;
  Button captureButton, blackCalibrateButton, whiteCalibrateButton;
public:
  Hardware();
  void begin(int S0, int S1, int S2, int S3, int Out, int captureButton,int blackCalibrateButton, int whiteCalibrateButton);
  String capture();
  bool blackCalibrate();
  bool whiteCalibrate();
};