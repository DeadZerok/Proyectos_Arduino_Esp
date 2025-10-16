 #include <Adafruit_Fingerprint.h>

// Pines de configuración
#define RXD2 14  // Pin RX para ESP32 (puedes cambiar este valor según tus necesidades)
#define TXD2 27  // Pin TX para ESP32 (puedes cambiar este valor según tus necesidades)

// Manejo de relés
#define R_Encendido 25  // Pin del relé de encendido
#define R_Arranque 21   // Pin del relé de arranque

// Configuración del sensor de huellas
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2); // Usa el puerto Serial2

void setup() {
  // Configuración de pines de relé como salida
  pinMode(R_Encendido, OUTPUT);
  pinMode(R_Arranque, OUTPUT);

  // Inicialmente apagamos ambos relés
  digitalWrite(R_Encendido, LOW);
  digitalWrite(R_Arranque, LOW);

  // Configuración del sensor de huellas
  Serial.begin(115200);
  Serial2.begin(57600, SERIAL_8N1, RXD2, TXD2); // Configuración de puerto para ESP32
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas encontrado y conectado.");
  } else {
    Serial.println("No se pudo conectar con el sensor de huellas.");
    while (1);
  }
}

void loop() {
  // Espera a que se detecte una huella válida
  if (getFingerprintID() == 1) {
    Serial.println("Huella válida detectada, activando relés.");

    // Enciende el relé de encendido
    digitalWrite(R_Encendido, HIGH);
    delay(2000); // Espera 2 segundos

    // Apaga el relé de encendido y enciende el relé de arranque
    digitalWrite(R_Encendido, LOW);
    digitalWrite(R_Arranque, HIGH);
    delay(2000); // Espera 2 segundos

    // Apaga el relé de arranque
    digitalWrite(R_Arranque, LOW);

    // Pequeña espera antes de permitir otra lectura de huella
    delay(1000);
  }
}

// Función para leer la huella y verificarla
int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  // Retorna el ID de la huella encontrada
  Serial.print("ID de la huella encontrada: "); Serial.println(finger.fingerID);
  return finger.fingerID;
}
