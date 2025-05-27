#include <SinglyLinkedList.hpp>

template <typename DataType>
void SLList<DataType>::insert(const DataType& value) {
  SLListNode<DataType>* newNode = new SLListNode<DataType>(value);
  newNode->next = this->nil;
  this->nil = newNode;
};

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::search(const DataType& value) const {
  SLListNode<DataType>* current = this->nil;
  // travel the list searching for the node
  while (current && current->key != value) {
    current = current->next;
  }
  // if current node is a valid node, return its value
  if (current) {
    return current;
  }
  // value not found
  return nullptr;
};

template <typename DataType>
void SLList<DataType>::remove(const DataType& value) {
  SLListNode<DataType>* toRemove = search(value);
  // node not found
  if (toRemove == nullptr) {
    return;
  }
  // if the node to remove is the head
  if (toRemove == this->nil) {
    this->nil = toRemove->next;
    delete toRemove;
    return;
  }
  // else, find its previous node
  SLListNode<DataType>* current = this->nil;
  while (current && current->next != toRemove) {
    current = current->next;
  }
  // if the previous node was found
  if (current) {
    current->next = toRemove->next;
    delete toRemove;
  }
};

template class SLListNode<int>;
template class SLList<int>;
