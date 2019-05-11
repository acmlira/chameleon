#include "WiFi.h"

#define WIFI_DELAY 2000

#define SERIAL_MY_IP "My IP is "
#define SERIAL_ENTER "\n"

void attempt(WiFiClass WiFi) {
  delay(WIFI_DELAY);
  Serial.print(SERIAL_MY_IP);
  Serial.print(WiFi.localIP());
  Serial.print(SERIAL_ENTER);
}