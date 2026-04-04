# MedLexer - Analizador Léxico y Semántico Hospitalario 

MedLexer es una herramienta construida en **C++ con el framework Qt**, diseñada para analizar archivos de texto plano que contienen información estructurada de un hospital (pacientes, médicos, citas y diagnósticos). El sistema realiza un análisis léxico para tokenizar la entrada, seguido de una extracción semántica para vincular los datos y generar reportes interactivos y visuales.

## Características Principales

* **Análisis Léxico:** Escanea el texto de entrada identificando palabras reservadas, identificadores, cadenas, números y signos de puntuación.
* **Tolerancia a Errores (UI-Driven):** Captura caracteres desconocidos y errores léxicos sin detener el análisis, mostrándolos directamente en la interfaz gráfica.
* **Extracción de Datos:** Convierte los tokens abstractos en estructuras de datos reales (`Paciente`, `Medico`, `Cita`, `Diagnostico`) utilizando lógica de parsing.
* **Detección de Conflictos:** Cruza información para detectar, por ejemplo, choques de horarios en citas médicas o medir la carga de trabajo de los doctores.
* **Generación de Reportes Múltiples:** Exporta automáticamente **7 archivos** (HTML, DOT y PNG) a la carpeta que elija el usuario.

## Requisitos del Sistema

Para compilar y ejecutar este proyecto, necesitas tener instalado:
1. **Compilador C++** (GCC/MinGW, Clang o MSVC).
2. **CMake** (Versión 3.5 o superior).
3. **Qt Framework** (Módulo Core y Widgets).
4. **Graphviz** (El comando `dot` debe estar agregado a las variables de entorno / PATH del sistema operativo para generar la imagen PNG).

## Compilación y Ejecución

El proyecto utiliza CMake para facilitar la construcción multiplataforma. Desde la terminal en la raíz del proyecto:

1. **Configurar el proyecto:**
   ```bash
   cmake -B build