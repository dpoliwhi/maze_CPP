#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <cmath>
#include <iostream>
#include <list>
#include <string>

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
    ListIterator(const list<T> &other);
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
    ListConstIterator(const list<T> &other);
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
  list();                                                // done
  list(size_type n);                                     // done
  list(std::initializer_list<value_type> const &items);  // done
  list(const list &l);                                   // done
  list(list &&l);                                        // done
  ~list();                                               // done
  list<value_type> &operator=(list<value_type> &&l);     // done
  list<value_type> &operator=(list<T> &l);               // done

  // Element access
  const_reference front();  // done
  const_reference back();   // done
  // iterators
  iterator begin();
  iterator end();
  // const iterators
  const_iterator cbegin();
  const_iterator cend();
  // capacity
  bool empty();          // done
  size_type size();      // done
  size_type max_size();  // done, need to check!
  // modifiers
  void clear();  // done
  iterator insert(iterator pos,
                  const_reference value);        // done
  void erase(iterator pos);                      // done
  void push_back(const_reference value);         // done
  void pop_back();                               // done
  void push_front(const_reference value);        // done
  void pop_front();                              // done
  void swap(list &other);                        // done
  void merge(list &other);                       // done
  void splice(const_iterator pos, list &other);  // done
  void reverse();                                // done
  void unique();                                 // done
  void sort();                                   // done
  // additional functions
  void printList();
};
}  // namespace s21

namespace s21 {

// constructors
template <typename T>
list<T>::list() : _size(0), _end(nullptr), _begin(nullptr) {}

template <typename T>
list<T>::list(size_type n) : _size(n), _end(nullptr), _begin(nullptr) {
  while (n) {
    push_back(0);
    _size--;
    n--;
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : _size(0), _end(nullptr), _begin(nullptr) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(const list &l) : _size(l._size) {
  if (l._begin == nullptr) {
    _begin = nullptr;
  } else {
    _begin = _end = nullptr;
    _size = 0;
    Node *temp = l._begin;
    while (temp != 0) {
      push_back(temp->_data);
      temp = temp->_next;
    }
  }
}

template <typename T>
list<T>::list(list &&l) : _size(0), _end(nullptr), _begin(nullptr) {
  std::swap(_begin, l._begin);
  std::swap(_end, l._end);
  std::swap(_size, l._size);
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&l) {
  if (this == &l) {
    return *this;
  } else {
    clear();
    std::swap(_begin, l._begin);
    std::swap(_end, l._end);
    std::swap(_size, l._size);
    return *this;
  }
}

template <typename T>
list<T> &list<T>::operator=(list<T> &l) {
  if (this == &l) {
    return *this;
  } else {
    if (l._begin == nullptr) {
      _begin = nullptr;
    } else {
      _begin = _end = nullptr;
      _size = 0;
      Node *temp = l._begin;
      while (temp != 0) {
        push_back(temp->_data);
        temp = temp->_next;
      }
    }
    return *this;
  }
}

// accessors
template <typename T>
const T &list<T>::front() {
  if (_size == 0) {
    throw std::invalid_argument("No items available");
  } else {
    return _begin->_data;
  }
}

template <typename T>
const T &list<T>::back() {
  if (_size == 0) {
    throw std::invalid_argument("No items available");
  } else {
    return _end->_data;
  }
}

// iterators
template <class T>
list<T>::ListIterator::ListIterator() : _iter(nullptr), _head(nullptr), _tail(nullptr) {}

template <class T>
list<T>::ListIterator::ListIterator(const list<T> &other)
    : _iter(other._begin), _head(other._begin), _tail(other._end) {}

template <typename T>
typename list<T>::ListIterator list<T>::begin() {
  if (empty()) {
    throw std::out_of_range("Beginig of list doesn't exist");
  } else {
    iterator it;
    it._iter = _begin;
    return it;
  }
}

template <typename T>
typename list<T>::ListIterator list<T>::end() {
  if (empty()) {
    throw std::out_of_range("Endinig of list doesn't exist");
  } else {
    iterator it(*this);
    while (it._iter != nullptr) it._iter = it._iter->_next;
    return it;
  }
}

template <typename T>
void list<T>::ListIterator::operator++() {
  if (_iter->_next) _iter = _iter->_next;
}

template <typename T>
void list<T>::ListIterator::operator--() {
  if (_iter) {
    _iter = _iter->_prev;
  } else {
    _iter = _tail;
  }
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) {
  return (this->_iter != other._iter);
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator &other) {
  return (this->_iter == other._iter);
}

// const iterators
template <class T>
list<T>::ListConstIterator::ListConstIterator() : _iter(nullptr), _head(nullptr), _tail(nullptr) {}

template <class T>
list<T>::ListConstIterator::ListConstIterator(const list<T> &other)
    : _iter(other._begin), _head(other._begin), _tail(other._end) {}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() {
  if (empty()) {
    throw std::out_of_range("Beginig of list doesn't exist");
  } else {
    const_iterator it;
    it._iter = _begin;
    return it;
  }
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() {
  if (empty()) {
    throw std::out_of_range("Endinig of list doesn't exist");
  } else {
    const_iterator it(*this);
    while (it._iter != nullptr) it._iter = it._iter->_next;
    return it;
  }
}

template <typename T>
void list<T>::ListConstIterator::operator++() {
  if (_iter->_next) _iter = _iter->_next;
}

template <typename T>
void list<T>::ListConstIterator::operator--() {
  if (_iter) {
    _iter = _iter->_prev;
  } else {
    _iter = _tail;
  }
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator &other) {
  return (this->_iter != other._iter);
}

template <typename T>
bool list<T>::ListConstIterator::operator==(const ListConstIterator &other) {
  return (this->_iter == other._iter);
}

// capacity
template <typename T>
bool list<T>::empty() {
  if (_size) {
    return false;
  } else {
    return true;
  }
}

template <typename T>
size_t list<T>::size() {
  return _size;
}

template <typename T>
size_t list<T>::max_size() {  // need to check!
  return (pow(2, (64 - sizeof(T)) - 1));
  // return static_cast<size_type>(pow(2, sizeof(void *) * 8) / sizeof(list) - 1);
}

// modifiers
template <typename T>
void list<T>::clear() {
  while (_begin) {
    _end = _begin->_next;
    delete _begin;
    _begin = _end;
  }
  _size = 0;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *buf = new Node;
  buf->_data = value;
  if (!_begin) {
    buf->_next = _end;
    _begin = buf;
    buf->_prev = nullptr;
  } else {
    buf->_next = _end->_next;
    buf->_prev = _end;
    _end->_next = buf;
  }
  _end = buf;
  _end->_next = nullptr;
  _size++;
}

template <typename T>
void list<T>::pop_back() {
  if (!empty() && _size != 1) {
    Node *buf = _end;
    _end = _end->_prev;
    _end->_next = nullptr;
    delete buf;
    _size--;
  } else if (_size == 1) {
    _end = nullptr;
    _begin = nullptr;
    _size--;
  } else {
    std::cout << "List is empty" << std::endl;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *buf = new Node;
  buf->_data = value;
  if (!_begin) {
    buf->_next = _end;
    _end = buf;
  } else {
    buf->_next = _begin;
    _begin->_prev = buf;
  }
  _begin = buf;
  _size++;
}

template <typename T>
void list<T>::pop_front() {
  if (!empty() && _size != 1) {
    Node *buf = _begin;
    _begin = _begin->_next;
    _begin->_prev = nullptr;
    delete buf;
    _size--;
  } else if (_size == 1) {
    _end = nullptr;
    _begin = nullptr;
    _size--;
  } else {
    std::cout << "Nothing to pop" << std::endl;
  }
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(_begin, other._begin);
  std::swap(_end, other._end);
  std::swap(_size, other._size);
}

template <typename T>
void list<T>::merge(list &other) {
  const_iterator cur = cend();
  splice(cur, other);
  other.clear();
}

template <typename T>
void list<T>::reverse() {
  if (!empty()) {
    Node *tmp, *ptr = NULL;
    Node *tmp_begin = _begin;
    ;
    while (_end->_next == 0) {
      tmp = _begin->_next;
      _begin->_next = ptr;
      ptr = _begin;
      _begin = tmp;
    }
    _begin = ptr;
    _end = tmp_begin;
  }
}

template <typename T>
void list<T>::unique() {
  if (!empty()) {
    iterator cur = end();
    for (; cur != begin(); --cur) {
      if (cur._iter && cur._iter->_data == cur._iter->_prev->_data) {
        --cur;
        erase(cur);
        cur = end();
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (!empty()) {
    Node *temp = _begin;
    while (temp->_next) {
      if (temp->_data > temp->_next->_data) {
        std::swap(temp->_data, temp->_next->_data);
        temp = temp->_next;
        sort();
      } else {
        temp = temp->_next;
      }
    }
  }
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == begin() && _size > 0) {
    pop_front();
  } else if (pos._iter == _end) {
    pop_back();
  } else if (pos == end()) {
    std::cout << "Out of range" << std::endl;
  } else {
    for (iterator iter = begin(); iter != end(); ++iter) {
      if (iter == pos) {
        Node *buf = iter.get_node();
        Node *buf_prev = buf->_prev;
        Node *buf_next = buf->_next;
        buf_prev->_next = buf_next;
        buf_next->_prev = buf_prev;
        delete buf;
        break;
      }
    }
    _size--;
  }
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListIterator pos, const T &value) {
  iterator result;
  if (pos == end()) {
    push_back(value);
    result = end();
    --result;
  } else if (pos == begin()) {
    push_front(value);
    result = begin();
  } else {
    Node *cur_pos = _begin;
    for (; cur_pos != _end && cur_pos != pos.get_node();) {
      cur_pos = cur_pos->_next;
    }
    Node *prev_pos = cur_pos->_prev;
    Node *new_node = new Node;
    new_node->_data = value;
    new_node->_prev = prev_pos;
    new_node->_next = cur_pos;
    prev_pos->_next = new_node;
    cur_pos->_prev = new_node;
    _size++;
    result = pos;
    --result;
  }
  return result;
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  iterator it;
  if (pos == cend())
    it = end();
  else
    it = begin();
  while (it._iter != pos._iter) ++it;
  while (other.size()) {
    insert(it, other.front());
    other.pop_front();
  }
}

// additional methods
template <typename T>
void list<T>::printList() {
  if (_begin) {
    Node *buf = _begin;
    while (buf) {
      std::cout << buf->_data << " ";
      buf = buf->_next;
    }
    std::cout << std::endl;
  } else
    std::cout << "List is empty" << std::endl;
}
}  // namespace s21

// for print std::list
std::ostream &operator<<(std::ostream &ostr, const std::list<int> &list) {
  for (auto &i : list) {
    ostr << " " << i;
  }
  return ostr;
}

#endif  //    SRC_S21_LIST_H_
