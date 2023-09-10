#ifndef CONTAINERS_LIB_VECTOR_H_
#define CONTAINERS_LIB_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Vector {
  using size_type = std::size_t;  // std::allocator<T>::size_type;
  using alloc_traits = std::allocator_traits<Allocator>;
  using reference = T&;
  using const_reference = const T&;

  T* v_data;
  size_type v_size;
  size_type v_capacity;
  Allocator v_alloc;

 public:
  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  Vector() noexcept(noexcept(Allocator()))
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(Allocator()){};

  explicit Vector(size_type count, const Allocator& alloc = Allocator())
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(alloc) {
    // *this(count, 0);
    check_size(count);
    try {
      reserve(count);
      for (size_type i = 0; i < count; ++i) {
        new (v_data + i) T(0);  // TODO: реально ли так? если да, то надо try
                                // catch и освобождать
      }
    } catch (...) {
      throw;
    }
    v_size = count;
  };

  Vector(size_type count, const T& value, const Allocator& alloc = Allocator())
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(alloc) {
    try {
      reserve(count);
      for (size_type i = 0; i < count; ++i) {
        new (v_data + i) T(value);  // TODO: реально ли так? если да, то надо
                                    // try catch и освобождать
      }
    } catch (...) {
      throw;
    }
    v_size = count;
  };

  // ------- Copy -------
  Vector(const Vector& other)
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(Allocator()) {
    reserve(other.v_capacity);
    copyElems(other);
  };

  Vector(const Vector& other, const Allocator& alloc)
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(Allocator()) {
    reserve(other.v_capacity);
    copyElems(other);
  };

  // ------- Move -------
  // vector( vector&& other ) noexcept;

  // vector( vector&& other, const Allocator& alloc );

  // ------- initializer_list -------
  // vector( std::initializer_list<T> init, const Allocator& alloc = Allocator()
  // );

  // ------- Destructors -------
  ~Vector() {
    if (v_data != nullptr) {
      delete[] v_data;
    }
  };

  // ------- = -------
  reference operator=(const Vector& other) {
    if (*this != other) {
      Vector copy(other);
      swap(copy);
    }
    return *this;
  };

  // TODO: vector& operator=( vector&& other );

  // --------------------- ELEMENT ACCESS ---------------------
  reference at(size_type pos) {
    if (pos > v_size || !v_size) {
      throw std::out_of_range(
          "vector::_M_range_check: __n (which is" + std::to_string(pos) +
          ">= this->size() (which is " + std::to_string(pos) + ")");
    }
    return v_data[pos];
  };

  const_reference at(size_type pos) const {
    if (pos > v_size || !v_size) {
      throw std::out_of_range(
          "vector::_M_range_check: __n (which is" + std::to_string(pos) +
          ">= this->size() (which is " + std::to_string(pos) + ")");
    }
    return v_data[pos];
  };

  reference operator[](size_type i) { return v_data[i]; };
  const reference operator[](size_type i) const { return v_data[i]; };

  reference front() { return data[0]; };
  const_reference front() const { return data[0]; };

  reference back() { return data[v_size - 1]; };
  const_reference back() const { return data[v_size - 1]; };

  T* data() noexcept { return v_data; };
  const T* data() const noexcept { return v_data; };

  // --------------------- CAPACITY ---------------------
  size_type size() const noexcept { return v_size; };

  size_type capacity() const noexcept { return v_capacity; };

  void reserve(size_type n) {
    if (n > v_capacity) {
      T* new_v_data = reinterpret_cast<T*>(new char[n * sizeof(T)]);
      try {
        std::uninitialized_copy(v_data, v_data + v_size, new_v_data);
      } catch (...) {
        delete[] reinterpret_cast<char*>(new_v_data);
        throw;
      }
      for (size_type i = 0; i < v_size; ++i) {
        v_data[i].~T();
      }
      delete[] reinterpret_cast<char*>(v_data);
      v_data = new_v_data;
      v_capacity = n;
    }
  };

  size_type max_size() const { return alloc_traits::max_size(v_alloc); };

  void shrink_to_fit() {
    size_type old_cap = v_capacity;
    for (size_type i = v_size; i < old_cap; ++i) {
      v_data[i].~T();
      v_capacity--;
    }
  };

  // --------------------- ITERATORS ---------------------

  // --------------------- MODIFIERS ---------------------
  void resize(size_type n, const T& value = T()) {
    if (n > v_capacity) reserve(n);
    size_type i = v_size;
    try {
      for (; i < n; ++i) {
        new (v_data + i) T(value);
      }
    } catch (...) {
      for (size_type j = v_size; j < i; ++j) {
        v_data[j].~T();
      }
      throw;
    }
    if (n < v_size) {
      v_size = n;
    }
  };

  void push_back(const T& value) {
    if ((v_capacity == v_size)) {
      reserve(2 * v_size + 1);
    }
    try {
      new (v_data + v_size) T(value);
      ++v_size;
    } catch (...) {
      v_data[v_size].~T();
      throw;
    }
  };

  void pop_back() {
    --v_size;
    v_data[v_size].~T();
  };

  void swap(Vector& other) {
    std::swap(v_data, other.v_data);
    std::swap(v_size, other.v_size);
    std::swap(v_capacity, other.v_capacity);
  };

 private:
  int check_size(size_type size) const {
    if (max_size() < size) {
      throw std::invalid_argument("std::vector larger than max_size()");
    }
    return true;
  }
  void copyElems(const Vector& other) {
    for (size_type i = 0; i < other.v_size; ++i) {
      v_data[i] = other.v_data[i];
    }
    v_size = other.v_size;
  }
};

template <>
class Vector<bool> {};

#endif  // CONTAINERS_LIB_VECTOR_H_
