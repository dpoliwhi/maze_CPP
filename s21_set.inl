#include "s21_BinaryTree.h"

namespace s21 {

template <class Key, class T>
set<Key, T>::set() : BinaryTree<Key, T>::BinaryTree() {}

template <class Key, class T>
set<Key, T>::set(const set &s) : BinaryTree<Key, T>::BinaryTree(s) {}

template <class Key, class T>
set<Key, T>::set(set &&s) : BinaryTree<Key, T>::BinaryTree(std::move(s)) {}

template <class Key, class T>
set<Key, T>::set(std::initializer_list<value_type> const &items) {
  for (auto it : items) insert(it);
}

template <class Key, class T>
set<Key, T>::~set() {}

template <class Key, class T>
set<Key, T> &set<Key, T>::operator=(set &&s) {
  BinaryTree<Key, T>::operator=(std::move(s));
  return *this;
}

template <class Key, class T>
set<Key, T> &set<Key, T>::operator=(set &s) {
  BinaryTree<Key, T>::operator=(s);
  return *this;
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool> set<Key, T>::insert(const value_type &value) {
  std::pair<Key, T> ins = std::make_pair(value, 0);
  return this->insert_data_AC(ins);
}

template <class Key, class T>
typename set<Key, T>::iterator set<Key, T>::find(const Key &key) {
  return this->find_iterator(key);
}

template <class Key, class T>
template <class... Args>
std::vector<std::pair<typename BinaryTree<Key, T>::iterator, bool>> set<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<typename BinaryTree<Key, T>::iterator, bool>> res;
  std::vector<value_type> bufArgs = {args...};
  for (auto &i : bufArgs) {
    res.push_back(insert(i));
  }
  return res;
}

}  // namespace s21
