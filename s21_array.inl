namespace s21 {

// constructors
template <typename T, std::size_t N>
array<T, N>::array() {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
    if (items.size() > N) {
        throw std::out_of_range("too many initializers");
    }
    int i = 0;
    for (auto it = items.begin(); i < N; it++) {
        if (i < items.size()) _data[i++] = *it;
        else _data[i++] = 0;
    }
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
    for (size_type i = 0; i < this->size(); ++i) _data[i] = a._data[i];
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
    std::swap(_data, a._data);
}

template <typename T, std::size_t N>
array<T, N>::~array() {}

// overload operators
template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&a) {
    if (this == &a) {
      return *this;
    } else {
      std::swap(_data, a._data);
      return *this;
    }
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array<T, N> &a) {
    if (this == &a) {
      return *this;
    } else {
      for (size_type i = 0; i < this->size(); ++i) _data[i] = a._data[i];;
      return *this;
    }
}

// Capacity
template <typename T, std::size_t N>
bool array<T, N>::empty() {
  if (N == 0) {
    return true;
  } else {
    return false;
  }
}

template <typename T, std::size_t N>
size_t array<T, N>::size() {
    return N;
}

template <typename T, std::size_t N>
size_t array<T, N>::max_size() {
  return (pow(2, (64 - sizeof(T)) - 1));
}

// Element access
template <typename T, std::size_t N>
T& array<T, N>::at(size_type pos) {
    if (pos >= N) {
        throw std::out_of_range("position outside the array");
    }
    return _data[pos];
}

template <typename T, std::size_t N>
T& array<T, N>::operator[](size_type pos) {
    return _data[pos];
}

template <typename T, std::size_t N>
const T& array<T, N>::front() {
    return _data[0];
}

template <typename T, std::size_t N>
const T& array<T, N>::back() {
    return _data[N - 1];
}

template <typename T, std::size_t N>
T* array<T, N>::data() {
    return _data;
}

// Iterators
template <typename T, std::size_t N>
T* array<T, N>::begin() {
    return _data;
}

template <typename T, std::size_t N>
T* array<T, N>::end() {
    return _data + N;
}

// Modifiers
template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
    std::swap(_data, other._data);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
    for (int i = 0; i < N; ++i) _data[i] = value;
}

// Additional
template <typename T, std::size_t N>
void array<T, N>::Print_array() {
  for (size_type i = 0; i < this->size(); ++i) std::cout << _data[i] << " ";
  std::cout << std::endl;
}

}  // namespace s21
