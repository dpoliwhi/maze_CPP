#include <map>
#include <map>

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
  // typedef typename BinaryTree<Key, T>::const_iterator const_iterator;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  // map(map &&m);
  ~map();
  // map<value_type> &operator=(map<value_type> &&m);
  // map<value_type> &operator=(map<value_type> &m);

  // element access
  T &at(const Key &key);
  T &operator[](const Key &key);

  // iterators
  iterator begin();
  iterator end();

  // capacity
  bool empty();
  size_type size();
  size_type max_size();

  // modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  // lookup
  bool contains(const Key &key);
};

template <class Key, class T>
map<Key, T>::map() : BinaryTree<Key, T>::BinaryTree() {}

template <class Key, class T>
map<Key, T>::map(const map &m) {}


template <class Key, class T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : BinaryTree<Key, T>::BinaryTree(items) {}

template <class Key, class T>
map<Key, T>::~map() {}

template <class Key, class T>
bool map<Key, T>::empty() {return BinaryTree<Key, T>::empty();}

template <class Key, class T>
size_t map<Key, T>::size() {return BinaryTree<Key, T>::size();}



}  // namespace s21

int main() {
  // std::map<int, int> myFirstMap;

  // //вывод явно инициализированной map на экран
  // // for (auto it = myFirstMap.end(); it != myFirstMap.begin(); --it)
  // // {
  // //     std::cout << it->first << " : " << it->second << std::endl;
  // // }
  // auto it1 = myFirstMap.begin();
  // // ++it1;
  // // ++it1;
  // // ++it1;
  // // ++it1;
  // // ++it1;
  // // ++it1;

  // std::cout << "iterator std: " << it1->second << std::endl;

  s21::map<int, int> one = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  std::cout << one.size() << std::endl;
  // s21::map<int, int> one;
  // one.a = 5;
  //  typename s21::map<int, int>::iterator s21_it(one.begin());
  // typename s21::map<int, int>::iterator s21_it1(one.end());
  // std::cout << "end " << s21_it1._node->data.second << std::endl;
  one.print_tree();

  // auto it2 = one.end();
  // --it2;
  // std::cout << it2._node->data.first << " : " << it2._node->data.second << std::endl;
  // --it2;
  // std::cout << it2._node->data.first << " : " << it2._node->data.second << std::endl;
  // --it2;
  // std::cout << it2._node->data.first << " : " << it2._node->data.second << std::endl;
  // --it2;
  // std::cout << it2._node->data.first << " : " << it2._node->data.second << std::endl;
  // --it2;
  // std::cout << it2._node->data.first << " : " << it2._node->data.second << std::endl;

  // for (auto it = one.end(); it != one.begin(); --it)
  // {
  //     std::cout << it._node->data.first << " : " << it._node->data.second << std::endl;
  // }

  // std::map<int, int> two = {{12, 112}, {13, 113}, {10, 100}, {5, 55}, {7, 77}, {2, 22}};
  // std::map<int, int>::iterator iter(two.begin());

  // std::pair<int, int> pair_iter = *iter;
  // std::cout << pair_iter.first << std::endl;
  return 0;
}
