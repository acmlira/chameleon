#include "Hardware.h"
#include "Monitor.h"
#include "EventManager.h"

#define S0 35
#define S1 34
#define S2 18
#define S3 5
#define Out 19
#define capturePushButton 32
#define calibratePushButton_BLACK 33
#define calibratePushButton_WHITE 25

#define baudrate 115200

Hardware hardware;
Monitor monitor;
EventManager manager;

bool onCapture_Event(){
  hardware.capture();
  monitor.print(CAPTURE_MSG_BEGIN + hardware.RGB() + CAPTURE_MSG_FINISH);
  return true;
}

bool onCalibrate_BLACK_Event() {
  hardware.calibrate_BLACK();
  monitor.print(FINISH_CALIBRATION_BLACK);
  return true;
}

bool onCalibrate_WHITE_Event() {
  hardware.calibrate_WHITE();
  monitor.print(FINISH_CALIBRATION_WHITE);
  return true;
}

void setup() {
  monitor.begin(baudrate);
  hardware.begin(S0,S1,S2,S3,Out,capturePushButton,calibratePushButton_BLACK,calibratePushButton_WHITE);

  manager.addListener(new HardwareListener(capturePushButton,(Action)onCapture_Event));
  manager.addListener(new HardwareListener(calibratePushButton_BLACK,(Action)onCalibrate_BLACK_Event));
  manager.addListener(new HardwareListener(calibratePushButton_WHITE,(Action)onCalibrate_WHITE_Event));
}

loop(manager);