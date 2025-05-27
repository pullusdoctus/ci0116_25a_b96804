#include <BinarySearchTree.hpp>

template <typename DataType>
void BSTree<DataType>::insert(const DataType &value) {
  // avoid inserting duplicate values
  if (this->search(this->root, value)) return;
  // node being compared with z (new value)
  BSTreeNode<DataType>* x = this->root;
  // y will be parent of z
  BSTreeNode<DataType>* y = nullptr;
  // descend down to a leaf
  while (x) {
    y = x;
    if (value < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  // found the spot; insert the new value z with parent y
  BSTreeNode<DataType>* z =
    new BSTreeNode<DataType>(value, y, nullptr, nullptr);
  // tree was empty
  if (!y) this->root = z;
  // y adopts z as the correct-side child
  else if (z->key < y->key) y->left = z;
  else y->right = z;
}

template <typename DataType>
void BSTree<DataType>::remove(const DataType &value) {
  BSTreeNode<DataType>* z = this->search(this->root, value);
  // if the value wasn't found
  if (!z) return;
  // replace z with its right child
  if (!z->left) this->transplant(z, z->right);
  // replace z with its right child
  else if (!z->right) this->transplant(z, z->left);
  else {
    // y is z's successor
    BSTreeNode<DataType>* y = this->getMinimum(z->right);
    // is y farther down the tree?
    if (y != z->right) {
      // replace y with its right child
      this->transplant(y, y->right);
      // z's right child becomes y's right child
      y->right = z->right;
      y->right->parent = y;
    }
    // replace z by its successor y
    this->transplant(z, y);
    // give z's left child to y
    y->left = z->left;
    z->left->parent = y;
  }
  delete z;
}

template <typename DataType>
void BSTree<DataType>::transplant(
  BSTreeNode<DataType>* u, BSTreeNode<DataType>* v) {
  if (!u->parent) this->root = v;
  else if (u == u->parent->left) u->parent->left = v;
  else u->parent->right = v;
  if (v) v->parent = u->parent;
}

template <typename DataType>
void BSTree<DataType>::inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
  if (rootOfSubtree) {
    this->inorderWalk(rootOfSubtree->left);
    std::cout << rootOfSubtree->key << " ";
    this->inorderWalk(rootOfSubtree->right);
  }
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::search(
  const BSTreeNode<DataType> *rootOfSubtree, const DataType &value) const {
  if (!rootOfSubtree || value == rootOfSubtree->key) {
    return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
  }
  if (value < rootOfSubtree->key) {
    return this->search(rootOfSubtree->left, value);
  } else {
    return this->search(rootOfSubtree->right, value);
  }
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMinimum(
    const BSTreeNode<DataType> *rootOfSubtree) const {
  if (!rootOfSubtree) return nullptr;
  while (rootOfSubtree->left) rootOfSubtree = rootOfSubtree->left;
  return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMaximum(
    const BSTreeNode<DataType> *rootOfSubtree) const {
  if (!rootOfSubtree) return nullptr;
  while (rootOfSubtree->right) rootOfSubtree = rootOfSubtree->right;
  return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getSuccessor(
  const BSTreeNode<DataType> *node) const {
  if (!node) return nullptr;
  if (node->right) return this->getMinimum(node->right);
  else {
    BSTreeNode<DataType>* y = node->parent;
    while (y && node == y->right) {
      node = y;
      y = y->parent;
    }
    return y;
  }
}

template <typename DataType>
void BSTree<DataType>::fastinsert(size_t n) {
  // insert values in a balanced way
  this->root = balancedInsert(0, n - 1, nullptr);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::balancedInsert(
  size_t start, size_t end, BSTreeNode<DataType>* parent) {
  if (start > end) return nullptr;
  size_t middle = start + (end - start) / 2;
  // insert the middle value in this subtree's root
  BSTreeNode<DataType>* subroot =
    new BSTreeNode<DataType>(static_cast<DataType>(middle), parent,
                             nullptr, nullptr);
  // insert the left half's middle value as the root of the left subtree
  if (middle > start) {
    subroot->left = balancedInsert(start, middle - 1, subroot);
  }
  // insert the riht half's middle value as the root of the right subtree
  subroot->right = balancedInsert(middle + 1, end, subroot);
  return subroot;
}

template class BSTree<int>;
template class BSTreeNode<int>;
