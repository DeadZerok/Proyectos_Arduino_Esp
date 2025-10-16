# Control de LED por Telegram con ESP32

---

## 💡 Descripción del Proyecto

Este proyecto es un ejemplo práctico y funcional de cómo puedes **controlar un LED** conectado a tu **ESP32** utilizando un **bot de Telegram**. La solución permite enviar comandos específicos ("encender" o "apagar") al bot, y el ESP32 responderá controlando el estado de un LED físico, además de enviar una confirmación de vuelta a Telegram.

Es una excelente base para proyectos de **automatización del hogar, IoT o control remoto** donde necesitas interactuar con tus dispositivos desde cualquier lugar a través de una interfaz de mensajería familiar.

---

## ✨ Características Principales

* **Control Remoto por Telegram:** Enciende y apaga un LED enviando mensajes a tu bot.
* **Comunicación Bidireccional:** El ESP32 recibe comandos y envía confirmaciones a Telegram.
* **Mensaje de Bienvenida:** Saluda a los nuevos usuarios o a quienes envíen comandos no reconocidos.
* **Fácil Configuración:** Utiliza un archivo `token.h` separado para tus credenciales, facilitando la gestión y seguridad.
* **Compatibilidad ESP32:** Diseñado para funcionar con placas ESP32.

---

## 🛠️ Hardware Necesario

* **ESP32:** Cualquier modelo de placa ESP32.
* **LED:** Un LED común.
* **Resistencia:** Una resistencia adecuada para el LED (por ejemplo, 220 ohms).
* **Cables de Conexión:** Para interconectar el LED al ESP32.

---

## 📦 Estructura de Archivos

* `Control_LED_Telegram.ino`: El **código principal** del firmware del ESP32, que maneja la comunicación con Telegram y el control del LED.
* `token.h`: **¡Importante!** Este es un archivo local que contiene tus **credenciales Wi-Fi y el token de tu bot de Telegram**. **NO se incluye en el repositorio público por razones de seguridad.**

---

## 🚀 Cómo Usar

Sigue estos pasos para poner en marcha tu sistema de control de LED por Telegram:

1.  **Crea tu Bot de Telegram:** Si aún no tienes uno, habla con [BotFather](https://t.me/botfather) en Telegram y sigue las instrucciones para crear un nuevo bot y obtener su **token HTTP API**.
2.  **Configura `token.h`:**
    * modifica el archivo llamado **`token.h`** en la misma carpeta que `Control_LED_Telegram.ino`.
    * Abre `token.h` y **rellena tus credenciales**: tu SSID de WiFi, la contraseña de tu WiFi y el token HTTP de tu bot de Telegram. Asegúrate de que el formato sea el mismo que el del ejemplo.
3.  **Abre en Arduino IDE:** Abre el archivo `Control_LED_Telegram.ino` con el Arduino IDE.
4.  **Instala Librerías:** Asegúrate de tener instaladas las siguientes librerías desde el **Gestor de Librerías** del Arduino IDE:
    * `CTBot` (puedes buscarla directamente por ese nombre)
    * `WiFiClientSecure` (generalmente viene con el ESP32 Core)
5.  **Sube al ESP32:** Selecciona tu placa ESP32 y el puerto COM correcto, luego compila y sube el código a tu ESP32.
6.  **Prueba el Control:**
    * Abre el **Monitor Serial** en el Arduino IDE (asegúrate de que la velocidad de baudios sea 115200) para ver el estado de la conexión.
    * En Telegram, busca tu bot y envíale el mensaje `encender`. Deberías ver el LED activarse y recibir una confirmación del bot.
    * Envía `apagar` para apagar el LED.

---

## 🔐 Ejemplo de `token.h`

**¡Atención!** Crea este archivo en tu entorno local. **Nunca lo subas a un repositorio público para proteger tus credenciales.**

```cpp



const char* ssid = "juan";          // Reemplaza con el nombre de tu red WiFi
const char* password = "juan3243";   // Reemplaza con la contraseña de tu red WiFi
const char* token = "515664:AAEKkp2xb1dbuu";      // Reemplaza con el token HTTP de tu bot de Telegram
