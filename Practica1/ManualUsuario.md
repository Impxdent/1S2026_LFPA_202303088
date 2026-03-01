# Manual de Usuario  
## Sistema de Análisis Académico

---

## 1. Introducción

El **Sistema de Análisis Académico** es una aplicación de consola desarrollada en C++ que permite cargar información académica desde archivos de texto y generar reportes en formato HTML para su análisis.

El sistema procesa:
- Estudiantes
- Cursos
- Notas académicas

Y genera distintos reportes estadísticos.

---

## 2. Requisitos del Sistema

- Sistema Operativo: Windows o Linux  
- Compilador C++: `g++`  
- Navegador web para visualizar reportes HTML  
- Archivos de entrada ubicados en la misma carpeta del programa:
  - `estudiantes.lfp`
  - `cursos.lfp`
  - `notas.lfp`

---

## 3. Compilación del Programa

Abra una terminal en la carpeta del proyecto y ejecute: **g++ main.cpp -o sistema**.

---

## 4. Ejecución del programa

En la terminal escriba **./sistema** y el programa se ejecutará.

---

## 5. Menú principal

Al ejecutarse el programa, se abrirá el menú intuitivo, y solo se presiona la tecla que corresponta a la opción deseada.

---

## 6. Carga de archivos

Se agregan archivos a la carpeta para que el programa los lea y muestre sus datos, para esto se debe ingresar el nombre y la ruta correcta del archivo.

---

## 7. Generación de reportes

Una vez se haya agregado los archivos, los reportes se podrán generar extrayendo los datos de dichos archivos, y los mostrará de manera organizada en una tabla.

---

## 8. Visualización de reportes

Al seleccionar la opción en el menú y generar el reporte deseado, este se guardará en la carpeta donde se encuentra el proyecto, y al localizar el archivo y hacer doble clic, se podrá acceder a su información.

---

## 9. Salir del programa

Al elegir la última opción, la ejecución del programa finalizará.

---

## 10. Recomendaciones

- Cargar archivos en el orden correcto
- Verificar el formato de los archivos
- No ejecutar reportes sin datos cargados
- Mantener los archivos en la misma carpeta del ejecutable

---

## 11. Conclusión

El sistema permite analizar información académica de forma eficiente y generar reportes claros, cumpliendo con los objetivos del proyecto.
