#ifndef S21_CONTAINERS_LIB_S21_VECTOR_H_
#define S21_CONTAINERS_LIB_S21_VECTOR_H_

#include <iostream>
#include <memory>
#include <cstddef>

template <typename T>  // , class Allocator = std::allocator<T>
class Vector {
  T* data;
  size_t v_size;
  size_t v_capacity;
  
 public:
  // T& operator=();

  T& operator[](size_t i);
  const T& operator[](size_t i) const;
  T& at(size_t i);

  size_t size() const noexcept;
  size_t capacity() const noexcept;
  void reserve(size_t n);
  // void shrink_to_fit();
  
  void resize(size_t n, const T& value = T());
  void push_back(const T& value);
  void pop_back();

 // private:
  
};

template <>
class Vector<bool> {

};

#endif  // S21_CONTAINERS_LIB_S21_VECTOR_H_
