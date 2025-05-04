#include "./include/Heap.hpp"
#include "./include/Utilidades.hpp"

// Construye el montículo máximo comenzando desde el último padre no hoja (n/2 -1)
// y aplicando maxHeapify en orden inverso para garantizar propiedad de montículo
Heap::Heap(uint32_t*A, uint32_t n) : heapSize(n) {
  for (int i = n / 2 - 1; i >= 0; --i) {
    maxHeapify(A, i);
  }
}

uint32_t Heap::findParent(uint32_t i) {
  return i / 2;
}
uint32_t Heap::findLeftChild(uint32_t i) {
  return 2 * i + 1;
}
uint32_t Heap::findRightChild(uint32_t i) {
  return 2 * i + 2;
}

// Implementación iterativa para mantener la propiedad de montículo máximo
// Compara el nodo con sus hijos y realiza swaps recursivamente hacia abajo
void Heap::maxHeapify(uint32_t* A, uint32_t i) {
  uint32_t l = findLeftChild(i);
  uint32_t r = findRightChild(i);
  uint32_t largest = i;
  // Encontrar el mayor entre nodo actual y sus hijos
  if (l < this->heapSize && A[l] > A[largest]) {
    largest = l;
  }
  if (r < this->heapSize && A[r] > A[largest]) {
    largest = r;
  }
  // Si el mayor no es el nodo actual, intercambiar y continuar
  if (largest != i) {
    Utilidades utilidades;
    utilidades.intercambiar(A, i, largest);
    maxHeapify(A, largest);
  }
}

void Heap::decreaseHeapSize() {
  --this->heapSize;
}
