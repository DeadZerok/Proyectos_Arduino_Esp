//librerias 

  //telegram bot
#include "CTBot.h"
  // wifi
  #include <WiFi.h>
  //.h
#include "token.h"
// Permite usar Serial << "texto";
template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}



CTBot miBot;

// funcion que verifica que establesca la conexion a wifi

void conectarWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando al WiFi...");
    miBot.wifiConnect(ssid, password);
    delay(1000);
  }
}

// funcion de conexion con telegram

void responderMensaje(TBMessage &msg) {
  Serial << "\n \n" << "Nombre de usuario: " << msg.sender.firstName << "  "  << " Apellido: " << msg.sender.lastName <<"\n" <<"Usuario: " << msg.sender.username <<
  " - " <<"ID: " <<msg.sender.id << "\n\nMensaje:  " <<msg.text << "\n";
  String txt = msg.text;
  txt.toLowerCase();

  if (txt == "/start") {
    miBot.sendMessage(msg.sender.id, "¡Hola! Estoy listo para recibir comandos.");
  }
  else if (txt == "/status") {
    miBot.sendMessage(msg.sender.id, "Todo funcionando correctamente.");
  }
  else {
    miBot.sendMessage(msg.sender.id, "Comando no reconocido.");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot de Telegram");

  conectarWiFi();
  miBot.setTelegramToken(token);
  

  if (miBot.testConnection()) {
    Serial.println("✅ Conectado correctamente a Telegram.");
  } else {
    Serial.println("❌ No se pudo conectar a Telegram.");
  }
}


void loop() {
  conectarWiFi();  // Mejora: reconectar si se cae

  TBMessage msg;
  if (CTBotMessageText == miBot.getNewMessage(msg)) {
    responderMensaje(msg);
  }

  delay(500);  // Controla la frecuencia de consulta
}
