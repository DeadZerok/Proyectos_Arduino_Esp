#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // Modo estación (cliente WiFi)
  Serial.print("MAC del ESP32: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // No necesitas nada aquí
}
