#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <iostream>
#include <string>

namespace s21 {

    template <class T>
    class stack {
    private:
    size_t _size;
    size_t _capacity;
    T *_stackptr;

    public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    private:
    void Reserve_more_capacity(size_type size);
    void Destroy_stack();

    public:
    // constructors
    stack();
    stack(size_type n);
    stack(std::initializer_list<value_type> const &items);
    stack(const stack &s);
    stack(stack &&s);
    ~stack();
    // overload operators
    stack<value_type> &operator=(stack<value_type> &&s);
    stack<value_type> &operator=(stack<T> &s);
    // main methods
    const_reference top();
    bool empty();
    size_type size();
    void push(const_reference value);
    void pop();
    void swap(stack &other);
    };
}   // namespace s21

namespace s21 {

    // constructors
    template <typename T>
    stack<T>::stack() : _size(0), _capacity(0), _stackptr(nullptr) {}

    template <typename T>
    stack<T>::stack(size_type n) : _size(0), _capacity(n), _stackptr(n ? new value_type[n] : nullptr) {}

    template <typename T>
    stack<T>::stack(std::initializer_list<value_type> const &items) : _size(0), _capacity(0) {
        _stackptr = new value_type[items.size()];
        int i = 0;
        for (auto it = items.begin(); it != items.end(); it++) _stackptr[i++] = *it;
        _size = items.size();
        _capacity = items.size();
    }

    template <typename T>
    stack<T>::stack(const stack &s) : _size(s._size), _capacity(s._capacity) {
        _stackptr = new value_type[s._capacity];
        for (size_type i = 0; i < _size; ++i) _stackptr[i] = s._stackptr[i];
    }

    template <typename T>
    stack<T>::stack(stack &&s) : _size(0), _capacity(0), _stackptr(nullptr) {
        std::swap(_size, s._size);
        std::swap(_capacity, s._capacity);
        std::swap(_stackptr, s._stackptr);
    }

    template <typename T>
    void stack<T>::Reserve_more_capacity(size_type size) {
        value_type *buff = new value_type[size];
        for (size_type i = 0; i < _size; ++i) buff[i] = std::move(_stackptr[i]);
        delete[] _stackptr;
        _stackptr = buff;
        _capacity = size;
    }

    template <typename T>
    stack<T>::~stack() {
        delete[] _stackptr;
    }

    template <typename T>
    void stack<T>::Destroy_stack() {
        _size = 0;
        _capacity = 0;
        _stackptr = nullptr;
    }

    // overload operators
    template <typename T>
    stack<T> &stack<T>::operator=(stack<T> &&s) {
        if (this == &s) {
            return *this;
        } else {
            Destroy_stack();
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
            std::swap(_stackptr, s._stackptr);
            return *this;
        }
    }

    template <typename T>
    stack<T> &stack<T>::operator=(stack<T> &s) {
        if (this == &s) {
            return *this;
        } else {
            for (size_type i = 0; i < s._size; i++) push(s._stackptr[i]);
            return *this;
        }
    }

    // main methods
    template <typename T>
    void stack<T>::swap(stack &other) {
        if (!empty() && !other.empty()) {
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(_stackptr, other._stackptr);
        }
    }

    template <typename T>
    size_t stack<T>::size() {
        return _size;
    }

    template <typename T>
    void stack<T>::push(const_reference value) {
        if (_size >= _capacity) {
            Reserve_more_capacity(_size + 2);
        }
        _stackptr[_size++] = value;
    }

    template <typename T>
    const T &stack<T>::top() {
        if (_size == 0) {
            throw std::invalid_argument("Nothihg to top");
        } else {
            return _stackptr[_size - 1];
        }
    }

    template <typename T>
    bool stack<T>::empty() {
        if (_size) {
            return false;
        } else {
            return true;
        }
    }

    template <typename T>
    void stack<T>::pop() {
        if (_size == 0) {
            throw std::invalid_argument("Nothihg to pop");
        } else {
            _size--;
        }
    }
} // namespace s21

#endif  //    SRC_S21_QUEUE_H_
