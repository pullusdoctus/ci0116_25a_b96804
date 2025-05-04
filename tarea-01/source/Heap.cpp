#include "./include/Heap.hpp"
#include "./include/Utilidades.hpp"

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

void Heap::maxHeapify(uint32_t* A, uint32_t i) {
  uint32_t l = findLeftChild(i);
  uint32_t r = findRightChild(i);
  uint32_t largest = i;
  if (l < this->heapSize && A[l] > A[largest]) {
    largest = l;
  }
  if (r < this->heapSize && A[r] > A[largest]) {
    largest = r;
  }
  if (largest != i) {
    Utilidades utilidades;
    utilidades.intercambiar(A, i, largest);
    maxHeapify(A, largest);
  }
}

void Heap::decreaseHeapSize() {
  --this->heapSize;
}
