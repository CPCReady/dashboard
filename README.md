# Dashboard para Proyectos CPCReady

![Licencia](https://img.shields.io/badge/Licencia-GPLv3-blue.svg)
![Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-orange.svg)

Una aplicación de terminal en C++ que muestra un panel de información para proyectos de Amstrad CPC gestionados con el ecosistema **CPCReady**. La interfaz está construida con la fantástica biblioteca [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

## Descripción

Este programa lee un archivo de configuración `.cpcready.yml` de un directorio de proyecto especificado y muestra sus datos más importantes en una interfaz de terminal limpia y organizada. Proporciona una vista rápida del estado del proyecto, la configuración del emulador y las unidades de disco.

### Vista Previa

Así es como se ve la aplicación en la terminal:

```
┌────────────────────────────────────────────────────────────────────────────┐
│                                                                            │
│                    ▞▀▖▛▀▖▞▀▖▛▀▖        ▌                                   │
│                    ▌  ▙▄▘▌  ▙▄▘▞▀▖▝▀▖▞▀▌▌ ▌                                │
│                    ▌ ▖▌  ▌ ▖▌▚ ▛▀ ▞▀▌▌ ▌▚▄▌                                │
│                    ▝▀ ▘  ▝▀ ▘ ▘▝▀▘▝▀▘▝▀▘▗▄▘                                │
│                                                                            │
└────────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────────────────────────────────────────────┐
│                     🟥🟩🟦 AMSTRAD CPC 6128                                 │
└────────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────────────────────────────────────────────┐
│ 📺 Mode: 1                                                                 │
└────────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────────────────────────────────────────────┐
│ 💾 🟢 Drive A: /path/to/drive_a.dsk                                        │
│ 💾 🔴 Drive B: /path/to/drive_b.dsk                                        │
└────────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────────────────────────────────────────────┐
│ 📁 Path: /home/user/projects/my-cpc-project                                │
│ 🛠️ Project: MiJuego                                                        │
└────────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────────────────────────────────────────────┐
│ 📚 https://cpcready.readthedocs.io/                                        │
│ ⚙️ https://github.com/orgs/CPCReady/repositories                           │
└────────────────────────────────────────────────────────────────────────────┘
┌────────────────────────────────────────────────────────────────────────────┐
│ 🏷️  cpcready v1.2.3 by Destroyer                                           │
└────────────────────────────────────────────────────────────────────────────┘
```

## Requisitos

Para compilar y ejecutar este proyecto, necesitarás:

- Un compilador de C++ compatible con C++17 (ej. `g++`, `clang++`).
- `CMake` (versión 3.16 o superior).
- La biblioteca `ftxui`.
- La biblioteca `yaml-cpp`.
- `pkg-config` para localizar las bibliotecas.

## Compilación

Sigue estos pasos para compilar el ejecutable:

1.  **Clona el repositorio (si aún no lo has hecho):**
    ```sh
    git clone <url-del-repositorio>
    cd dashboard
    ```

2.  **Crea y entra en el directorio de compilación:**
    ```sh
    mkdir build
    cd build
    ```

3.  **Ejecuta CMake para configurar el proyecto:**
    ```sh
    cmake ..
    ```

4.  **Compila el proyecto:**
    ```sh
    make
    ```
    El ejecutable `dashboard` se creará dentro del directorio `build`.

## Uso

El programa requiere una única ruta como argumento en la línea de comandos: la ruta al directorio del proyecto de CPC que contiene el archivo de configuración.

```sh
./build/dashboard /ruta/a/tu/proyecto_cpc
```

### Archivo de Configuración (`.cpcready.yml`)

El dashboard espera encontrar un archivo `.cpcready.yml` en la raíz del proyecto que le pases como argumento. Este archivo define los parámetros del proyecto.

**Ejemplo de `.cpcready.yml`:**

```yaml
project: "MiJuego"
mode: 1
title: "Mi Juego de CPC"
drive_a: "disk/juego.dsk"
drive_b: "disk/vacio.dsk"
drive_select: "a"
cpc_model: "6128"
```

- `project`: Nombre del proyecto.
- `mode`: Modo de pantalla de Amstrad (0, 1, o 2).
- `title`: Título del proyecto.
- `drive_a` / `drive_b`: Ruta a las imágenes de disco para las unidades A y B.
- `drive_select`: Unidad de disco activa (`a` o `b`).
- `cpc_model`: Modelo de Amstrad CPC (ej. "6128", "464").

## Licencia

Este proyecto está bajo la Licencia Pública General de GNU v3.0. Consulta el archivo [LICENSE](LICENSE) para más detalles.
