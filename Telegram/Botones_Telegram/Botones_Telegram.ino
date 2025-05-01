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
CTBotInlineKeyboard miTeclado;


// pines

const int led = 26;  // Define el pin del LED


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

  pinMode(led, OUTPUT);  // Inicializa el pin del LED

  conectarWiFi();
  miBot.setTelegramToken(token);

  if (miBot.testConnection()) {
    Serial.println("✅ Conectado correctamente a Telegram.");
  } else {
    Serial.println("❌ No se pudo conectar a Telegram.");
  }

  // Teclado con botones
  miTeclado.addButton("menu De opciones", "opciones", CTBotKeyboardButtonQuery);
  miTeclado.addButton("Información", "status", CTBotKeyboardButtonQuery);
  miTeclado.addButton("Encender", "/encender", CTBotKeyboardButtonQuery);
  miTeclado.addButton("Apagar", "/apagar", CTBotKeyboardButtonQuery);
  miTeclado.addRow();
  miTeclado.addButton("Ver documentación", "https://core.telegram.org/bots/features#keyboards", CTBotKeyboardButtonURL);
}



void loop() {
  conectarWiFi();  // Mejora: reconectar si se cae

  TBMessage msg;
  if (miBot.getNewMessage(msg)) {
    if (msg.messageType == CTBotMessageText) {
      if (msg.text.equalsIgnoreCase("opciones")) {
        miBot.sendMessage(msg.sender.id, "Opciones disponibles:", miTeclado);
      }
      else {
        miBot.sendMessage(msg.sender.id, "prueba 'opciones'");
      }
    } else if (msg.messageType == CTBotMessageQuery) {
      Serial << "Mensaje: " <<  msg.sender.firstName;
      if (msg.callbackQueryData.equals("/encender")) {
        Serial.println(" Endender");
        digitalWrite(led, LOW);
        miBot.endQuery(msg.callbackQueryID, "Led Encendido", true);
      } else if (msg.callbackQueryData.equals("/apagar")) {
        Serial.println(" Apagar");
        digitalWrite(led, HIGH);
        miBot.endQuery(msg.callbackQueryID, "Led Apagado", true);
      }
    }
  }

  delay(250);  // Controla la frecuencia de consulta
}
