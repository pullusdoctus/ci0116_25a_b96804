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
             DLListNode<DataType>* prev = nullptr);

  ~DLListNode();

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
  DLList();

  ~DLList() { clean(); };

  void insert(const DataType& value);

  DLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  void remove(DLListNode<DataType>* node);

  DLListNode<DataType>* getNil() const { return this->nil; }

 private:
  DLListNode<DataType>* nil;

  void clean();
};
