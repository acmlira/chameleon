#include "WiFi.h"
#include "Arduino.h"

class SocketClient {
private:
  const uint16_t port;
  const char *   host;
public:
  SocketClient();
  
  void request(uint16_t port, char* host, String RGB);

  String response;
};