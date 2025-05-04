#include "./include/Ordenador.hpp"

#include <iostream>

void Ordenador::ordenamientoPorSeleccion(uint32_t *A, uint32_t n) const {
  for (uint32_t i = 0; i < n; ++i) {
  uint32_t m = i;
    for (uint32_t j = i + 1; j <= n; ++j) {
      if (A[j] < A[m]) {
        m = j;
      }
    }
    this->intercambiar(A, i, m);
  }
}
void Ordenador::ordenamientoPorInserccion(uint32_t *A, uint32_t n) const {
  for (uint32_t i = 1; i < n; ++i) {
    uint32_t key = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      --j;
    }
    A[j + 1] = key;
  }
}
void Ordenador::ordenamientoPorMezcla(uint32_t *A, uint32_t n) const {
  (void)A;
  (void)n;
  std::cout << "mezcla" << std::endl;
}
void Ordenador::ordenamientoPorMonticulos(uint32_t *A, uint32_t n) const {
  (void)A;
  (void)n;
  std::cout << "monticulos" << std::endl;
}
void Ordenador::ordenamientoRapido(uint32_t *A, uint32_t n) const {
  (void)A;
  (void)n;
  std::cout << "rapido" << std::endl;
}
void Ordenador::ordenamientoPorResiduos(uint32_t *A, uint32_t n) const {
  (void)A;
  (void)n;
  std::cout << "residuos" << std::endl;
}

// Metodos auxiliares
void Ordenador::intercambiar(uint32_t* A, uint32_t i, uint32_t j) const {
  uint32_t temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}
