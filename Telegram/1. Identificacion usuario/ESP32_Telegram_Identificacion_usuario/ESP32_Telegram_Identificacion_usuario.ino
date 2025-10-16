
#include "CTBot.h"
#include "token.h"

CTBot miBot;

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot de Telegram");

  miBot.wifiConnect(ssid, password);
  miBot.setTelegramToken(token);

  Serial.println(miBot.testConnection() ? "\n Conectado" : "\n Problemas Auxilio");
}

void loop() {
  TBMessage msg;

  if (CTBotMessageText == miBot.getNewMessage(msg)) {
    Serial << "Mensaje: " << msg.sender.firstName << " - " << msg.text << "\n";
    Serial << "usuario: " << msg.sender.username << " ID: " << msg.sender.id << "\n";
  
    
    miBot.sendMessage(msg.sender.id, "Analizando usuario ");
    
  }

  delay(250);
}
