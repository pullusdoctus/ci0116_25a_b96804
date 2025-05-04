#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#include "Ordenador.hpp"

class Utilidades {
  public:
    void generarArreglo(uint32_t* A, uint32_t n);
    void copiarArreglo(const uint32_t* A, uint32_t* B, uint32_t n);
    double ordenar(const Ordenador& ordenador, uint32_t* A, uint32_t N, int algoritmo);
    std::string nombreAlgoritmo(int algoritmo);
};
