#pragma once

#include <cmath>
#include <iostream>

namespace s21 {

template <class T>
class vector {
 private:
  size_t _size;
  size_t _capacity;
  T *_data;
  struct vec {
    T *_end;
    T *_begin;
  };
  vec v;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  void Reserve_more_capacity(size_type size, bool shrink);
  void Destroy_vector();

 public:
  // Constructors
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &s);
  vector(vector &&s);
  ~vector();

  // overload operators
  vector<value_type> &operator=(vector<value_type> &&s);
  vector<value_type> &operator=(const vector<T> &s);

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
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // bonus
  void emplace_back() {}
  template <class TYPE, class... Args>
  void emplace_back(TYPE data, Args... args);

  iterator emplace(iterator pos) { return pos; }
  template <class TYPE, class... Args>
  iterator emplace(iterator pos, TYPE data, Args... args);
};
}  // namespace s21

#include "s21_vector.inl"
