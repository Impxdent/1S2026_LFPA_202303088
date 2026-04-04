cmake_minimum_required(VERSION 3.16)
project(MedLexer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(MedLexer
    src/main.cpp
    #src/Token.cpp 
    src/Token.h
    src/LexicalAnalyzer.cpp src/LexicalAnalyzer.h
    src/ReportGenerator.cpp src/ReportGenerator.h
    src/MainWindow.cpp src/MainWindow.h
    src/DataExtractor.cpp src/DataExtractor.h
)

target_link_libraries(MedLexer PRIVATE Qt6::Widgets)