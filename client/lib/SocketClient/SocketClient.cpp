#include "SocketClient.h"

SocketClient::SocketClient() {}

void SocketClient::request(uint16_t port, char* host, String RGB) {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.print(SERIAL_CONNECTION_FAILED);

    delay(1000);
    return;
  }

  Serial.print(SERIAL_CONNECTION_SUCCEED);

  client.print(RGB);

  if (client.connected()) {
    response = client.readStringUntil('\n');
    Serial.print(SERIAL_RESPONSE + response + SERIAL_ENTER);
  }
  Serial.print(SERIAL_DISCONNECTED);
  client.stop();
}