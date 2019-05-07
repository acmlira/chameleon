#include "Hardware.h"
#include "Monitor.h"
#include "EventManager.h"
#include "Connection.h"
#include "SPIFFS.h"
#include "SocketClient.h"
#include "Config.h"

#define S0 35
#define S1 34
#define S2 18
#define S3 5
#define OUT 19
#define CAPTURE_PUSH_BUTTON 32
#define BLACK_CALIBRATE_PUSH_BUTTON 33
#define WHITE_CALIBRATE_PUSH_BUTTON 25

#define BAUDRATE 115200
#define INSTANT 100

Hardware hardware;
Monitor monitor;
EventManager manager;
Connection connection;
SocketClient socket;

bool onCaptureEvent(){
  hardware.capture();
  monitor.print(CAPTURE_MSG_BEGIN + hardware.RGB() + CAPTURE_MSG_FINISH);
  socket.request(PORT, HOST, hardware.RGB());
  return true;
}

bool onBlackCalibrateEvent() {
  hardware.blackCalibrate();
  monitor.print(FINISH_CALIBRATION_BLACK);
  return true;
}

bool onWhiteCalibrateEvent() {
  hardware.whiteCalibrate();
  monitor.print(FINISH_CALIBRATION_WHITE);
  return true;
}

bool onConnectionEvent() {
  connection.catchIP();
  monitor.print(CONNECTED_MSG + connection.IP);
  return true;
}

void setup() {
  monitor.begin(BAUDRATE);
  
  connection.begin(SSID, PASSWORD);
  manager.addListener(new ConnectionListener(INSTANT, false, (Action)onConnectionEvent));

  hardware.begin(S0,S1,S2,S3,OUT,CAPTURE_PUSH_BUTTON,BLACK_CALIBRATE_PUSH_BUTTON,WHITE_CALIBRATE_PUSH_BUTTON);
  manager.addListener(new HardwareListener(CAPTURE_PUSH_BUTTON,(Action)onCaptureEvent));
  manager.addListener(new HardwareListener(BLACK_CALIBRATE_PUSH_BUTTON,(Action)onBlackCalibrateEvent));
  manager.addListener(new HardwareListener(WHITE_CALIBRATE_PUSH_BUTTON,(Action)onWhiteCalibrateEvent));
  
  if(!SPIFFS.begin())return;
}

loop(manager);