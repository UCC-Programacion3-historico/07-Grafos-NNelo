cmake_minimum_required(VERSION 3.2)
project(07_Grafos)

set(CMAKE_CXX_STANDARD 14)

# Agrego todos los test.
add_subdirectory(test)

set(SOURCE_FILES_01 Ej-01/main.cpp Ej-01/GrafoMatriz.h)
add_executable(Ej-01 ${SOURCE_FILES_01})

set(SOURCE_FILES_02 Ej-02/main.cpp Ej-02/GrafoEnlazado.h Ej-02/Lista.h Ej-02/Vertice.h Ej-02/Arco.h)
add_executable(Ej-02 ${SOURCE_FILES_02})

set(SOURCE_FILES_03 Ej-03/main.cpp)
add_executable(Ej-03 ${SOURCE_FILES_03})
