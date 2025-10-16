# Control de Bombillos Secuencial por RFID con ESP32
---

## 💡 Descripción del Proyecto

Este proyecto demuestra un sistema de **control por RFID** que activa dos bombillos (o cualquier carga conectada a relés) de forma secuencial mediante la **autenticación de una tarjeta RFID**. Utilizando un **ESP32** y un módulo lector **RFID RC522**, el sistema verifica el UID (Identificador Único) de la tarjeta presentada contra un UID autorizado predefinido en el código.

Si se detecta una tarjeta válida, se ejecuta una secuencia de encendido programada:
1.  El primer bombillo (o LED/relé) se **enciende por 5 segundos**.
2.  El primer bombillo se **apaga**.
3.  Después de una pausa de **2 segundos**.
4.  El segundo bombillo (o LED/relé) se **enciende y permanece encendido**.

Si la tarjeta RFID no es reconocida, el sistema simplemente indica el estado en el Monitor Serial sin activar los bombillos. Este proyecto es una base excelente para sistemas de control de acceso básicos, automatización del hogar o aplicaciones de seguridad donde se requiere una secuencia de activación específica.

---

## ✨ Características Principales

* **Autenticación RFID:** Controla el encendido de dispositivos con tarjetas RFID autorizadas.
* **Secuencia de Encendido Programable:** Activa dos cargas eléctricas de forma secuencial y con tiempos definidos.
* **Identificación Sencilla:** Verifica el UID de la tarjeta contra un valor predefinido.
* **Indicación Visual/Serial:** Muestra mensajes en el Monitor Serial para indicar el estado de la autenticación.
* **Compatibilidad ESP32:** Diseñado para funcionar con placas ESP32 y el módulo RC522.

---

## 🛠️ Hardware Necesario

* **ESP32:** Cualquier modelo de placa ESP32.
* **Lector RFID RC522 (MFRC522):** Módulo lector/escritor RFID de 13.56 MHz.
* **2 Bombillos / LEDs / Módulos de Relé:** Para simular las cargas a controlar.
    * **LED/Relé 1**
    * **LED/Relé 2**
* **Resistencias (para LEDs):** Si usas LEDs directamente, necesitarás resistencias adecuadas (ej. 220 ohms).
* **Cables Jumper:** Para todas las conexiones.

---

## 📦 Estructura de Archivos

* `Control_Bombillos_RFID.ino`: El archivo principal del firmware del ESP32 que contiene toda la lógica de control.

---

## 🚀 Cómo Usar

Sigue estos pasos para implementar y probar el sistema de control de bombillos por RFID:

1.  **Instala Arduino IDE:** Asegúrate de tener el Arduino IDE instalado y configurado para programar placas ESP32.
2.  **Instala Librerías:** Abre el **Gestor de Librerías** en Arduino IDE y busca e instala las siguientes librerías:
    * `MFRC522` (asegúrate de que sea la versión correcta, podrías ver varias con este nombre).
    * `SPI` (esta librería suele estar incluida por defecto en el Arduino IDE).
3.  **Conecta el Hardware:** Realiza todas las conexiones del lector RFID y los bombillos/LEDs/relés al ESP32 según el esquema proporcionado en la sección "Hardware Necesario".
4.  **Configura el UID Autorizado:**
    * Abre el archivo `Control_Bombillos_RFID.ino`.
    * **Lee el UID de tu tarjeta:** Si no conoces el UID de tu tarjeta, puedes usar el ejemplo `DumpInfo` de la librería `MFRC522` para leerlo y anotarlo.
    * Localiza el arreglo `targetUID[]` en el código y **reemplaza los valores existentes** con los del UID de la tarjeta RFID que deseas autorizar.
5.  **Sube el Código:** Selecciona tu placa ESP32 y el puerto COM correcto, luego compila y sube el código a tu ESP32.
6.  **Prueba el Sistema:**
    * Abre el **Monitor Serial** en el Arduino IDE (asegúrate de que la velocidad de baudios sea 115200) para ver los mensajes de depuración.
    * **Acerca la tarjeta RFID autorizada** al lector RC522. Deberías observar la secuencia de encendido y apagado del primer bombillo, seguida por el encendido del segundo.
    * Si acercas una tarjeta no autorizada, el Monitor Serial indicará "Tarjeta no reconocida".

---