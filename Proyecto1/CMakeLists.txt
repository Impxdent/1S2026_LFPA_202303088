cmake_minimum_required(VERSION 3.16)
project(MedLexer VERSION 1.0 LANGUAGES CXX)

# Requerimiento estricto: C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración automática de Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Buscar las librerías de Qt (Ajusta a Qt5 si usas esa versión)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Archivos fuente del proyecto (iremos agregando los demás paso a paso)
add_executable(MedLexer
    src/main.cpp
    src/Token.cpp src/Token.h
    src/ErrorManager.cpp src/ErrorManager.h
    # src/LexicalAnalyzer.cpp src/LexicalAnalyzer.h
    # src/ReportGenerator.cpp src/ReportGenerator.h
    src/MainWindow.cpp src/MainWindow.h
)

target_link_libraries(MedLexer PRIVATE Qt6::Widgets)