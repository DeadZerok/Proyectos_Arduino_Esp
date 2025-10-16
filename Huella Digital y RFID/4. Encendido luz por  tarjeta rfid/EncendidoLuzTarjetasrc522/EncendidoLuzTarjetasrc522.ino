#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5      // SDA Pin (cambiado si es necesario)
#define RST_PIN 22    // RST Pin
#define LED_PIN_1 21  // Pin del primer bombillo
#define LED_PIN_2 25  // Pin del segundo bombillo

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia MFRC522

// UID esperado de la tarjeta
byte targetUID[] = {0x64, 0xCA, 0xE8, 0x2B};  // UID de la tarjeta a verificar

void setup() {
  Serial.begin(115200);    // Iniciar comunicación serial
  SPI.begin();             // Iniciar bus SPI
  mfrc522.PCD_Init();      // Iniciar MFRC522

  pinMode(LED_PIN_1, OUTPUT);  // Configurar pin del primer bombillo como salida
  pinMode(LED_PIN_2, OUTPUT);  // Configurar pin del segundo bombillo como salida

  // Asegurarse de que los bombillos estén apagados al inicio
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);

  Serial.println("Acerque su tarjeta al lector...");
}

void loop() {
  // Verificar si hay una nueva tarjeta cerca
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Seleccionar la tarjeta detectada
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Verificar si el UID coincide con el UID objetivo
  if (isTargetCard(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    Serial.println("Tarjeta reconocida, encendiendo bombillos...");
    digitalWrite(LED_PIN_1, HIGH);  // Encender primer bombillo
     delay(5000);   
    digitalWrite(LED_PIN_1, LOW);
    delay(2000);   
    digitalWrite(LED_PIN_2, HIGH);  // Encender segundo bombillo                 // Mantener encendidos los bombillos por 5 segundos
       // Apagar primer bombillo
       // Apagar segundo bombillo
  } else {
    Serial.println("Tarjeta no reconocida.");
  }

  // Parar la lectura de la tarjeta actual
  mfrc522.PICC_HaltA();
}

// Función para verificar si el UID leído coincide con el objetivo
bool isTargetCard(byte *uid, byte uidSize) {
  if (uidSize != sizeof(targetUID)) return false;  // Comparar tamaños de UID
  for (byte i = 0; i < uidSize; i++) {
    if (uid[i] != targetUID[i]) return false;
  }
  return true;
}
