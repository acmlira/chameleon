#include "Connection.h"

Connection::Connection() {}

void Connection::begin(const char* ssid,const char* password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

IPAddress Connection::IP() {
  return WiFi.localIP();
}