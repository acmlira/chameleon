#include "SocketClient.h"

SocketClient::SocketClient() {}

void SocketClient::request(uint16_t port, char* host, String RGB) {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("Connection to host failed");

    delay(1000);
    return;
  }

  Serial.println("Connected to server successful!");

  client.print(RGB);

  if (client.connected())
  {
    response = client.readStringUntil('\n');
    Serial.println(response);
  }
  Serial.println("Disconnecting...");
  client.stop();
}