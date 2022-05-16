#pragma once

#include <cmath>
#include <iostream>
#include <string>

#include "s21_BinaryTree.h"

namespace s21 {

template <class Key, class T = int>
class set : public BinaryTree<Key, T> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Node = _NodeRBT<Key, T> *;
  typedef typename BinaryTree<Key, T>::iterator iterator;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set<Key, T> &operator=(set &&s);
  set<Key, T> &operator=(set &s);

  // modifiers
  std::pair<iterator, bool> insert(const value_type &value);
  // lookup
  iterator find(const Key &key);

  // bonus
  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

}  // namespace s21

#include "s21_set.inl"
