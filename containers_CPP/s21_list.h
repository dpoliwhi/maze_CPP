#pragma once

#include <cmath>
#include <iostream>

namespace s21 {

template <class T>
class list {
 private:
  struct Node {
    T _data;
    Node *_prev;
    Node *_next;
  };
  size_t _size;
  Node *_end;
  Node *_begin;

 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  typedef typename list<T>::ListIterator iterator;
  typedef typename list<T>::ListConstIterator const_iterator;

  class ListIterator {
   public:
    Node *_iter;
    Node *_head;
    Node *_tail;

    // constructors
    ListIterator();
    explicit ListIterator(const list<T> &other);

    // operators
    T operator*() { return _iter ? _iter->_data : 0; }
    void operator++();
    void operator--();
    bool operator!=(const ListIterator &other);
    bool operator==(const ListIterator &other);

    // other methods
    Node *get_node() { return _iter; }
  };

  class ListConstIterator {
   public:
    Node *_iter;
    Node *_head;
    Node *_tail;

    // constructors
    ListConstIterator();
    explicit ListConstIterator(const list<T> &other);

    // operators
    T operator*() { return _iter ? _iter->_data : 0; }
    void operator++();
    void operator--();
    bool operator!=(const ListConstIterator &other);
    bool operator==(const ListConstIterator &other);

    // other methods
    Node *get_node() { return _iter; }
  };

 public:
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list<value_type> &operator=(list<value_type> &&l);
  list<value_type> &operator=(const list<T> &l);

  // Element access
  const_reference front();
  const_reference back();

  // iterators
  iterator begin();
  iterator end();

  // const iterators
  const_iterator cbegin();
  const_iterator cend();

  // capacity
  bool empty();
  size_type size();
  size_type max_size();

  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  // bonus
  void emplace_front() {}
  template <class TYPE, class... Args>
  void emplace_front(TYPE data, Args... args);

  void emplace_back() {}
  template <class TYPE, class... Args>
  void emplace_back(TYPE data, Args... args);

  iterator emplace(iterator pos) { return pos; }
  template <class TYPE, class... Args>
  iterator emplace(iterator pos, TYPE data, Args... args);
};
}  // namespace s21

#include "s21_list.inl"
