#include <ChainedHashTable.hpp>

template <typename DataType>
void ChainedHashTable<DataType>::insert(const DataType& value) {
  size_t index = this->hash(value);
  this->table[index].insert(value);
}

template <typename DataType>
DLListNode<DataType>* ChainedHashTable<DataType>::search(
  const DataType& value) const {
  size_t index = this->hash(value);
  return this->table[index].search(value);
}

template <typename DataType>
void ChainedHashTable<DataType>::remove(const DataType& value) {
  size_t index = this->hash(value);
  this->table[index].remove(value);
}

template class ChainedHashTable<int>;
