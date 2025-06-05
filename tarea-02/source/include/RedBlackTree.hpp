/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#pragma once
#include <iostream>
#include <limits>

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
  enum colors getColor() const { return this->color; }

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

  void insert(const DataType &value) {
    // avoid inserting duplicate values
    RBTreeNode<DataType>* temp = this->search(this->root, value);
    if (temp != this->nil) return;  // FIXED: was just 'if (temp)', should check against nil
    // node being compared with the new node z
    RBTreeNode<DataType>* x = this->root;
    // y will be parent of z
    RBTreeNode<DataType>* y = this->nil;
    // the new node - set both of z's children as sentinels, starts red
    RBTreeNode<DataType>* z =
      new RBTreeNode<DataType>(value, this->nil, this->nil, this->nil, RED);
    while (x != this->nil) {
      y = x;
      if (z->key < x->key) x = x->left;
      else x = x->right;
    }
    // found the spot; insert z with parent y
    z->parent = y;
    if (y == this->nil) this->root = z;  // tree was empty
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    // correct violations of red-black properties
    this->insertFixup(z);
  }

  void insertFixup(RBTreeNode<DataType>* z) {
    while (z->parent->color == RED) {
      // is z's parent a left child?
      if (z->parent == z->parent->parent->left) {
        // y is z's uncle
        RBTreeNode<DataType>* y = z->parent->parent->right;
        // are z's parent and uncle both red?
        if (y->color == RED) {
          // case 1
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          // is z a right child?
          if (z == z->parent->right) {
            // case 2
            z = z->parent;
            this->leftRotate(z);
          }
          // case 3
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          this->rightRotate(z->parent->parent);
        }
      } else {  // z's parent is a right child
        // y is z's uncle - FIXED: was parent->right, should be parent->left
        RBTreeNode<DataType>* y = z->parent->parent->left;
        // are z's parent and uncle both red?
        if (y->color == RED) {
          // case 1
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          // is z a left child?
          if (z == z->parent->left) {
            //case 2
            z = z->parent;
            this->rightRotate(z);
          }
          // case 3
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          this->leftRotate(z->parent->parent);
        }
      }
    }
    this->root->color = BLACK;
  }

  void leftRotate(RBTreeNode<DataType>* x) {
    RBTreeNode<DataType>* y = x->right;
    // make y's left subtree x's right subtree
    x->right = y->left;
    // if y's left subtree is not empty
    // then x becomes the parent of the subtree's root
    if (y->left != this->nil) y->left->parent = x;
    // x's parent becomes y's parent
    y->parent = x->parent;
    // if x was the root then y becomes the root
    if (x->parent == this->nil) this->root = y;
    // otherwise, if x was a left child then y becomes a left child
    else if (x == x->parent->left) x->parent->left = y;
    // otherwise, y becomes a right child
    else x->parent->right = y;
    // make x y's left child
    y->left = x;
    x->parent = y;
  }

  void rightRotate(RBTreeNode<DataType>* x) {
    RBTreeNode<DataType>* y = x->left;
    // make y's right subtree x's left subtree
    x->left = y->right;
    // if y's right subtree is not empty
    // then x becomes the parent of the subtree's root
    if (y->right != this->nil) y->right->parent = x;
    // x's parent becomes y's parent
    y->parent = x->parent;
    // if x was the root then y becomes the root
    if (x->parent == this->nil) this->root = y;
    // otherwise, if x was a left child then y becomes a left child
    else if (x == x->parent->left) x->parent->left = y;
    // otherwise, y becomes a right child
    else x->parent->right = y;
    // make x y's right child
    y->right = x;
    x->parent = y;
  }

  void remove(const DataType &value) {
    RBTreeNode<DataType>* z = this->search(this->root, value);
    if (z == this->nil) return;
    RBTreeNode<DataType>* y = z;
    RBTreeNode<DataType>* x = nullptr;
    enum colors yOriginalColor = y->color;
    if (z->left == this->nil) {
      x = z->right;
      // replace z with its right child
      this->transplant(z, z->right);
    } else if (z->right == this->nil) {
      x = z->left;
      // replace z with its left child
      this->transplant(z, z->left);
    } else {
      // y is z's successor
      y = this->getMinimum(z->right);
      yOriginalColor = y->color;
      x = y->right;
      // is y farther down the tree?
      if (y != z->right) {
        // replace y with its right child
        this->transplant(y, y->right);
        // z's right child becomes y's right child
        y->right = z->right;
        y->right->parent = y;
      } else x->parent = y;  // in case x is nil
      // replace z by its successor y
      this->transplant(z, y);
      // give z's left child to y
      y->left = z->left;
      z->left->parent = y;
      y->color = z->color;
    }
    // if any red-black violations occured, correct them
    if (yOriginalColor == BLACK) this->removeFixup(x);
    delete z;
  }

  void transplant(RBTreeNode<DataType>* u, RBTreeNode<DataType>* v) {
    if (u->parent == this->nil) this->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
  }

  void removeFixup(RBTreeNode<DataType>* x) {
    while (x != this->root && x->color == BLACK) {
      // is x a left child?
      if (x == x->parent->left) {
        // x's sibling
        RBTreeNode<DataType>* w = x->parent->right;
        if (w->color == RED) {
          // case 1
          w->color = BLACK;
          x->parent->color = RED;
          this->leftRotate(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          // case 2
          w->color = RED;
          x = x->parent;
        } else {
          if (w->right->color == BLACK) {
            // case 3
            w->left->color = BLACK;
            w->color = RED;
            this->rightRotate(w);
            w = x->parent->right;
          }
          // case 4
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->right->color = BLACK;
          this->leftRotate(x->parent);
          x = this->root;
        }
      } else {  // x is a right child
        // x's sibling
        RBTreeNode<DataType>* w = x->parent->left;
        if (w->color == RED) {
          // case 1
          w->color = BLACK;
          x->parent->color = RED;
          this->rightRotate(x->parent);
          w = x->parent->left;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          // case 2
          w->color = RED;
          x = x->parent;
        } else {
          if (w->left->color == BLACK) {
            // case 3
            w->right->color = BLACK;
            w->color = RED;
            this->leftRotate(w);
            w = x->parent->left;
          }
          // case 4
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          this->rightRotate(x->parent);
          x = this->root;
        }
      }
    }
    x->color = BLACK;
  }

  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const {
    if (rootOfSubtree == this->nil || value == rootOfSubtree->key) {
      return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    }
    if (value < rootOfSubtree->key) {
      return this->search(rootOfSubtree->left, value);
    } else {
      return this->search(rootOfSubtree->right, value);
    }
  }

  RBTreeNode<DataType> *getMinimum(const RBTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree == this->nil) return const_cast<RBTreeNode<DataType>*>(this->nil);
    while (rootOfSubtree->left != this->nil)
      rootOfSubtree = rootOfSubtree->left;
    return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
  }

  RBTreeNode<DataType> *getMaximum(const RBTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree == this->nil) return const_cast<RBTreeNode<DataType>*>(this->nil);
    while (rootOfSubtree->right != this->nil)
      rootOfSubtree = rootOfSubtree->right;
    return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
  }

  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const {
    if (node == this->nil) return const_cast<RBTreeNode<DataType>*>(this->nil);
    if (node->right != this->nil) return this->getMinimum(node->right);
    else {
      RBTreeNode<DataType>* y = node->parent;
      while (y != this->nil && node == y->right) {
        node = y;
        y = y->parent;
      }
      return y;
    }
  }

  RBTreeNode<DataType> *getRoot() const { return this->root; }
  RBTreeNode<DataType> *getNil() const { return this->nil; }

 private:
  RBTreeNode<DataType> *root;
  RBTreeNode<DataType> *nil;
};
