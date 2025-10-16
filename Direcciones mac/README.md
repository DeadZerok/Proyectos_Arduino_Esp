# ESP32-C3 MAC Reader

Este proyecto usa PlatformIO con un ESP32-C3 Super Mini para imprimir la dirección MAC del chip a través del puerto USB CDC.

## 🛠 Requisitos

- PlatformIO (recomendado usarlo con Visual Studio Code)
- ESP32-C3 Super Mini
- Cable USB de datos (no solo de carga)

## ⚙️ Uso

1. Conecta la placa ESP32-C3 a tu PC por USB.
2. Presiona el botón **BOOT** y mantenlo presionado.
3. Haz clic en **Upload** en PlatformIO y suelta el botón **BOOT** cuando diga "Connecting...".
4. Abre el **monitor serie** (`Ctrl + Alt + M`) para ver la dirección MAC del ESP32-C3.

---

## ❗ Problemas comunes

### 🔄 "Unknown board ID" o error al compilar

Si ves un error como: UnknownBoard: Unknown board ID 'esp32-c3-devkitm-1'

Es porque tu instalación de PlatformIO no tiene actualizada la plataforma `espressif32`.

👉 **Solución**:

Abre la terminal de PlatformIO (dentro de VS Code) y ejecuta:

```bash
pio platform update espressif32