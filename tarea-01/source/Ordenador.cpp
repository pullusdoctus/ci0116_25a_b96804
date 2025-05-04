#include <cmath>
#include <iostream>

#include "./include/Ordenador.hpp"
#include "./include/Heap.hpp"
#include "./include/Utilidades.hpp"

// Selection Sort
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
// Insertion Sort
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
// Merge Sort
void Ordenador::ordenamientoPorMezcla(uint32_t *A, uint32_t n) const {
  mergeSort(A, 0, n);
}
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
// Heap Sort
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
// Quicksort
void Ordenador::ordenamientoRapido(uint32_t *A, uint32_t n) const {
  quicksort(A, 0, n - 1);
}
void Ordenador::quicksort(uint32_t* A, int32_t p, int32_t r) const {
  if (p < r) {
    uint32_t q = partition(A, p, r);
    quicksort(A, p, q - 1);
    quicksort(A, q + 1, r);
  }
}
uint32_t Ordenador::partition(uint32_t* A, int32_t p, int32_t r) const {
  uint32_t q = A[r];  // Indice de pivote
  uint32_t i = p - 1;  // Indice de elementos menores al pivote
  Utilidades utilidades;
  for (int32_t j = p; j < r; ++j) {
    if (A[j] <= q) {
      ++i;
      utilidades.intercambiar(A, i, j);
    }
  }
  utilidades.intercambiar(A, i + 1, r);
  return i + 1;
}
// Radix Sort
void Ordenador::ordenamientoPorResiduos(uint32_t *A, uint32_t n) const {
  const uint32_t bits = sizeof(uint32_t) * 8;  // cantidad de bits para representar un uin32_t
  const uint32_t r = (uint32_t) log2(n);  // cantidad de bits por digito
  const uint32_t d = (uint32_t) std::ceil(bits / r);  // numero de digitos
  // por cada digito
  for (uint32_t i = 0; i < d; ++i) {
    countingSort(A, n, r, i);
  }
}
void Ordenador::countingSort(uint32_t* A, uint32_t n, uint32_t r, uint32_t exp) const {
  uint32_t k = 1u << r;  // 2^r dentro del rango de digitos
  uint32_t B[k];  // Arreglo de conteo
  uint32_t C[n];  // Arreglo ordenado
  for (uint32_t i = 0; i < k; ++i) {
    B[i] = 0;
  }
  // Contar veces que aparece un digito en 2^exp
  for (uint32_t i = 0; i < n; ++i) {
    uint32_t digit = (A[i] >> (r * exp)) & (k - 1);  // Extrae el digito especifico aplicandole una mascara AND y un shift a la derecha
    ++B[digit];
  }
  // Acumular veces
  for (uint32_t i = 1; i < k; ++i) {
    B[i] += B[i - 1];
  }
  // Construir arreglo ordenado
  for (int i = n - 1; i >= 0 ; --i) {
    uint32_t digit = (A[i] >> (r * exp )) & (k - 1);
    C[--B[digit]] = A[i];
  }
  // Copiar arreglo ordenado al original
  for (uint32_t i = 0; i < n; ++i) {
    A[i] = C[i];
  }
}
