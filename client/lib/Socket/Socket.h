#include "WiFi.h"
#include "Arduino.h"

class Socket {
public:
  Socket();
  
  void request(uint16_t port, char* host, String RGB);

  String response_rgb;
  String response_color_spectrum;
  String response_hex;
};