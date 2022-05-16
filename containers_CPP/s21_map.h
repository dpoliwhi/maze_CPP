#pragma once

#include <iostream>
#include "s21_BinaryTree.h"

namespace s21 {

template <class Key, class T>
class map : public BinaryTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Node = _NodeRBT<Key, T> *;
  typedef typename BinaryTree<Key, T>::iterator iterator;

  // constructors
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map<Key, T> &operator=(map &&m);
  map<Key, T> &operator=(map &m);

  // element access
  T &at(const Key &key);
  T &operator[](const Key &key);

  // modifiers
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  // bonus
  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);
};

}  // namespace s21

#include "s21_map.inl"
