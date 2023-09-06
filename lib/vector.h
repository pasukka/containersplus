#ifndef CONTAINERS_LIB_VECTOR_H_
#define CONTAINERS_LIB_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Vector {
  T* data;
  size_t v_size;
  size_t v_capacity;

 public:
  // --------------------- MEMBER FUNCTION ---------------------
  Vector() noexcept : data(nullptr), v_size(0), v_capacity(0){};

  Vector(size_t n) : data(nullptr), v_size(0), v_capacity(0) {
    // TODO: 
    // size_type max_size() const;
    // std::vector larger than max_size()


    try {
      reserve(n);
      for (size_t i = 0; i < n; ++i) {
        new (data + i) T(0);
      }
    } catch (...) {
      throw;
    }
    v_size = n;
  };

  ~Vector() {
    if (data != nullptr) {
      delete[] data;
    }
  };

  // constexpr ~vector();

  Vector(const Vector& other) : data(nullptr), v_size(0), v_capacity(0) {
    reserve(other.v_capacity);
    for (size_t i = 0; i < other.v_size; ++i) {
      data[i] = other.data[i];
    }
    v_size = other.v_size;
  };

  T& operator=(const Vector& other) {
    if (*this != other) {
      Vector copy(other);
      swap(copy);
    }
    return *this;
  };

  // Vector<int>(const Vector<int>&)

  // --------------------- ELEMENT ACCESS ---------------------
  T& operator[](size_t i) { return data[i]; };

  const T& operator[](size_t i) const { return data[i]; };

  T& at(size_t i) {
    if (i >= v_size) {
      throw std::out_of_range("Index out of range.");
    }
    return data[i];
  };

  // --------------------- CAPACITY ---------------------
  size_t size() const noexcept { return v_size; };

  size_t capacity() const noexcept { return v_capacity; };

  void reserve(size_t n) {
    if (n > v_capacity) {
      T* new_data = reinterpret_cast<T*>(new char[n * sizeof(T)]);
      try {
        std::uninitialized_copy(data, data + v_size, new_data);
      } catch (...) {
        delete[] reinterpret_cast<char*>(new_data);
        throw;
      }
      for (size_t i = 0; i < v_size; ++i) {
        data[i].~T();
      }
      delete[] reinterpret_cast<char*>(data);
      data = new_data;
      v_capacity = n;
    }
  };

  // void shrink_to_fit();

  // --------------------- ITERATORS ---------------------

  // --------------------- MODIFIERS ---------------------
  void resize(size_t n, const T& value = T()) {
    if (n > v_capacity) reserve(n);
    size_t i = v_size;
    try {
      for (; i < n; ++i) {
        new (data + i) T(value);
      }
    } catch (...) {
      for (size_t j = v_size; j < i; ++j) {
        data[j].~T();
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
      new (data + v_size) T(value);
      ++v_size;
    } catch (...) {
      data[v_size].~T();
      throw;
    }
  };

  void pop_back() {
    --v_size;
    data[v_size].~T();
  };

  void swap(Vector& other) {
    std::swap(data, other.data);
    std::swap(v_size, other.v_size);
    std::swap(v_capacity, other.v_capacity);
  };

  // private:
};

template <>
class Vector<bool> {};

#endif  // CONTAINERS_LIB_VECTOR_H_
