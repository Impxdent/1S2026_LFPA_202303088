cmake_minimum_required(VERSION 3.16)
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
    src/SyntaxAnalyzer.cpp
    src/Token.cpp
    src/ErrorManager.cpp
    src/ReportGenerator.cpp
)

target_include_directories(TaskScriptProject PRIVATE src)

target_link_libraries(TaskScriptProject PRIVATE Qt6::Widgets)