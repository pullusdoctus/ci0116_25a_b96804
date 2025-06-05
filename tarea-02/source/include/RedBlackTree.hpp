/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#pragma once

enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  RBTreeNode() = default;

  RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent = nullptr,
             RBTreeNode<DataType> *left = nullptr,
             RBTreeNode<DataType> *right = nullptr, enum colors c = RED)
    : key(value), parent(parent), left(left), right(right), color(c) {}

  ~RBTreeNode() {
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
  }

  DataType getKey() const { return this->key; }

  RBTreeNode<DataType> *getParent() const { return this->parent; }

  RBTreeNode<DataType> *getLeft() const { return this->left; }

  RBTreeNode<DataType> *getRight() const { return this->right; }

  void setKey(DataType key) { this->key = key; }

  void setParent(RBTreeNode<DataType> *parent) { this->parent = parent; }

  void setLeft(RBTreeNode<DataType> *left) { this->left = left; }

  void setRight(RBTreeNode<DataType> *right) { this->right = right; }

  void setColor(enum colors newColor) { this->color = newColor; }

 private:
  DataType key;

  RBTreeNode<DataType> *parent;

  RBTreeNode<DataType> *left;

  RBTreeNode<DataType> *right;

  enum colors color;
};

template <typename DataType>
class RBTree {
 public:
  RBTree() {
    this->nil = new RBTreeNode<DataType>();
    this->nil->parent = this->nil;
    this->nil->left = this->nil;
    this->nil->right = this->nil;
    this->nil->color = BLACK;
    this->root = this->nil;
  }

  ~RBTree() {
    while (this->root != this->nil) this->remove(this->root->key);
    delete this->nil;
    this->root = nullptr;
    this->nil = nullptr;
  }

  void insert(const DataType &value);

  void insertFixup(RBTreeNode<DataType>* z);

  void leftRotate(RBTreeNode<DataType>* x);

  void rightRotate(RBTreeNode<DataType>* x);

  void remove(const DataType &value);

  void transplant(RBTreeNode<DataType>* u, RBTreeNode<DataType>* v);

  void removeFixup(RBTreeNode<DataType>* x);

  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  RBTreeNode<DataType> *getMinimum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  RBTreeNode<DataType> *getMaximum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const;

  RBTreeNode<DataType> *getRoot() const { return this->root; }

  RBTreeNode<DataType> *getNil() const { return this->nil; }


 private:
  RBTreeNode<DataType> *root;

  RBTreeNode<DataType> *nil;
};
