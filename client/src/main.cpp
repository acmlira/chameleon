#include "Hardware.h"
#include "ESPAsyncWebServer.h"
#include "Manager.h"
#include "Socket.h"

#include "SPIFFS.h"
#include "WiFi.h"

#include "Config.h"
#include "Constants.h"
#include "Pins.h"
#include "Serial.h"

Hardware hardware;
Manager manager;
Socket socket;

AsyncWebServer webserver(80);

bool onCaptureEvent(){
  hardware.capture();
  Serial.print(SERIAL_CAPTURE + hardware.RGB() + SERIAL_ENTER);
  socket.request(PORT, HOST, hardware.RGB());
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
  if(var == PLACEHOLDER_COLOR_SPECTRUM){
    return socket.response_color_spectrum;
  } else if (var == PLACEHOLDER_RGB) {
    return socket.response_rgb;
  } else if (var == PLACEHOLDER_HEX) {
    return socket.response_hex;
  }
  return WAITING;
}

void setup() {
  Serial.begin(BAUDRATE);
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)delay(WIFI_DELAY);
  Serial.print(SERIAL_MY_IP);
  Serial.print(WiFi.localIP());
  Serial.print(SERIAL_ENTER);

  hardware.begin(S0,S1,S2,S3,OUT,CAPTURE_PUSH_BUTTON,BLACK_CALIBRATE_PUSH_BUTTON,WHITE_CALIBRATE_PUSH_BUTTON);
  manager.addListener(new HardwareListener(CAPTURE_PUSH_BUTTON,(Action)onCaptureEvent));
  manager.addListener(new HardwareListener(BLACK_CALIBRATE_PUSH_BUTTON,(Action)onBlackCalibrateEvent));
  manager.addListener(new HardwareListener(WHITE_CALIBRATE_PUSH_BUTTON,(Action)onWhiteCalibrateEvent));
  
  if(!SPIFFS.begin())return; 
  webserver.on("/index", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
  });
  webserver.on("/src/reset.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/reset.css", "text/css");
  });
  webserver.on("/src/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/style.css", "text/css");
  });
  webserver.on("/src/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/script.js", "text/javascript");
  });
  webserver.on("/src/chameleon.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/chameleon.png", "image/png");
  });
  webserver.begin();
}

loop(manager);