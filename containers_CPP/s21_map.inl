#include "s21_BinaryTree.h"

namespace s21 {

template <class Key, class T>
map<Key, T>::map() : BinaryTree<Key, T>::BinaryTree() {}

template <class Key, class T>
map<Key, T>::map(const map &m) : BinaryTree<Key, T>::BinaryTree(m) {}

template <class Key, class T>
map<Key, T>::map(map &&m) : BinaryTree<Key, T>::BinaryTree(std::move(m)) {}

template <class Key, class T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : BinaryTree<Key, T>::BinaryTree(items) {}

template <class Key, class T>
map<Key, T>::~map() {}

template <class Key, class T>
map<Key, T> &map<Key, T>::operator=(map &&m) {
  BinaryTree<Key, T>::operator=(std::move(m));
  return *this;
}

template <class Key, class T>
map<Key, T> &map<Key, T>::operator=(map &m) {
  BinaryTree<Key, T>::operator=(m);
  return *this;
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool> map<Key, T>::insert(const value_type &value) {
  return this->insert_data_AC(value);
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool> map<Key, T>::insert(const Key &key, const T &obj) {
  return this->insert_data_AC({key, obj});
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(const Key &key,
                                                                                     const T &obj) {
  if (this->contains(key)) {
    typename map<Key, T>::iterator it_find(this->find_iterator(key));
    it_find._node->data.second = obj;
    return std::make_pair(it_find, true);
  } else {
    return this->insert_data_AC({key, obj});
  }
}

template <class Key, class T>
T &map<Key, T>::at(const Key &key) {
  if (!this->contains(key)) {
    throw std::out_of_range("Key not found");
  }
  s21::map<Key, T>::iterator it_at(this->find_iterator(key));
  return it_at._node->data.second;
}

template <class Key, class T>
T &map<Key, T>::operator[](const Key &key) {
  return at(key);
}

template <class Key, class T>
template <class... Args>
std::vector<std::pair<typename BinaryTree<Key, T>::iterator, bool>> map<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<typename BinaryTree<Key, T>::iterator, bool>> res;
  std::vector<value_type> bufArgs = {args...};
  for (auto &i : bufArgs) {
    res.push_back(insert(i));
  }
  return res;
}

}  // namespace s21
