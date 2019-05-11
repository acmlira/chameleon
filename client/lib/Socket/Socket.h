#include "WiFi.h"
#include "Arduino.h"

class Socket {
public:
  Socket();
  String response_rgb;
  String response_color_spectrum;
  String response_hex;
  bool request(uint16_t port, char* host, String rgb);
};