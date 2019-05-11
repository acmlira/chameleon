#include "Socket.h"

Socket::Socket() {}

bool Socket::request(uint16_t port, char* host, String rgb) {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.print("Connection to host failed\n");

    delay(1000);
    return true;
  }

  Serial.print("Connection established\n");

  client.print(rgb);

  if (client.connected()) {
    response_color_spectrum = client.readStringUntil('\n');
    response_rgb = client.readStringUntil('\n');
    response_hex = client.readStringUntil('\n');
    Serial.print("Response (received):\n| - Color spectrum: " + response_color_spectrum + "\n" + "| - " + response_rgb + "\n| - " + response_hex + "\n");
  }
  Serial.print("Disconnecting...\n");
  client.stop();
  return true;
}