#pragma once
#include <cmath>

#include "s21_rbtree.h"

namespace s21 {

template <class Key, class T>
class BinaryTree {
 public:
  class iterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Node = _NodeRBT<Key, T> *;
  //typedef typename BinaryTree<Key, T>::iterator iterator;

  class iterator {
   public:
    Node _node;
    Node _leaf;
    // constructors
    iterator();
    iterator(Node node, Node leaf);
    iterator(const iterator &other);
    ~iterator();
    // operators
    value_type operator*() { return _node->data; }
    iterator &operator++();
    iterator &operator--();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
  };

 protected:
  RedBlackTree<Key, T> _tree;

 public:
  // constructors
  BinaryTree();
  BinaryTree(std::initializer_list<value_type> const &items);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other);
  ~BinaryTree();
  BinaryTree<Key, T> &operator=(BinaryTree<Key, T> &&other);
  BinaryTree<Key, T> &operator=(BinaryTree<Key, T> &other);

  std::pair<iterator, bool> insert_data_AC(const value_type &data);
  void preorder_insert(Node node, Node leaf);
  // iterators
  iterator begin();
  iterator end();
  // capacity
  bool empty();
  size_type size();
  size_type max_size();
  // modifiers
  void clear();
  void erase(iterator pos);  // проверить, что с итератором после удаления?
  void swap(BinaryTree &other);
  void merge(BinaryTree &other);
  // lookup
  bool contains(const Key &key);

  // additional methods
  void print_tree();
};
}  // namespace s21

#include "s21_BinaryTree.inl"
