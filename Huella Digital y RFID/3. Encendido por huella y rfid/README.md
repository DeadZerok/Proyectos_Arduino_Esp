# Sistema de Encendido con Doble Autenticación (RFID + Huella) usando ESP32
---

## 💡 Descripción del Proyecto

Este proyecto implementa un sistema de **control de encendido con doble autenticación** utilizando un **ESP32**, que combina la seguridad de la **identificación por radiofrecuencia (RFID)** y el **reconocimiento biométrico de huellas digitales**. El objetivo es proporcionar un método seguro y flexible para activar un equipo, como un vehículo o un sistema eléctrico, solo a usuarios autorizados.

El sistema funciona de la siguiente manera:
1.  **Autenticación RFID:** Al acercar una tarjeta RFID con un UID autorizado predefinido.
2.  **Autenticación por Huella Digital:** Al reconocer una huella digital previamente registrada en el sensor.

Si cualquiera de estas dos autenticaciones es exitosa, el ESP32 activa una **secuencia de encendido de dos relés**: primero un relé de "encendido" (por 2 segundos) y luego un relé de "arranque" (por 2 segundos). Ambos relés se apagan automáticamente después de completar la secuencia. Este diseño de doble vía (RFID *o* Huella) ofrece flexibilidad sin comprometer la seguridad.

---

## ✨ Características Principales

* **Doble Autenticación:** Soporta tanto RFID como huella digital para el acceso.
* **Encendido Secuencial:** Activa dos relés en una secuencia controlada para simular el encendido de un motor o sistema.
* **Seguridad Flexible:** Permite la autenticación por cualquiera de los dos métodos, aumentando la versatilidad.
* **Basado en ESP32:** Aprovecha las capacidades de este microcontrolador para una solución eficiente.
* **Robustez:** Incluye verificación de la conexión con el sensor de huellas al inicio.

---

## 🛠️ Hardware Necesario

* **ESP32:** Cualquier modelo de placa ESP32.
* **Sensor de Huellas Digitales:** Compatible con la librería `Adafruit_Fingerprint` (DY50).
* **Lector RFID RC522 (MFRC522):** Módulo lector/escritor RFID de 13.56 MHz.
* **2 Módulos de Relé:** Para controlar el encendido y el arranque.
* **Cables Jumper:** Para todas las conexiones.

---

## 📦 Estructura de Archivos

* `Doble_Autenticacion_Encendido.ino`: El archivo principal del firmware del ESP32 que contiene toda la lógica de control.

---

## 🚀 Cómo Usar

Sigue estos pasos para implementar y probar el sistema de doble autenticación:

1.  **Instala Arduino IDE:** Asegúrate de tener el Arduino IDE instalado y configurado para programar placas ESP32.
2.  **Instala Librerías:** Abre el **Gestor de Librerías** en Arduino IDE y busca e instala las siguientes librerías:
    * `Adafruit_Fingerprint`
    * `MFRC522`
    * Asegúrate de que la librería `SPI` esté instalada (generalmente viene por defecto con el IDE).
3.  **Conecta el Hardware:** Realiza todas las conexiones del sensor de huellas, el lector RFID y los relés al ESP32 según el esquema proporcionado en la sección "Hardware Necesario".
4.  **Configura el UID Autorizado:**
    * Abre el archivo `Doble_Autenticacion_Encendido.ino`.
    * Localiza la sección donde se define `TARJETA_AUTORIZADA` y reemplaza el UID de ejemplo con el UID de la tarjeta RFID que deseas autorizar. Puedes usar un ejemplo de la librería `MFRC522` (como `DumpInfo`) para leer el UID de tu tarjeta.
5.  **Registra la Huella Digital:**
    * El código espera una huella digital previamente registrada en el sensor.
    * Utiliza los ejemplos de la librería `Adafruit_Fingerprint` (como `enroll` o `fingerprint`) para registrar la huella digital que desees autorizar. Es recomendable registrarla con un **ID específico** si el código lo requiere, o con cualquier ID si el código busca cualquier huella registrada. (El código actual valida si la huella está "previamente registrada", lo que implica que cualquier ID válido en el sensor funcionaría. Para mayor seguridad, podrías modificar el código para validar un `ID` de huella específico, como el `ID 1` del ejemplo anterior).
6.  **Sube el Código:** Selecciona tu placa ESP32 y el puerto COM correcto en el Arduino IDE. Luego, compila y sube el código a tu ESP32.
7.  **Prueba el Sistema:**
    * Abre el **Monitor Serial** (a 115200 baudios) para observar el estado del sistema y los mensajes de depuración.
    * **Para RFID:** Acérca la tarjeta RFID autorizada al lector. Deberías ver los relés activarse secuencialmente.
    * **Para Huella Digital:** Coloca la huella digital registrada en el sensor. Deberías observar la misma secuencia de activación de los relés.
    * Si el sensor de huellas no se detecta al inicio, el sistema se detendrá y lo indicará en el Monitor Serial.

---