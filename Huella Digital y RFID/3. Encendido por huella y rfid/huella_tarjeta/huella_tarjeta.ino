#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_Fingerprint.h>

// Definición de pines
#define RXD2 14        // Pin RX para sensor de huellas
#define TXD2 27        // Pin TX para sensor de huellas
#define SS_PIN 5       // Pin SS (SDA) para RFID
#define RST_PIN 22     // Pin RST para RFID
#define R_ENCENDIDO 25 // Pin para relé de encendido
#define R_ARRANQUE 21  // Pin para relé de arranque

// Constantes de tiempo
const unsigned long TIEMPO_RELE = 2000;    // Tiempo de activación de relés (2 segundos)
const unsigned long TIEMPO_ESPERA = 100;   // Tiempo entre lecturas de tarjeta

// UID de la tarjeta autorizada
const byte TARJETA_AUTORIZADA[] = {0x64, 0xCA, 0xE8, 0x2B};
const byte TAMANO_UID = sizeof(TARJETA_AUTORIZADA);

// Variables globales
MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_Fingerprint huella(&Serial2);
unsigned long ultimaLectura = 0;

// Función de inicialización de relés
void inicializarReles() {
    pinMode(R_ENCENDIDO, OUTPUT);
    pinMode(R_ARRANQUE, OUTPUT);
    digitalWrite(R_ENCENDIDO, LOW);
    digitalWrite(R_ARRANQUE, LOW);
}

// Función para mostrar el UID de una tarjeta
void mostrarUID(byte *buffer, byte bufferSize) {
    Serial.print("UID detectado: ");
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
    Serial.println();
}

// Función de inicialización del sensor de huellas
bool inicializarHuella() {
    Serial2.begin(57600, SERIAL_8N1, RXD2, TXD2);
    huella.begin(57600);
    
    if (!huella.verifyPassword()) {
        Serial.println("Error: Sensor de huellas no conectado");
        return false;
    }
    
    Serial.print("Huellas almacenadas: ");
    Serial.println(huella.templateCount);
    return true;
}

// Función de inicialización del RFID
void inicializarRFID() {
    SPI.begin();
    rfid.PCD_Init();
}

// Secuencia de activación de relés
void activarReles() {
    digitalWrite(R_ENCENDIDO, HIGH);
    delay(TIEMPO_RELE);
    
    
    digitalWrite(R_ARRANQUE, HIGH);
    delay(TIEMPO_RELE);
    digitalWrite(R_ARRANQUE, LOW);
}

// Verificar tarjeta RFID
bool verificarRFID() {
    if (millis() - ultimaLectura < TIEMPO_ESPERA) {
        return false;
    }
    ultimaLectura = millis();

    if (!rfid.PICC_IsNewCardPresent()) {
        return false;
    }
    
    if (!rfid.PICC_ReadCardSerial()) {
        return false;
    }

    Serial.println("\n=== Tarjeta Detectada ===");
    mostrarUID(rfid.uid.uidByte, rfid.uid.size);

    bool tarjetaValida = (rfid.uid.size == TAMANO_UID);
    if (tarjetaValida) {
        for (byte i = 0; i < TAMANO_UID && tarjetaValida; i++) {
            if (rfid.uid.uidByte[i] != TARJETA_AUTORIZADA[i]) {
                tarjetaValida = false;
            }
        }
    }

    if (tarjetaValida) {
        Serial.println("Estado: Tarjeta AUTORIZADA ✓");
    } else {
        Serial.println("Estado: Tarjeta NO autorizada ✗");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    
    return tarjetaValida;
}

// Verificar huella digital
bool verificarHuella() {
    uint8_t p = huella.getImage();
    if (p != FINGERPRINT_NOFINGER) {  // Solo procesar si se detecta un dedo
        if (p != FINGERPRINT_OK) {
            Serial.println("\nError al capturar huella");
            return false;
        }

        p = huella.image2Tz();
        if (p != FINGERPRINT_OK) {
            Serial.println("Error: Huella de baja calidad");
            return false;
        }

        p = huella.fingerFastSearch();
        if (p != FINGERPRINT_OK) {
            Serial.println("Huella NO autorizada ✗");
            return false;
        }

        // Solo si la huella es encontrada
        Serial.println("\n=== Huella Detectada ===");
        Serial.println("Estado: Huella AUTORIZADA ✓");
        Serial.print("ID #");
        Serial.println(huella.fingerID);
        return true;
    }
    return false;
}

void setup() {
    Serial.begin(115200);
    while (!Serial) delay(10);
    
    Serial.println("\nIniciando sistema...");
    
    inicializarReles();
    inicializarRFID();
    
    if (!inicializarHuella()) {
        Serial.println("ERROR: Sistema detenido");
        while (1) {
            digitalWrite(R_ENCENDIDO, !digitalRead(R_ENCENDIDO));
            delay(500);
        }
    }
    
    Serial.println("Sistema listo");
}

void loop() {
    if (verificarRFID() || verificarHuella()) {
        Serial.println("¡Acceso autorizado!");
        activarReles();
        delay(1000);
    }
    delay(50);
}