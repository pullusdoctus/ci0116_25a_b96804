#pragma once

#include <cstdint>

class Heap {
  private:
    uint32_t heapSize;

  public:
    Heap(uint32_t* A, uint32_t n);

    uint32_t findParent(uint32_t i);
    uint32_t findLeftChild(uint32_t i);
    uint32_t findRightChild(uint32_t i);

    void maxHeapify(uint32_t* A, uint32_t i);
    void decreaseHeapSize();
};
