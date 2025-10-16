// Creado ChepeCarlos

#include "CTBot.h"
#include "token.h"

CTBot miBot;
const int Led = 13;

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot de Telegram");

  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);

  miBot.wifiConnect(ssid, password);
  miBot.setTelegramToken(token);

  Serial.println(miBot.testConnection() ? "\n Conectado" : "\n Problemas Auxilio");
}

void loop() {
  TBMessage msg;

  if (CTBotMessageText == miBot.getNewMessage(msg)) {
    Serial << "Mensaje: " << msg.sender.firstName << " - " << msg.text << "\n";

    if (msg.text.equalsIgnoreCase("encender")) {
      digitalWrite(Led, HIGH);
      miBot.sendMessage(msg.sender.id, "Led Encendido");
    } else if (msg.text.equalsIgnoreCase("apagar")) {
      digitalWrite(Led, LOW);
      miBot.sendMessage(msg.sender.id, "Led Apagado");
    } else {
      miBot.sendMessage(msg.sender.id, "Bienvenido " + msg.sender.firstName + ", intenta usar: encender o apagar");
    }
  }

  delay(250);
}
