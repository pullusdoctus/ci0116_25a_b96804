#include <DoublyLinkedList.hpp>

template <typename DataType>
DLListNode<DataType>::DLListNode(
  const DataType& value, DLListNode<DataType>* next,
  DLListNode<DataType>* prev)
  : key(value), next(next), prev(prev) {}

template <typename DataType>
DLListNode<DataType>::~DLListNode() {
  this->next = nullptr;
  this->prev = nullptr;
}

template <typename DataType>
DLList<DataType>::DLList() {
  DLListNode<DataType>* nil = new DLListNode<DataType>();
  this->nil = nil;
  this->nil->next = nil;
  this->nil->prev = nil;
}

template <typename DataType>
void DLList<DataType>::insert(const DataType& value) {
  // newNode has the old head as next, nil as prev
  DLListNode<DataType>* oldHead = this->nil->next;
  DLListNode<DataType>* newNode
    = new DLListNode<DataType>(value, this->nil->next, this->nil);
  // newNode is the head
  this->nil->next = newNode;
  if (oldHead != this->nil) oldHead->prev = newNode;
}

template <typename DataType>
DLListNode<DataType>* DLList<DataType>::search(const DataType& value) const {
  // start searching from the head
  DLListNode<DataType>* current = this->nil->next;
  // travel the list searching for the node
  while (current != this->nil && current->key != value) {
    current = current->next;
  }
  // return the current node
  // if the value was found in a node, a valid node is returned
  // else, nil is returned
  return current;
}

template <typename DataType>
void DLList<DataType>::remove(const DataType& value) {
  DLListNode<DataType>* toRemove = this->search(value);
  // node not found
  if (toRemove == this->nil) return;
  // delete the node
  this->remove(toRemove);
}

template <typename DataType>
void DLList<DataType>::remove(DLListNode<DataType>* node) {
  DLListNode<DataType>* prev = node->prev;
  DLListNode<DataType>* next = node->next;
  prev->next = next;
  next->prev = prev;
  delete node;
}

template <typename DataType>
void DLList<DataType>::clean() {
  // delete all nodes, starting from the head
  DLListNode<DataType>* current = this->nil->next;
  // delete all nodes not nil
  while (current != this->nil) {
    DLListNode<DataType>* toRemove = current;
    current = current->next;
    this->remove(toRemove);
  }
  // delete nil
  delete this->nil;
  this->nil->next = nullptr;
  this->nil->prev = nullptr;
}

template class DLListNode<int>;
template class DLList<int>;
