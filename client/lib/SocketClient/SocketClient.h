#include "WiFi.h"
#include "Arduino.h"

class SocketClient {
public:
  SocketClient();
  
  void request(uint16_t port, char* host, String RGB);

  String response_rgb;
  String response_color_spectrum;
  String response_hex;
};