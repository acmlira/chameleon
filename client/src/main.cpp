#include "Hardware.h"
#include "ESPAsyncWebServer.h"
#include "EventManager.h"
#include "SocketClient.h"

#include "SPIFFS.h"
#include "WiFi.h"

#include "Config.h"
#include "Constants.h"
#include "Pins.h"
#include "Serial.h"

Hardware hardware;
EventManager manager;
SocketClient socket;

AsyncWebServer webserver(80);

bool onCaptureEvent(){
  hardware.capture();
  socket.request(PORT, HOST, hardware.RGB());
  Serial.print(SERIAL_CAPTURE_BEGIN + hardware.RGB() + SERIAL_CAPTURE_FINISH);
  return true;
}

bool onBlackCalibrateEvent() {
  hardware.blackCalibrate();
  Serial.print(SERIAL_CALIBRATION_BLACK);
  return true;
}

bool onWhiteCalibrateEvent() {
  hardware.whiteCalibrate();
  Serial.print(SERIAL_CALIBRATION_WHITE);
  return true;
}

String processor(const String& var) {
  if(var == PLACEHOLDER){
    return hardware.RGB();
  }
  return WAITING;
}

void setup() {
  Serial.begin(BAUDRATE);
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)delay(WIFI_DELAY);
  Serial.print(SERIAL_MY_IP + WiFi.localIP());

  hardware.begin(S0,S1,S2,S3,OUT,CAPTURE_PUSH_BUTTON,BLACK_CALIBRATE_PUSH_BUTTON,WHITE_CALIBRATE_PUSH_BUTTON);
  manager.addListener(new HardwareListener(CAPTURE_PUSH_BUTTON,(Action)onCaptureEvent));
  manager.addListener(new HardwareListener(BLACK_CALIBRATE_PUSH_BUTTON,(Action)onBlackCalibrateEvent));
  manager.addListener(new HardwareListener(WHITE_CALIBRATE_PUSH_BUTTON,(Action)onWhiteCalibrateEvent));
  
  if(!SPIFFS.begin())return; 
  webserver.on(ROUTE, HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, HTML_FILE, HTML_TYPE, false, processor);
  });
  webserver.begin();
}

loop(manager);