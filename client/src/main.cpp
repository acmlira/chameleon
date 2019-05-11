#include "Hardware.h"
#include "ESPAsyncWebServer.h"
#include "Manager.h"
#include "Socket.h"
#include "Serial.h"

#include "SPIFFS.h"
#include "WiFi.h"
#include "Config.h"

#define BAUDRATE 115200
#define PLACEHOLDER_COLOR_SPECTRUM "PLACEHOLDER_COLOR_SPECTRUM"
#define PLACEHOLDER_RGB "PLACEHOLDER_RGB"
#define PLACEHOLDER_HEX "PLACEHOLDER_HEX"
#define WAITING "Waiting for response..."

#define S0 35
#define S1 34
#define S2 18
#define S3 5
#define OUT 19
#define CAPTURE_BUTTON 32
#define BLACK_CALIBRATE_BUTTON 33
#define WHITE_CALIBRATE_BUTTON 25

Hardware hardware;
Manager manager;
Socket socket;

AsyncWebServer server(80);

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

bool onCapture() {
  return socket.request(PORT, HOST, hardware.capture());
}

bool onBlackCalibrate() {
  return hardware.blackCalibrate();
}

bool onWhiteCalibrate() {
  return hardware.whiteCalibrate();
}

void setup() {
  Serial.begin(BAUDRATE);
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) attempt(WiFi);

  hardware.begin(S0,S1,S2,S3,OUT,CAPTURE_BUTTON,BLACK_CALIBRATE_BUTTON,WHITE_CALIBRATE_BUTTON);

  manager.on(new Event(CAPTURE_BUTTON,(Action)onCapture));
  manager.on(new Event(BLACK_CALIBRATE_BUTTON,(Action)onBlackCalibrate));
  manager.on(new Event(WHITE_CALIBRATE_BUTTON,(Action)onWhiteCalibrate));
  
  if(!SPIFFS.begin())return; 
  server.on("/index", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
  });
  server.on("/src/reset.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/reset.css", "text/css");
  });
  server.on("/src/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/style.css", "text/css");
  });
  server.on("/src/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/script.js", "text/javascript");
  });
  server.on("/src/chameleon.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/src/chameleon.png", "image/png");
  });
  server.begin();
}

loop(manager);