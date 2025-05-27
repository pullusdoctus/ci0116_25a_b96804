/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstddef>
#include <iostream>

template <typename DataType>
class BSTree;

template <typename DataType>
class BSTreeNode {
 public:
  friend class BSTree<DataType>;

  BSTreeNode() = default;

  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr)
  : key(value), parent(parent), left(left), right(right) {}

  ~BSTreeNode() {
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
  }

  DataType getKey() const { return this->key; }

  BSTreeNode<DataType> *getParent() const { return this->parent; }

  BSTreeNode<DataType> *getLeft() const { return this->left; }

  BSTreeNode<DataType> *getRight() const { return this->right; }

  void setParent(BSTreeNode<DataType> *parent) { this->parent = parent; }

  void setLeft(BSTreeNode<DataType> *left) { this->left = left; }

  void setRight(BSTreeNode<DataType> *right) { this->right = right; }

 private:
  DataType key;

  BSTreeNode<DataType> *parent = nullptr;

  BSTreeNode<DataType> *left = nullptr;

  BSTreeNode<DataType> *right = nullptr;
};

template <typename DataType>
class BSTree {
 public:
  BSTree() : root(nullptr) {}

  ~BSTree() {
    while (this->root) this->remove(this->root->key);
    this->root = nullptr;
  }

  void insert(const DataType &value);

  void remove(const DataType &value);

  void transplant(BSTreeNode<DataType>* u, BSTreeNode<DataType>* v);

  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getMaximum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const;

  BSTreeNode<DataType> *getRoot() const { return this->root; }

  void fastinsert(size_t n);

  BSTreeNode<DataType>* balancedInsert(size_t start, size_t end,
                                       BSTreeNode<DataType>* parent);
  
 private:
  BSTreeNode<DataType> *root = nullptr;
};
