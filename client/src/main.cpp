#include "Hardware.h"
#include "Monitor.h"
#include "EventManager.h"
#include "Connection.h"
#include "SPIFFS.h"
#include "SocketClient.h"
#include "Config.h"
#include "ESPAsyncWebServer.h"

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

AsyncWebServer webserver(80);
const char * html = "<p>%PLACEHOLDER%</p>";

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

bool onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
 
    Serial.println("Websocket client connection received");
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    Serial.println("-----------------------");
 
  } else if(type == WS_EVT_DATA){
    
    Serial.print("Data received: ");
 
    for(int i=0; i < len; i++) {
      Serial.print((char) data[i]);
    }
 
    Serial.println();
  }
  return true;
}

String processor(const String& var) {
 
  if(var == "PLACEHOLDER"){
    return String(random(1,20));
  }
 
  return String();
}

void setup() {
  monitor.begin(BAUDRATE);
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)delay(1000);
  Serial.println(WiFi.localIP());

  hardware.begin(S0,S1,S2,S3,OUT,CAPTURE_PUSH_BUTTON,BLACK_CALIBRATE_PUSH_BUTTON,WHITE_CALIBRATE_PUSH_BUTTON);
  manager.addListener(new HardwareListener(CAPTURE_PUSH_BUTTON,(Action)onCaptureEvent));
  manager.addListener(new HardwareListener(BLACK_CALIBRATE_PUSH_BUTTON,(Action)onBlackCalibrateEvent));
  manager.addListener(new HardwareListener(WHITE_CALIBRATE_PUSH_BUTTON,(Action)onWhiteCalibrateEvent));
  
  monitor.print(CONNECTED_MSG + connection.IP());
  if(!SPIFFS.begin())return; 
  webserver.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
  });
  webserver.begin();
}

loop(manager);