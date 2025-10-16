# Registro y Gestión de Huellas Digitales con ESP32 y EEPROM
---

## 💡 Descripción del Proyecto

Este proyecto ofrece un sistema para el **registro, visualización y eliminación de huellas digitales** utilizando un **ESP32** y un sensor de huellas compatible con la librería `Adafruit_Fingerprint`. Una de las características clave es la **persistencia de los datos de gestión de huellas en la EEPROM interna del ESP32**. Esto asegura que la información sobre las huellas registradas (si una posición está ocupada, cuándo se actualizó) se conserve incluso después de un reinicio del dispositivo.

El sistema está diseñado para ser interactivo y fácil de usar a través del **Monitor Serial**, proporcionando un menú intuitivo para realizar las operaciones básicas de gestión de huellas. Es una solución ideal para aplicaciones que requieren un control de acceso robusto y una gestión dinámica de usuarios basada en biometría.

---

## ✨ Características Principales

* **Registro Sencillo:** Permite registrar nuevas huellas digitales asignando automáticamente el siguiente ID disponible.
* **Gestión Persistente:** Almacena metadatos de cada huella (estado `ocupado` y `fecha de actualización`) en la **EEPROM** del ESP32, garantizando la persistencia de los datos.
* **Visualización en Consola:** Muestra un listado claro de todas las huellas registradas en el Monitor Serial.
* **Eliminación por ID:** Permite borrar huellas específicas introduciendo su ID desde el Monitor Serial.
* **LED Indicador:** Utiliza un LED para proporcionar retroalimentación visual sobre el estado del sistema o las operaciones.
* **Menú Interactivo:** Interfaz de usuario basada en texto a través del Monitor Serial para una fácil interacción.

---

## 🛠️ Hardware Necesario

* **ESP32:** Cualquier modelo de placa ESP32.
* **Sensor de Huellas Digitales:** Compatible con la librería `Adafruit_Fingerprint` (ej., dy50).
* **LED:** Un LED estándar.
* **Resistencia para LED:** Una resistencia de 220-330 ohms para proteger el LED.
* **Cables Jumper:** Para todas las conexiones.

---

## 📦 Estructura de Archivos

* `Registro_Huellas_EEPROM.ino`: El archivo principal del firmware del ESP32 que contiene toda la lógica de gestión.

---

## ⚙️ Constantes Configurables

Puedes ajustar las siguientes constantes directamente en el código para adaptar el comportamiento a tus necesidades:

* `MAX_FINGERS`: Define el número máximo de huellas que el sistema puede gestionar.
    * Valor por defecto: `127`
* `EEPROM_SIZE`: Establece el tamaño del espacio de EEPROM reservado para los metadatos. Debe ser lo suficientemente grande para almacenar los metadatos de `MAX_FINGERS`.
    * Valor por defecto: `512` bytes

---

## 🚀 Cómo Usar

Sigue estos pasos para poner en marcha tu sistema de gestión de huellas digitales:

1.  **Instala Arduino IDE:** Asegúrate de tener el Arduino IDE instalado y configurado para programar placas ESP32.
2.  **Instala Librerías:** Abre el **Gestor de Librerías** en Arduino IDE y busca e instala las siguientes librerías:
    * `Adafruit_Fingerprint`
    * `EEPROM` (generalmente incluida con el ESP32 Core, pero verifica si necesitas una versión específica).
3.  **Conecta el Hardware:** Realiza todas las conexiones del sensor de huellas y el LED al ESP32 según el esquema proporcionado en la sección "Hardware Necesario".
4.  **Abre y Configura el Código:** Abre el archivo `Registro_Huellas_EEPROM.ino` en el Arduino IDE. Si lo deseas, ajusta las constantes `MAX_FINGERS` y `EEPROM_SIZE` según tus requisitos.
5.  **Sube el Código:** Selecciona tu placa ESP32 y el puerto COM correcto, luego compila y sube el código a tu ESP32.
6.  **Interactúa con el Sistema:**
    * Abre el **Monitor Serial** en el Arduino IDE (asegúrate de que la velocidad de baudios esté configurada a `115200`).
    * El sistema mostrará un menú con las siguientes opciones:
        * **`1`**: Registrar una nueva huella digital.
        * **`2`**: Borrar una huella digital existente por su ID.
        * **`3`**: Ver la lista de todas las huellas almacenadas (ocupadas/libres).
    * Sigue las instrucciones en el Monitor Serial para interactuar con el sistema. El **LED indicador** te dará retroalimentación visual durante el proceso.

---