#pragma once

#include <iostream>
#include <string>
#include <utility>

namespace s21 {
enum nodeColor { BLACK, RED };

template <class Key, class T>
struct _NodeRBT {
  std::pair<Key, T> data;
  nodeColor color;
  _NodeRBT<Key, T> *left;
  _NodeRBT<Key, T> *right;
  _NodeRBT<Key, T> *parent;
  _NodeRBT();
  _NodeRBT(std::pair<Key, T> pair_data, _NodeRBT<Key, T> *buf);
};

template <class Key, class T>
class RedBlackTree {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Node = _NodeRBT<Key, T> *;

 private:
  size_type _size;
  void clear_tree_helper(Node root);
  void printHelper(Node root, std::string indent, bool last);
  void rotate_left(Node x);
  void rotate_right(Node x);
  void insertFixup(Node x);
  void insertNode(Node new_data);
  void transplant_tree(Node x, Node z);
  void deleteFixup(Node x);
  std::pair<Node, bool> find_by_node(Node node, Key key);

 public:
  // constructors
  RedBlackTree();
  ~RedBlackTree();
  void clear_tree();
  Node root;
  Node leaf;

  // main methods
  std::pair<Node, bool> insert_data(const value_type &data);
  std::pair<Node, bool> find_by_key(const Key &key);
  void deleteNode(Node node, Key key);

  // additional methods
  void printTree();
  void inorder_print(Node node);
  size_type size();
  void set_size(size_type size);
};
}  // namespace s21

#include "s21_rbtree.inl"
