#include "WiFi.h"
#include "/home/acmlira/Documents/Code/chameleon/client/src/Serial.h"
#include "Arduino.h"

class SocketClient {
public:
  SocketClient();
  
  void request(uint16_t port, char* host, String RGB);

  String response;
};