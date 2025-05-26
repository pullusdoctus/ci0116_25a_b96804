/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>

#include "DoublyLinkedList.hpp"

template <typename DataType>

class ChainedHashTable {
 public:
  ChainedHashTable(size_t size) : size(size) { this->table.resize(size); }

  ~ChainedHashTable() { this->table.clear(); }

  void insert(const DataType& value) {
    size_t index = this->hash(value);
    this->table[index].insert(value);
  }

  DLListNode<DataType>* search(const DataType& value) const {
    size_t index = this->hash(value);
    return this->table[index].search(value);
  }

  void remove(const DataType& value) {
    size_t index = this->hash(value);
    this->table[index].remove(value);
  }

  size_t hash(const DataType& value) const
    { return (size_t)(value % this->size); }

  size_t getSize() const { return this->size; }

  std::vector<DLList<DataType>> getTable() const { return this->table; }

  void setTable(std::vector<DLList<DataType>>);

 private:
  size_t size;

  std::vector<DLList<DataType>> table;
};
