#!/bin/bash

# Este script descarga TODOS los artefactos de la última compilación exitosa,
# extrae cada ejecutable, lo renombra según su plataforma y lo mueve a la carpeta `opt`.
#
# REQUISITOS:
#   - Tener la CLI de GitHub (`gh`) instalada y autenticada.
#     (https://cli.github.com/)
#   - Ejecutar este script desde la raíz del repositorio.

set -e

DEST_DIR="opt/software"
EXECUTABLE_NAME="dashboard"

# 1. Obtener el repositorio actual (ej. "owner/repo")
#REPO=CPCReady/dashboard
REPO=$(gh repo view --json nameWithOwner -q .nameWithOwner)
echo $REPO
if [ -z "$REPO" ]; then
    echo "Error: No se pudo determinar el repositorio de GitHub."
    echo "Asegúrate de estar en un repositorio de git con un remote configurado."
    exit 1
fi

# 2. Encontrar el ID de la última ejecución exitosa en la rama main
echo "Buscando la última compilación exitosa en la rama 'main'..."
LATEST_RUN_ID=$(gh run list --workflow=build.yml --branch=main --status=success -L 1 --json databaseId -q '.[] | .databaseId' --repo "$REPO")

if [ -z "$LATEST_RUN_ID" ]; then
    echo "Error: No se encontraron compilaciones exitosas para 'build.yml' en la rama main."
    exit 1
fi

echo "Encontrada la última ejecución exitosa con ID: $LATEST_RUN_ID"

# 3. Descargar TODOS los artefactos de la ejecución.
# gh creará un directorio por cada artefacto.
echo "Descargando todos los artefactos de la compilación..."

# Limpiar directorios de artefactos de ejecuciones anteriores
rm -rf dashboard-*

gh run download "$LATEST_RUN_ID" --repo "$REPO"

echo "Artefactos descargados."

# 4. Preparar el directorio de destino final
echo "Creando el directorio de destino '$DEST_DIR'..."
mkdir -p "$DEST_DIR"

# 5. Procesar cada artefacto descargado
echo "Procesando y renombrando los ejecutables..."

# Iterar sobre cada directorio de artefacto que gh ha creado (ej. dashboard-ubuntu-x86_64/)
for ARTIFACT_DIR in dashboard-*/; do
    if [ ! -d "$ARTIFACT_DIR" ]; then
        echo "Advertencia: No se encontraron directorios de artefactos que empiecen con 'dashboard-'."
        continue
    fi

    EXECUTABLE_PATH="${ARTIFACT_DIR}${EXECUTABLE_NAME}"

    if [ -f "$EXECUTABLE_PATH" ]; then
        # Obtener el nombre del artefacto a partir del nombre del directorio
        ARTIFACT_NAME=$(basename "$ARTIFACT_DIR")
        
        echo "  - Procesando: $ARTIFACT_NAME"

        # El nuevo nombre del ejecutable será el mismo que el del artefacto
        RENAMED_EXECUTABLE="$ARTIFACT_NAME"

        # Dar permisos de ejecución
        chmod +x "$EXECUTABLE_PATH"

        # Mover y renombrar el ejecutable a la carpeta opt
        mv "$EXECUTABLE_PATH" "$DEST_DIR/$RENAMED_EXECUTABLE"
        
        # Eliminar el directorio del artefacto ya vacío
        rm -r "$ARTIFACT_DIR"
    else
        echo "  - Advertencia: No se encontró el ejecutable '$EXECUTABLE_NAME' en '$ARTIFACT_DIR'."
    fi
done

echo ""
echo "✅ Proceso completado. Los ejecutables están en: ./$DEST_DIR/"
