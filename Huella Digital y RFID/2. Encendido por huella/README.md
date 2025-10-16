# Control de Encendido Secuencial por Huella Digital con ESP32
---

## 💡 Descripción del Proyecto

Este proyecto implementa un sistema de **control de encendido secuencial** mediante la **autenticación por huella digital** utilizando un **ESP32** y un sensor biométrico(DY 50) compatible con la librería Adafruit_Fingerprint. El objetivo principal es proporcionar una solución de acceso o activación segura, donde solo una huella digital específica (ID = 1 en este caso) puede iniciar una secuencia de encendido.

Al detectar una huella válida, el sistema activa **dos relés de forma secuencial**: primero un relé de "encendido" y luego un relé de "arranque", cada uno por un tiempo determinado, para finalmente solo el de encendido quede aquivo. Esta funcionalidad es ideal para aplicaciones que requieren una secuencia de activación controlada, como el encendido de sistemas complejos, máquinas o incluso vehículos.

---

## ✨ Características Principales

* **Activación por Huella Digital:** Permite el control del sistema solo a usuarios autorizados mediante un sensor de huellas.
* **Encendido Secuencial:** Activa dos relés (encendido y arranque) en una secuencia predefinida.
* **Seguridad Mejorada:** Ofrece un nivel de seguridad adicional en comparación con interruptores manuales.
* **Control por ESP32:** Aprovecha las capacidades del ESP32 para procesamiento y control.

---

## 🛠️ Hardware Necesario

* **ESP32:** Cualquier modelo de placa ESP32 (probado con éxito en diversas variantes).
* **Sensor de Huellas Digitales:** DY 50 Compatible con la librería `Adafruit_Fingerprint` 
* **2 Módulos de Relé:** Para controlar los dispositivos externos
* **Cables de Conexión:** Para interconectar todos los componentes.

### Conexiones de Hardware

* **Sensor de Huellas (RX del sensor)** $\leftrightarrow$ **GPIO 14 (ESP32)**
* **Sensor de Huellas (TX del sensor)** $\leftrightarrow$ **GPIO 27 (ESP32)**
* **Relé de Encendido** $\leftrightarrow$ **GPIO 25 (ESP32)**
* **Relé de Arranque** $\leftrightarrow$ **GPIO 21 (ESP32)**

---

## 📦 Estructura de Archivos

* `Control_Huella_Secuencial.ino`: El archivo principal del firmware del ESP32 que contiene toda la lógica de control.

---

## 🚀 Cómo Usar

Sigue estos pasos para implementar y probar el sistema:

1.  **Instala Arduino IDE:** Asegúrate de tener el Arduino IDE instalado y configurado para programar ESP32.
2.  **Instala la Librería:** Abre el **Gestor de Librerías** en Arduino IDE y busca e instala la librería `Adafruit_Fingerprint`.
3.  **Conecta el Hardware:** Realiza las conexiones del sensor de huellas y los relés al ESP32 según el esquema proporcionado en la sección "Hardware Necesario".
4.  **Abre el Código:** Abre el archivo `Control_Huella_Secuencial.ino` en el Arduino IDE.
5.  **Registra Huellas:**
    * Este código está configurado para **validar solo la huella con ID 1**.
    * Si aún no tienes huellas registradas o necesitas añadir más, utiliza los ejemplos incluidos en la librería `Adafruit_Fingerprint` (por ejemplo, `enroll` o `fingerprint`) para registrar tu huella con el **ID 1**.
6.  **Sube el Código:** Selecciona tu placa ESP32 y el puerto COM correcto en el Arduino IDE. Luego, compila y sube el código a tu ESP32.
7. **Prueba el Sistema:** Una vez que el ESP32 esté funcionando, coloca la huella digital registrada (ID 1) en el sensor. Observa cómo los relés se activan secuencialmente y luego se apagan.