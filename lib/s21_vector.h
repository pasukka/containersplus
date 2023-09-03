#ifndef S21_CONTAINERS_LIB_S21_VECTOR_H_
#define S21_CONTAINERS_LIB_S21_VECTOR_H_

#include "stddef.h"

template <class T>  // , class Allocator = std::allocator<T>
class Vector {
  // public:

 private:
  T* data;
  size_t size;
  size_t capacity;
};

#endif  // S21_CONTAINERS_LIB_S21_VECTOR_H_
