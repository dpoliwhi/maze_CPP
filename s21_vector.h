#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <cmath>
#include <iostream>
#include <vector>

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
    vec v = {nullptr, nullptr};

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
    vector(size_type n);
    vector(std::initializer_list<value_type> const &items);
    vector(const vector &s);
    vector(vector &&s);
    ~vector();
    // overload operators
    vector<value_type> &operator=(vector<value_type> &&s);
    vector<value_type> &operator=(vector<T> &s);
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

    // Additional
    void Print_vector();
    };

}   // namespace s21

namespace s21 {

    // constructors
    template <typename T>
    vector<T>::vector() : _size(0), _capacity(0), _data(nullptr) {}

    template <typename T>
    vector<T>::vector(size_type n) : _size(0), _capacity(n), _data(n ? new value_type[n] : nullptr) {}

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
    vector<T>::vector(std::initializer_list<value_type> const &items) : _size(0), _capacity(0) {
        _data = new value_type[items.size()];
        int i = 0;
        for (auto it = items.begin(); it != items.end(); it++) _data[i++] = *it;
        _size = items.size();
        _capacity = items.size();
        v._begin = _data;
        v._end = _data + (_size);
    }

    template <typename T>
    vector<T>::vector(const vector &s) : _size(s._size), _capacity(s._capacity) {
        _data = new value_type[s._capacity];
        for (size_type i = 0; i < _size; i++) _data[i] = s._data[i];
        v = s.v;
    }

    template <typename T>
    vector<T>::vector(vector &&s) : _size(0), _capacity(0), _data(nullptr) {
        v = {nullptr, nullptr};
        std::swap(_size, s._size);
        std::swap(_capacity, s._capacity);
        std::swap(_data, s._data);
        std::swap(v, s.v);
    }

    template <typename T>
    void vector<T>::Destroy_vector() {
        delete _data;
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
    vector<T> &vector<T>::operator=(vector<T> &s) {
        if (this == &s) {
            return *this;
        } else {
            for (size_type i = 0; i < s._size; i++) push_back(s._data[i]);
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
        if (_size > _capacity) _capacity *= 2;
        for (size_type i = 0, t = 0; i < _size + 1; t++)
            if ((_data + t) == pos)
            buff[t] = value;
            else
            buff[t] = _data[i++];
        delete[] _data;
        _data = buff;
        v._begin = _data;
        _size++;
        size_type count = pos - begin();
        return (buff + count);
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
        if (pos < 0 || pos >= _size)
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
            return *v._begin;
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

    // Additional
    template <typename T>
    void vector<T>::Print_vector() {
        for (size_type i = 0; i < _size; ++i) std::cout << _data[i] << " ";
        std::cout << std::endl;
    }

}  // namespace s21

#endif  //    SRC_S21_VECTOR_H_
