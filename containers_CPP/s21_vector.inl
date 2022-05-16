namespace s21 {

// constructors
template <typename T>
vector<T>::vector() : _size(0), _capacity(0), _data(nullptr), v({nullptr, nullptr}) {}

template <typename T>
vector<T>::vector(size_type n)
    : _size(0), _capacity(n), _data(n ? new value_type[n] : nullptr), v({nullptr, nullptr}) {}

template <typename T>
void vector<T>::Reserve_more_capacity(size_type size, bool shrink) {
  value_type *buff = new value_type[size];
  if (shrink == false)
    for (size_type i = 0; i < _size; ++i) buff[i] = std::move(_data[i]);
  else
    for (size_type i = 0; i < size; ++i) buff[i] = std::move(_data[i]);
  delete[] _data;
  _data = buff;
  _capacity = size;
}

template <typename T>
vector<T>::~vector() {
  delete[] _data;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : _data(nullptr), _size(0), _capacity(0), v({nullptr, nullptr}) {
  _data = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) _data[i++] = *it;
  _size = items.size();
  _capacity = items.size();
  v._begin = _data;
  v._end = _data + (_size);
}

template <typename T>
vector<T>::vector(const vector &s)
    : _data(nullptr), _size(s._size), _capacity(s._capacity), v({nullptr, nullptr}) {
  _data = new value_type[s._capacity];
  for (size_type i = 0; i < _size; ++i) _data[i] = s._data[i];
  v = s.v;
}

template <typename T>
vector<T>::vector(vector &&s) : _size(0), _capacity(0), _data(nullptr), v({nullptr, nullptr}) {
  std::swap(_size, s._size);
  std::swap(_capacity, s._capacity);
  std::swap(_data, s._data);
  std::swap(v, s.v);
}

template <typename T>
void vector<T>::Destroy_vector() {
  if (_data) delete[] _data;
  _size = 0;
  _capacity = 0;
  _data = nullptr;
  v = {nullptr, nullptr};
}

// overload operators
template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&s) {
  if (this == &s) {
    return *this;
  } else {
    Destroy_vector();
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
    std::swap(_data, s._data);
    std::swap(v, s.v);
    return *this;
  }
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &s) {
  if (this == &s) {
    return *this;
  } else {
    for (size_type i = 0; i < s._size; ++i) push_back(s._data[i]);
    _size = s._size;
    _capacity = s._capacity;
    v._begin = _data;
    v._end = _data + (_size);
    return *this;
  }
}

// Capacity
template <typename T>
bool vector<T>::empty() {
  if (_size) {
    return false;
  } else {
    return true;
  }
}

template <typename T>
size_t vector<T>::size() {
  return _size;
}

template <typename T>
size_t vector<T>::max_size() {
  return (pow(2, (64 - sizeof(T)) - 1));
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= _capacity)
    return;
  else
    Reserve_more_capacity(size, false);
}

template <typename T>
void vector<T>::shrink_to_fit() {
  Reserve_more_capacity(_size, true);
}

template <typename T>
size_t vector<T>::capacity() {
  return _capacity;
}

// Modifiers
template <typename T>
void vector<T>::clear() {
  Destroy_vector();
}

template <typename T>
T *vector<T>::insert(T *pos, const T &value) {
  value_type *buff = new value_type[_size + 1];
  size_type pos_in_data = pos - _data;
  if (_size == _capacity) Reserve_more_capacity(_capacity *= 2, false);
  for (size_type i = 0, t = 0; t < _size + 1; t++)
    if (t == pos_in_data)
      buff[t] = value;
    else
      buff[t] = _data[i++];
  _size++;
  for (size_t i = 0; i < _size; i++) {
    _data[i] = buff[i];
  }
  delete[] buff;
  v._begin = _data;
  size_type count = pos - begin();
  return (_data + count);
}

template <typename T>
void vector<T>::erase(T *pos) {
  value_type *buff = new value_type[_size - 1];
  for (size_type i = 0, t = 0; i < _size; i++)
    if ((_data + i) != pos) buff[t++] = _data[i];
  delete[] _data;
  _data = buff;
  _size--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (_size >= _capacity) {
    Reserve_more_capacity((_size + 2), false);
  }
  _data[_size++] = value;
  if (_size == 1) v._begin = _data;
  v._end = _data + (_size);
}

template <typename T>
void vector<T>::pop_back() {
  if (_size == 0) {
    throw std::invalid_argument("Nothihg to pop");
  } else {
    _size--;
    v._end = _data + (_size);
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  if (!empty() && !other.empty()) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_data, other._data);
    std::swap(v, other.v);
  }
}

// Element access
template <typename T>
T &vector<T>::at(size_type pos) {
  if (pos >= _size)
    throw std::out_of_range("Incorrect position of element");
  else
    return _data[pos];
}

template <typename T>
T &vector<T>::operator[](size_type pos) {
  if (pos >= _size)
    throw std::out_of_range("Incorrect position of element");
  else
    return _data[pos];
}

template <typename T>
const T &vector<T>::front() {
  if (v._begin == nullptr)
    throw std::out_of_range("Front element doesn't exist");
  else
    return _data[0];
}

template <typename T>
const T &vector<T>::back() {
  if (v._end == nullptr)
    throw std::out_of_range("Back element doesn't exist");
  else
    return *(v._end - 1);
}

template <typename T>
T *vector<T>::data() {
  return _data;
}

// Iterators
template <typename T>
T *vector<T>::begin() {
  if (v._begin == nullptr)
    throw std::out_of_range("Beginig of vector doesn't exist");
  else
    return v._begin;
}

template <typename T>
T *vector<T>::end() {
  if (v._end == nullptr)
    throw std::out_of_range("Endinig of vector doesn't exist");
  else
    return v._end;
}

template <typename T>
template <class TYPE, class... Args>
void vector<T>::emplace_back(TYPE data, Args... args) {
  push_back(data);
  emplace_back(args...);
}

template <typename T>
template <class TYPE, class... Args>
typename vector<T>::iterator vector<T>::emplace(iterator pos, TYPE data, Args... args) {
  pos = insert(pos, data);
  emplace(pos, args...);
  return pos;
}

}  // namespace s21
