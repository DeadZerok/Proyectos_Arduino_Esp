# Proyectos de Control de Acceso y Automatización con ESP32
---

Este repositorio es una colección versátil de proyectos desarrollados con **ESP32**, centrados en soluciones de **control de acceso, automatización del hogar y seguridad**. Cada proyecto demuestra cómo integrar el potente microcontrolador ESP32 con diversos componentes electrónicos como sensores de huella digital, lectores RFID, servomotores, relés y botones, para construir sistemas funcionales e inteligentes.

El objetivo es proporcionar ejemplos prácticos y configurables que sirvan como punto de partida para tus propias innovaciones en IoT y sistemas embebidos, facilitando el aprendizaje y la experimentación con las capacidades del ESP32.

## Software

* **Arduino IDE:** Entorno de desarrollo.

---

## 🧪 Proyectos Incluidos

| Proyecto                                 | Descripción Detallada                                                                                |
| :--------------------------------------- | :--------------------------------------------------------------------------------------------------- |
| `Registro_Gestion_Huellas/`              | Sistema completo para registrar, visualizar y eliminar huellas digitales, con persistencia en EEPROM. |
| `Encendido_por_Huella/`                  | Activa dos relés de forma secuencial (encendido y arranque) al detectar una huella digital válida.   |
| `Encendido_Huella_RFID/`                 | Proporciona acceso o activación mediante una doble autenticación: Huella Digital *o* RFID.           |
| `Encendido_Luz_RFID/`                    | Enciende dos bombillos (o LEDs/relés) en una secuencia definida tras verificar un UID RFID autorizado. |

---


## 🚀 Cómo Usar los Proyectos

1.  **Clona el Repositorio:** Descarga todo el contenido a tu máquina local.
2.  **Selecciona un Proyecto:** Navega a la carpeta del proyecto que te interese.
3.  **Abre en Arduino IDE:** Abre el archivo `.ino` principal (y cualquier otro archivo `.h` o `.cpp` asociado si los hubiera en la misma carpeta).
4.  **Instala Librerías:** Asegúrate de tener instaladas todas las librerías necesarias mencionadas anteriormente.
5.  **Conecta el Hardware:** Sigue las instrucciones de conexión específicas para cada proyecto (los comentarios en el código o un README.md interno en cada carpeta del proyecto te guiarán).
6.  **Configura Credenciales (si aplica):** Algunos proyectos pueden requerir un archivo `token.h` o similar para credenciales Wi-Fi o tokens (ej. Telegram). Revisa el código de cada proyecto para más detalles.
7.  **Compila y Sube:** Selecciona la placa ESP32 correcta y el puerto COM, luego compila y sube el código a tu ESP32.
8.  **Prueba y Monitorea:** Abre el Monitor Serial para ver mensajes de depuración y probar la funcionalidad.

---

## 🔐 Consideraciones de Seguridad

* Los proyectos de control de acceso utilizan huellas y UIDs RFID predefinidos o almacenados dinámicamente en EEPROM para la autenticación.
* Para aplicaciones de acceso real o críticas, se recomienda implementar medidas de seguridad adicionales, como encriptación de datos, manejo de errores robusto y protección física de los componentes.
* **¡Advertencia!** Nunca compartas tus credenciales de red o tokens API en repositorios públicos. Utiliza archivos locales (ej. `token.h`) y `.gitignore` para excluirlos.

---