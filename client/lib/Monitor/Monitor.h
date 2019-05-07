#include "Arduino.h"

#define CAPTURE_MSG_BEGIN "Captured: RGB("
#define CAPTURE_MSG_FINISH ")"
#define FINISH_CALIBRATION_BLACK "Black calibrated"
#define FINISH_CALIBRATION_WHITE "White calibrated"
#define CONNECTED_MSG "Connected with IP: "

#define BEGIN_DELAY 1000

class Monitor {
public:
  Monitor();

  void begin(int baudrate);
  void print(String string);
};