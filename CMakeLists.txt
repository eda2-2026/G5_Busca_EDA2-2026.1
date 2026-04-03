cmake_minimum_required(VERSION 4.1)

project(G5_Busca_EDA2_2026_1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../G5_Busca_EDA2-2026.1)
include_directories(../G5_Busca_EDA2-2026.1/src)

add_executable(G5_Busca_EDA2_2026_1
        ../G5_Busca_EDA2-2026.1/src/ArvoreBinaria.h
        ../G5_Busca_EDA2-2026.1/src/NoArvore.h
        ../G5_Busca_EDA2-2026.1/src/TabelaHash.h
        ../G5_Busca_EDA2-2026.1/src/Veiculo.h
        ../G5_Busca_EDA2-2026.1/src/main.cpp
        ../G5_Busca_EDA2-2026.1/src/GeradorDePlacas.h)