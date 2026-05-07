# TaskScript Analyzer 

Un analizador léxico y sintáctico desarrollado en **C++** y **Qt Framework**, diseñado para interpretar un Lenguaje Específico de Dominio (DSL) para la definición y estructuración de tableros Kanban. 

Este compilador lee archivos `.task`, valida su estructura gramatical y genera visualizaciones interactivas (HTML) y árboles de derivación (AST mediante Graphviz).

## Características Principales

* **Análisis Léxico:** Autómata Finito Determinista (AFD) propio que tokeniza la entrada y maneja errores por caracteres inválidos o cadenas sin cerrar.
* **Análisis Sintáctico:** Parser Descendente Recursivo Predictivo (LL(1)) sin recursividad por la izquierda.
* **Recuperación de Errores:** Implementación de *Panic Mode* a nivel de token. El programa no se detiene ante el primer error; descarta tokens hasta sincronizarse y reporta todos los fallos al final.
* **Generación de AST:** Construcción de un Árbol de Análisis Sintáctico Abstracto en memoria utilizando punteros inteligentes (`std::shared_ptr`), exportable a formato `.dot`.
* **Reportes Visuales:** Generación automática de archivos HTML/CSS para visualizar el tablero Kanban y las cargas de trabajo sin depender de software adicional.
* **Interfaz Gráfica (GUI):** Entorno amigable construido en Qt con editor de texto integrado, resaltado básico y tablas de visualización en tiempo real para Tokens y Errores.

## Tecnologías Utilizadas

* **Lenguaje:** C++ (Estándar C++17 o superior)
* **Framework UI:** Qt 5 / Qt 6
* **Herramientas Externas:** Graphviz (para renderizar los archivos `.dot` del Árbol de Derivación)

## Instalación y Uso

### Prerrequisitos
1. Instalar [Qt Creator](https://www.qt.io/download).
2. Instalar un compilador compatible con C++ (MinGW en Windows o GCC/Clang en Linux/macOS).
3. Instalar [Graphviz](https://graphviz.org/download/) y asegurarse de agregar `dot` a las variables de entorno del sistema (PATH).
