#include <Adafruit_Fingerprint.h>
#include <EEPROM.h>

// Definición de pines
#define RXD2 14
#define TXD2 27
#define LED_PIN 2

// Constantes
#define MAX_RETRY_COUNT 3
#define FINGERPRINT_TIMEOUT 10000
#define EEPROM_SIZE 512
#define FINGER_COUNT_ADDR 0
#define MAX_FINGERS 127

// Variables globales
HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

// Estructura para almacenar metadatos de huellas
struct FingerMetadata {
  bool isOccupied;
  uint32_t lastUpdated;
};

// Array para mantener registro de huellas almacenadas
FingerMetadata fingerMetadata[MAX_FINGERS];

void loadStoredFingerprints() {
  // Leer el estado de las huellas almacenadas desde EEPROM
  for (int i = 0; i < MAX_FINGERS; i++) {
    EEPROM.get(sizeof(FingerMetadata) * i + FINGER_COUNT_ADDR, fingerMetadata[i]);
  }
  Serial.println(F("Datos de huellas cargados de EEPROM"));
}

void updateFingerMetadata(uint8_t id) {
  if (id > 0 && id <= MAX_FINGERS) {
    fingerMetadata[id-1].isOccupied = true;
    fingerMetadata[id-1].lastUpdated = millis();
    // Guardar en EEPROM
    EEPROM.put(sizeof(FingerMetadata) * (id-1) + FINGER_COUNT_ADDR, fingerMetadata[id-1]);
    EEPROM.commit();
  }
}

uint8_t getNextAvailableID() {
  for (int i = 0; i < MAX_FINGERS; i++) {
    if (!fingerMetadata[i].isOccupied) {
      return i + 1;  // Los IDs comienzan en 1
    }
  }
  return 0;  // No hay espacios disponibles
}

void viewStoredFingerprints() {
  Serial.println(F("\n=== Huellas Almacenadas ==="));
  int count = 0;
  for (int i = 0; i < MAX_FINGERS; i++) {
    if (fingerMetadata[i].isOccupied) {
      count++;
      Serial.printf("ID #%d - Último registro: %lu ms\n", i+1, fingerMetadata[i].lastUpdated);
    }
  }
  Serial.printf("Total de huellas almacenadas: %d\n", count);
}

void deleteFingerprintPrompt() {
  Serial.println(F("\nIngrese ID a eliminar (1-127):"));
  uint8_t id = readNumber();
  
  if (id == 0) {
    Serial.println(F("ID inválido"));
    return;
  }
  
  if (deleteFinger(id)) {
    Serial.println(F("Huella eliminada correctamente"));
    fingerMetadata[id-1].isOccupied = false;
    EEPROM.put(sizeof(FingerMetadata) * (id-1) + FINGER_COUNT_ADDR, fingerMetadata[id-1]);
    EEPROM.commit();
  } else {
    Serial.println(F("Error al eliminar huella"));
  }
}

bool deleteFinger(uint8_t id) {
  uint8_t p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK) {
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  pinMode(LED_PIN, OUTPUT);
  
  // Inicialización del sensor
  mySerial.begin(57600, SERIAL_8N1, RXD2, TXD2);
  
  if (!initializeSensor()) {
    Serial.println(F("Error fatal en la inicialización del sensor"));
    errorBlink();
    ESP.restart();
  }
  
  loadStoredFingerprints();
}

bool initializeSensor() {
  uint8_t tries = 0;
  while (tries < MAX_RETRY_COUNT) {
    if (finger.verifyPassword()) {
      Serial.println(F("Sensor inicializado correctamente"));
      displaySensorInfo();
      return true;
    }
    tries++;
    delay(1000);
  }
  return false;
}

void displaySensorInfo() {
  finger.getParameters();
  Serial.println(F("\nInformación del sensor:"));
  Serial.printf("Capacidad: %d huellas\n", finger.capacity);
  Serial.printf("Nivel de seguridad: %d\n", finger.security_level);
  Serial.printf("Velocidad: %d baudios\n", finger.baud_rate);
}

uint8_t readNumber() {
  String input = "";
  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n') {
        return input.toInt();
      }
      if (isdigit(c)) {
        input += c;
        Serial.print(c);
      }
    }
    yield();
  }
}

void loop() {
  Serial.println(F("\n=== Menú de Registro de Huellas ==="));
  Serial.println(F("1 - Registrar nueva huella"));
  Serial.println(F("2 - Borrar huella"));
  Serial.println(F("3 - Ver huellas almacenadas"));
  
  while (!Serial.available()) {
    yield();
  }
  
  uint8_t option = readNumber();
  switch (option) {
    case 1:
      enrollNewFingerprint();
      break;
    case 2:
      deleteFingerprintPrompt();
      break;
    case 3:
      viewStoredFingerprints();
      break;
    default:
      Serial.println(F("Opción no válida"));
  }
}

bool enrollNewFingerprint() {
  id = getNextAvailableID();
  if (id == 0) {
    Serial.println(F("Error: No hay espacios disponibles"));
    return false;
  }
  
  Serial.printf("Registrando huella #%d\n", id);
  
  uint32_t startTime = millis();
  uint8_t result = getFingerprintEnroll();
  
  if (result) {
    updateFingerMetadata(id);
    Serial.println(F("Registro exitoso"));
    successBlink();
    return true;
  } else {
    Serial.println(F("Error en el registro"));
    errorBlink();
    return false;
  }
}

uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.println(F("Esperando dedo..."));
  
  // Primera captura
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if (p == FINGERPRINT_OK) {
      Serial.println(F("Imagen capturada"));
    } else if (p == FINGERPRINT_NOFINGER) {
      Serial.print(".");
    } else {
      printError(p);
      return p;
    }
    yield();
  }
  
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    printError(p);
    return p;
  }
  
  Serial.println(F("Retire el dedo"));
  delay(2000);
  
  // Segunda captura para verificación
  p = -1;
  Serial.println(F("Coloque el mismo dedo nuevamente"));
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    yield();
  }
  
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    printError(p);
    return p;
  }
  
  // Crear y guardar modelo
  p = finger.createModel();
  if (p != FINGERPRINT_OK) {
    printError(p);
    return p;
  }
  
  p = finger.storeModel(id);
  if (p != FINGERPRINT_OK) {
    printError(p);
    return p;
  }
  
  return true;
}

void printError(uint8_t error) {
  Serial.printf("Error: %d - ", error);
  switch (error) {
    case FINGERPRINT_IMAGEMESS:
      Serial.println(F("Imagen poco clara"));
      break;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println(F("No se encontraron características"));
      break;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println(F("Imagen inválida"));
      break;
    default:
      Serial.println(F("Error desconocido"));
  }
}

void successBlink() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void errorBlink() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}