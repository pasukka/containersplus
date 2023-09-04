#ifndef S21_CONTAINERS_LIB_S21_VECTOR_H_
#define S21_CONTAINERS_LIB_S21_VECTOR_H_

#include <cstddef>

template <class T>  // , class Allocator = std::allocator<T>
class Vector {
  T* data;
  size_t v_size;
  size_t v_capacity;
  
 public:
  size_t size() noexcept;



 // private:
  
};

#endif  // S21_CONTAINERS_LIB_S21_VECTOR_H_
