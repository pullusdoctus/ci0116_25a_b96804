#include <iostream>

#include "./include/Ordenador.hpp"
#include "./include/Heap.hpp"
#include "./include/Utilidades.hpp"

void Ordenador::ordenamientoPorSeleccion(uint32_t *A, uint32_t n) const {
  for (uint32_t i = 0; i < n; ++i) {
  uint32_t m = i;
    for (uint32_t j = i + 1; j <= n; ++j) {
      if (A[j] < A[m]) {
        m = j;
      }
    }
    Utilidades utilidades;
    utilidades.intercambiar(A, i, m);
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
  mergeSort(A, 0, n);
}
void Ordenador::ordenamientoPorMonticulos(uint32_t *A, uint32_t n) const {
  // Construir Max Heap
  Heap* heap = new Heap(A, n);
  for (uint32_t i = n - 1; i > 0; --i) {
    Utilidades utilidades;
    utilidades.intercambiar(A, 0, i);
    heap->decreaseHeapSize();
    heap->maxHeapify(A, 0);
  }
  delete heap;
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

void Ordenador::mergeSort(uint32_t* A, uint32_t p, uint32_t r) const {
  if (p >= r) {
    return;
  }
  uint32_t q = p + (r - p) / 2;
  mergeSort(A, p, q);
  mergeSort(A, q + 1, r);
  merge(A, p, q, r);
}

void Ordenador::merge(uint32_t* A, uint32_t p, uint32_t q, uint32_t r) const {
  uint32_t a = q - p + 1;
  uint32_t b = r - q;
  uint32_t L[a];
  uint32_t R[b];
  for (uint32_t i = 0; i < a; ++i) {
    L[i] = A[p + i];
  }
  for (uint32_t j = 0; j < b; ++j) {
    R[j] = A[q + j + 1];
  }
  uint32_t i = 0;
  uint32_t j = 0;
  uint32_t k = p;
  while (i < a && j < b) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      ++i;
    } else {
      A[k] = R[j];
      ++j;
    }
    ++k;
  }
  while (i < a) {
    A[k] = L[i];
    ++i;
    ++k;
  }
  while (j < b) {
    A[k] = R[j];
    ++j;
    ++k;
  }
}
