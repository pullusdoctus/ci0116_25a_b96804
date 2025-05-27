/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#pragma once
template <typename DataType>
class SLList;

template <typename DataType>
class SLListNode {
 public:
  friend class SLList<DataType>;

  SLListNode() : next(nullptr) {};

  SLListNode(const DataType& value, SLListNode<DataType>* next = nullptr)
    : key(value), next(next) {};

  ~SLListNode() { this->next = nullptr; };

  DataType getKey() const { return this->key; };

  SLListNode<DataType>* getNext() const { return this->next; };

  void setKey(DataType key) { this->key = key; };

  void setNext(SLListNode<DataType>* newNode) { this->next = newNode; };

 private:
  DataType key;

  SLListNode<DataType>* next;
};

template <typename DataType>
class SLList {
 public:
  SLList() = default;

  ~SLList() { clean(); };

  void insert(const DataType& value);

  SLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  SLListNode<DataType>* getNil() const { return this->nil; };
  
 private:
  SLListNode<DataType>* nil;

  void clean() {
    // while a head exists
    while (this->nil) {
      // delete the head
      this->remove(this->nil->key);
    }
    this->nil = nullptr;
  };
};
