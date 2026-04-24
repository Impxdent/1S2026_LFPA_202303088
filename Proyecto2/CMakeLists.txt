cmake_minimum_required(VERSION 3.10)
project(TaskScriptProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED) 

add_executable(TaskScriptProject
    src/main.cpp
    src/MainWindow.cpp
    src/LexicalAnalyzer.cpp
    src/Token.cpp
    src/ErrorManager.cpp
)

target_link_libraries(TaskScriptProject Qt6::Widgets)