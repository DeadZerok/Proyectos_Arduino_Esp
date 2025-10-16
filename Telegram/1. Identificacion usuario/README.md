# ESP32_Telegram_Identificacion
---

## 💡 Descripción del Proyecto

Este proyecto es un ejemplo práctico y conciso de cómo integrar tu **ESP32** con la plataforma de mensajería **Telegram**. Su objetivo principal es demostrar la capacidad de un bot de Telegram para **recibir mensajes** y, a partir de estos, **identificar al remitente**. Una vez que el ESP32 recibe un mensaje a través del bot, extrae y muestra en el **Monitor Serial** información clave del usuario, como su **nombre, nombre de usuario (username) y ID único**.

Este ejemplo es ideal para desarrolladores que buscan iniciar proyectos de **automatización, monitoreo remoto o control de dispositivos** a través de Telegram, donde la identificación del usuario que interactúa con el bot es fundamental para implementar lógica de acceso o permisos.

---
## ✨ Características Principales

* **Recepción de Mensajes:** Escucha y procesa los mensajes entrantes de un bot de Telegram.
* **Identificación del Remitente:** Extrae y muestra el nombre, nombre de usuario (username) e ID del usuario que envió el mensaje.
* **Monitor Serial:** Utiliza el puerto serial para visualizar la información de identificación.
* **Fácil Integración:** Diseñado para ESP32, es un excelente punto de partida para proyectos de Telegram con microcontroladores.
* **Seguridad de Credenciales:** Separa las credenciales sensibles en un archivo `token.h` para evitar subirlas accidentalmente al repositorio.

---

## 📦 Estructura de Archivos

* `ESP32_Telegram_Identificacion.ino`: El **código principal** del firmware del ESP32, que maneja la comunicación con Telegram y el procesamiento de mensajes.
* `token.h`: **¡Importante!** Este es un archivo local que contiene tus **credenciales Wi-Fi, el token de tu bot de Telegram y el ID del chat**. **NO se incluye en el repositorio público por razones de seguridad.**
* `token_example.h`: Una plantilla que te muestra el formato esperado para el archivo `token.h`.

---

## 🚀 Cómo Usar

Sigue estos pasos para poner en marcha tu bot de Telegram en el ESP32:

1.  **Crea tu Bot de Telegram:** Si aún no tienes uno, habla con [BotFather](https://t.me/botfather) en Telegram y sigue las instrucciones para crear un nuevo bot y obtener su **token HTTP API**.
2.  **Obtén tu Chat ID:** Envía un mensaje a tu nuevo bot. Luego, puedes usar servicios como [@userinfobot](https://t.me/userinfobot) en Telegram o ir a `https://api.telegram.org/bot<TU_BOT_TOKEN>/getUpdates` (reemplazando `<TU_BOT_TOKEN>` con el token de tu bot) en tu navegador para encontrar tu `chat_id`.
3.  **Configura `token.h`:**
    * Copia el archivo `token_example.h` y renómbralo a **`token.h`** en la misma carpeta que `ESP32_Telegram_Identificacion.ino`.
    * Abre `token.h` y **rellena tus credenciales**: tu SSID de WiFi, la contraseña de tu WiFi, el token HTTP de tu bot de Telegram y tu ID de chat.
4.  **Abre en Arduino IDE:** Abre el archivo `ESP32_Telegram_Identificacion.ino` con el Arduino IDE.
5.  **Instala Librerías:** Asegúrate de tener instaladas las siguientes librerías  y gestor de placas en el IDE de arduino.

**Gestor de Placas** del Arduino IDE:
    
    - esp32 de Espressif`

    
**Gestor de Librerías** del Arduino IDE:
   
    - Arduinojson  v5.13.5
    - CTBot

6.  **Sube al ESP32:** Selecciona tu placa ESP32 (por ejemplo, "ESP32 Dev Module" o "ESP32-C3 Dev Module") y el puerto COM correcto, luego compila y sube el código a tu ESP32.
7.  **Prueba el Bot:** Abre el **Monitor Serial** en el Arduino IDE (asegúrate de que la velocidad de baudios sea 115200). Envía cualquier mensaje a tu bot de Telegram. Deberías ver el nombre, nombre de usuario e ID del remitente aparecer en el Monitor Serial.

---