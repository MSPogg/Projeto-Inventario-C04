cmake_minimum_required(VERSION 3.10)

project(Projeto-Inventario-C04)

add_executable(Projeto-Inventario-C04 
    main.cpp
    src/inventario.cpp 
    src/menu.cpp
)

target_include_directories(Projeto-Inventario-C04 PRIVATE include)