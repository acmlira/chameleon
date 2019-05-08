#include "WiFi.h"
#include "Serial.h"
#include "Arduino.h"

class SocketClient {
public:
  SocketClient();
  
  void request(uint16_t port, char* host, String RGB);

  String response;
};