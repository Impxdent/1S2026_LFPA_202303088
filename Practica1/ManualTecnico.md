# Manual Técnico  
## Sistema de Análisis Académico

**Lenguaje:** C++  
**Tipo:** Aplicación de consola  
**Autor:** André Escobar
**Fecha:** 03/03/2026

---

## 1. Introducción

El presente documento describe la estructura interna, funcionamiento y componentes del programa **Sistema de Análisis Académico**, desarrollado en lenguaje C++.  
El sistema permite cargar información desde archivos de texto, procesar datos académicos y generar reportes en formato HTML.

---

## 2. Requerimientos Técnicos

- Sistema Operativo: Windows
- Compilador: g++ (GNU Compiler Collection)  
- Estándar del lenguaje: C++11 o superior  
- Archivos requeridos:
  - estudiantes.lfp
  - cursos.lfp
  - notas.lfp
- Navegador web para visualizar los reportes HTML

---

## 3. Estructura General del Programa

El programa está organizado en los siguientes bloques:

1. Definición de estructuras
2. Manejo de memoria dinámica
3. Carga de archivos
4. Procesamiento de información
5. Generación de reportes
6. Menú principal

---

## 4. Estructuras Utilizadas

### 4.1 Estudiante

struct Estudiante{
    int carnet;
    string nombre;
    string apellido;
    string carrera;
    int semestre;
};

Almacena la información personal y académica de cada estudiante.

### 4.2 Curso

struct Curso{
    int codigo;
    string nombre;
    int creditos;
    int semestre;
    string carrera;
};

Representa los cursos disponibles dentro del sistema académico.

### 4.3 Nota

struct Nota{
    int carnet;
    int codigoCurso;
    float nota;
    string ciclo;
    int año;
};

Relaciona a un estudiante con un curso y su respectiva calificación.

---

## 5. Manejo de memoria dinámica

El sistema utiliza arreglos dinámicos mediante punteros:

Estudiante*estudiantes;
Curso*cursos;
Nota*notas;

Cada arreglo se inicializa dinámicamente y se controla mediante contadores y capacidades máximas.

---

## 6. Carga y procesamiento de archivos

Los archivos se leen línea por línea utilizando:

- ifstream
- getline
- stringstream
- separación por comas

---

## 7. Generación de reportes

El sistema genera reportes en formato HTML usando ofstream.

Reportes disponibles:
- Estadísticas por curso
- Rendimiento por estudiante
- Top 10 mejores estudiantes
- Cursos con mayor reprobación
- Análisis por carrera

---

## 8. Observaciónes técnicas

- No se utilizan contenedores STL avanzados
- El código está modularizado para facilitar mantenimiento
- El sistema cumple con los requerimentos académicos establecidos
