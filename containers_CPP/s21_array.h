#pragma once

#include <cmath>
#include <iostream>

namespace s21 {

template <class T, std::size_t N>
class array {
 private:
  T _data[N];

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  // Constructors
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &s);
  array(array &&s);
  ~array();

  // overload operators
  array<value_type, N> &operator=(array &&a);
  array<value_type, N> &operator=(const array &a);

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void fill(const_reference value);
  void swap(array &other);

  void Print_array();
};
}  // namespace s21

#include "s21_array.inl"
