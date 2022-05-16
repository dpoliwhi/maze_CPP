#include "s21_BinaryTree.h"

namespace s21 {

template <class Key, class T>
BinaryTree<Key, T>::BinaryTree() {}

template <class Key, class T>
BinaryTree<Key, T>::~BinaryTree() {}

template <class Key, class T>
BinaryTree<Key, T>::BinaryTree(std::initializer_list<value_type> const& items) {
  for (auto& it : items) {
    _tree.insert_data(it);
  }
}

template <class Key, class T>
BinaryTree<Key, T>::BinaryTree(const BinaryTree& other) {
  preorder_insert(other._tree.root, other._tree.leaf);
}

template <class Key, class T>
BinaryTree<Key, T>& BinaryTree<Key, T>::operator=(BinaryTree<Key, T>&& other) {
  clear();
  merge(other);
  other.clear();
  return *this;
}

template <class Key, class T>
BinaryTree<Key, T>& BinaryTree<Key, T>::operator=(BinaryTree<Key, T>& other) {
  clear();
  merge(other);
  return *this;
}

template <class Key, class T>
BinaryTree<Key, T>::BinaryTree(BinaryTree&& other) : _tree(other._tree) {
  other._tree.set_size(0);
  other._tree.leaf = nullptr;
  other._tree.root = nullptr;
}

// iterator
template <class Key, class T>
BinaryTree<Key, T>::iterator::iterator() : _node(nullptr), _leaf(nullptr) {}

template <class Key, class T>
BinaryTree<Key, T>::iterator::iterator(Node node, Node leaf) : _node(node), _leaf(leaf) {}

template <class Key, class T>
BinaryTree<Key, T>::iterator::iterator(const iterator& other) : _node(other._node), _leaf(other._leaf) {}

template <class Key, class T>
BinaryTree<Key, T>::iterator::~iterator() {
  _node = nullptr;
  _leaf = nullptr;
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::begin() {
  if (_tree.size() != 0) {
    Node buf = find_min_leaf(_tree.root, _tree.leaf);
    iterator res(buf, _tree.leaf);
    return res;
  } else {
    Node buf = new _NodeRBT<Key, T>;
    buf->data = std::make_pair(0, 0);
    iterator res(buf, _tree.leaf);
    return res;
  }
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::end() {
  return iterator(_tree.leaf, _tree.leaf);
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool> BinaryTree<Key, T>::insert_data_AC(
    const value_type& data) {
  std::pair<Node, bool> buf = _tree.insert_data(data);
  iterator iter(buf.first, _tree.leaf);
  std::pair<iterator, bool> res = std::make_pair(iter, buf.second);
  return res;
}

template <class Key, class T>
_NodeRBT<Key, T>* next_element(_NodeRBT<Key, T>* node, _NodeRBT<Key, T>* leaf) {
  if (node->right != leaf) {
    return find_min_leaf(node->right, leaf);
  }
  _NodeRBT<Key, T>* res = node->parent;
  while (res != leaf && node == res->right) {
    node = res;
    res = res->parent;
  }
  return res;
}

template <class Key, class T>
_NodeRBT<Key, T>* previos_element(_NodeRBT<Key, T>* node, _NodeRBT<Key, T>* leaf) {
  if (node->left != leaf) {
    return find_max_leaf(node->left, leaf);
  }
  _NodeRBT<Key, T>* res = node->parent;
  while (res != leaf && node == res->left) {
    node = res;
    res = res->parent;
  }
  return res;
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator& BinaryTree<Key, T>::iterator::operator++() {
  if (_node != _leaf && _node != _leaf->parent) {
    _node = next_element(_node, _leaf);
  } else if (_node == _leaf) {
    _node = _leaf->parent;
  } else {
    _node->data = std::make_pair(0, 0);
  }
  return *this;
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator& BinaryTree<Key, T>::iterator::operator--() {
  if (_node != _leaf)
    _node = previos_element(_node, _leaf);
  else
    _node = _leaf->parent;
  return *this;
}

template <class Key, class T>
bool BinaryTree<Key, T>::iterator::operator==(const iterator& other) {
  return _node == other._node;
}

template <class Key, class T>
bool BinaryTree<Key, T>::iterator::operator!=(const iterator& other) {
  return _node != other._node;
}

template <class Key, class T>
void BinaryTree<Key, T>::preorder_insert(Node node, Node leaf) {
  if (node != leaf) {
    insert_data_AC(node->data);
    preorder_insert(node->right, leaf);
    preorder_insert(node->left, leaf);
  }
}

template <class Key, class T>
size_t BinaryTree<Key, T>::size() {
  return _tree.size();
}

template <class Key, class T>
bool BinaryTree<Key, T>::empty() {
  return (_tree.size() < 1);
}

template <class Key, class T>
size_t BinaryTree<Key, T>::max_size() {
  return pow(2, (64 - sizeof(T)) - 1);
}

template <class Key, class T>
void BinaryTree<Key, T>::clear() {
  if (size()) {
    _tree.clear_tree();
    _tree.set_size(0);
    _tree.root = nullptr;
    _tree.leaf = nullptr;
  }
}

template <class Key, class T>
void BinaryTree<Key, T>::erase(iterator pos) {
  std::pair<Key, T> del_pair = *pos;
  _tree.deleteNode(pos._node, del_pair.first);
  _tree.set_size(_tree.size() - 1);
}

template <class Key, class T>
void BinaryTree<Key, T>::print_tree() {
  _tree.printTree();
}

template <class Key, class T>
bool BinaryTree<Key, T>::contains(const Key& key) {
  std::pair<Node, bool> check_pair = _tree.find_by_key(key);
  return check_pair.second;
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::find_iterator(const Key& key) {
  return iterator(_tree.find_by_key(key).first, _tree.leaf);
}

template <class Key, class T>
void BinaryTree<Key, T>::swap(BinaryTree& other) {
  BinaryTree<Key, T> buf_main(*this);
  BinaryTree<Key, T> buf_other(other);
  other.clear();
  this->clear();
  std::swap(other._tree, buf_main._tree);
  std::swap(_tree, buf_other._tree);
}

template <class Key, class T>
void BinaryTree<Key, T>::merge(BinaryTree& other) {
  iterator iter(other.end());
  while (iter != other.begin()) {
    --iter;
    insert_data_AC(*iter);
  }
}

}  // namespace s21
