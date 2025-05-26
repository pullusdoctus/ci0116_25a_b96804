/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
template <typename DataType>
class DLList;

template <typename DataType>
class DLListNode {
 public:
  friend class DLList<DataType>;

  DLListNode() : next(nullptr), prev(nullptr) {}

  DLListNode(const DataType& value, DLListNode<DataType>* next = nullptr,
             DLListNode<DataType>* prev = nullptr)
    : key(value), next(next), prev(prev) {}

  ~DLListNode() {
    this->next = nullptr;
    this->prev = nullptr;
  }

  DataType getKey() const { return this->key; }

  DLListNode<DataType>* getPrev() const { return this->prev; }

  DLListNode<DataType>* getNext() const { return this->next; }

  void setKey(DataType key) { this->key = key; }

  void setPrev(DLListNode<DataType>* prev) { this->prev = prev; }

  void setNext(DLListNode<DataType>* next) { this->next = next; }

 private:
  DataType key;

  DLListNode<DataType>* next;

  DLListNode<DataType>* prev;
};

template <typename DataType>
class DLList {
 public:
  DLList() {
    DLListNode<DataType>* nil = new DLListNode<DataType>();
    this->nil = nil;
    this->nil->next = nil;
    this->nil->prev = nil;
  }

  ~DLList() { clean(); };

  void insert(const DataType& value) {
    // newNode has the old head as next, nil as prev
    DLListNode<DataType>* newNode
      = new DLListNode<DataType>(value, this->nil->next, this->nil);
    // newNode is the head
    this->nil->next = newNode;
  }

  DLListNode<DataType>* search(const DataType& value) const {
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

  void remove(const DataType& value) {
    DLListNode<DataType>* toRemove = this->search(value);
    // node not found
    if (toRemove == this->nil) return;
    // delete the node
    this->remove(toRemove);
  }

  void remove(DLListNode<DataType>* node) {
    DLListNode<DataType>* prev = node->prev;
    DLListNode<DataType>* next = node->next;
    prev->next = next;
    next->prev = prev;
    delete node;
  }

  DLListNode<DataType>* getNil() const { return this->nil; }

 private:
  DLListNode<DataType>* nil;

  void clean() {
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
};
